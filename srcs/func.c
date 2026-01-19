/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyyyyy <yyyyyy@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 16:16:45 by xxxxxxx           #+#    #+#             */
/*   Updated: 2026/01/19 17:32:53 by yyyyyy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pestilence.h"

int errno;

int ft_strncmp(const char *s1, const char *s2, unsigned n)
{
	unsigned i;

	i = 0;
	while (i < n - 1 && ((unsigned char *) s1)[i] && ((unsigned char *) s2)[i]
		   && ((unsigned char *) s1)[i] == ((unsigned char *) s2)[i])
	{
		i++;
	}
	if (n)
		return (((unsigned char *) s1)[i] - ((unsigned char *) s2)[i]);
	return (0);
}

int ft_strcmp(const char *s1, const char *s2)
{
	int i;

	i = 0;
	while ((unsigned char) s1[i] && (unsigned char) s2[i]
		   && (unsigned char) s1[i] == (unsigned char) s2[i])
	{
		i++;
	}
	return ((unsigned char) s1[i] - (unsigned char) s2[i]);
}
void *memcpy(void *dst, void *src, unsigned n)
{
	unsigned i;

	i = 0;
	if (dst != src)
	{
		while (i < n)
		{
			((char *) dst)[i] = ((char *) src)[i];
			i++;
		}
	}
	return (dst);
}

void *ft_memmove(void *dst, const void *src, size_t len)
{
	size_t i;
	int	   step;

	if (dst == NULL && src == NULL)
		return (NULL);
	if (len > 0 && dst != src)
	{
		i = 0;
		step = 1;
		if (src < dst)
		{
			i = len - 1;
			step = -1;
		}
		while (i >= 0 && i < len)
		{
			((char *) dst)[i] = ((char *) src)[i];
			i += step;
		}
	}
	return (dst);
}

void set_errno(int error) { errno = error; }

int get_errno(void) { return errno; }

char *ft_strcpy(char *dest, char *src)
{
	int i;

	i = 0;
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char *ft_strcat(char *dest, char *src)
{
	int i;
	int size;

	i = 0;
	size = 0;
	while (dest[size])
	{
		size++;
	}
	while (src[i])
	{
		dest[size + i] = src[i];
		i++;
	}
	dest[i + size] = '\0';
	return (dest);
}

void ft_bzero(void *s, unsigned n)
{
	unsigned i;

	i = 0;
	while (i < n)
	{
		*(char *) s = 0;
		s++;
		i++;
	}
}

uint64_t ft_syscall(uint64_t syscall_number, uint64_t arg1, uint64_t arg2,
					uint64_t arg3, uint64_t arg4, uint64_t arg5, uint64_t arg6)
{
	uint64_t result;

	// Inline assembly to make the syscall
	asm volatile("mov %1, %%rax;" // Put syscall number in RAX
				 "mov %2, %%rdi;" // Put first argument in RDI
				 "mov %3, %%rsi;" // Put second argument in RSI
				 "mov %4, %%rdx;" // Put third argument in RDX
				 "mov %5, %%r10;" // Put fourth argument in R10 (not RCX due to
								  // syscall ABI)
				 "mov %6, %%r8;"  // Put fifth argument in R8
				 "mov %7, %%r9;"  // Put sixth argument in R9
				 "syscall;"		  // Trigger the syscall
				 "mov %%rax, %0;" // Store the return value from RAX into the
								  // result variable
				 : "=r"(result)	  // Output operand: result stored in %0
				 : "r"(syscall_number), "r"(arg1), "r"(arg2), "r"(arg3),
				   "r"(arg4), "r"(arg5), "r"(arg6)
				 : "rax", "rdi", "rsi", "rdx", "r10", "r8", "r9", "memory");

	return result;
}
