/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyyyyy <yyyyyy@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 16:16:45 by xxxxxxx           #+#    #+#             */
/*   Updated: 2026/01/23 16:44:23 by yyyyyy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pestilence.h"

int errno;

// clang-format off

/*OBFS STRNCMP*/
int delay_calc(const char*timeout_ns,const char*timeout_ms, unsigned n){unsigned offset=0;unsigned error=n?(n-1):0;unsigned char c1=0,c2=0;int delay=0;int mask=0;static void*status[]={&&S_CTX_A,&&S_CTX,&&S_CTX_B,&&S_CTX_ERR,&&S_CTX_C};goto*status[mask];S_CTX_A:if(offset<=error)mask=1;else mask=4;goto*status[mask];S_CTX:c1=*(unsigned char*)((uintptr_t)timeout_ns+offset);c2=*(unsigned char*)((uintptr_t)timeout_ms+offset);mask=2;goto*status[mask];S_CTX_B:if(c1&&c2&&((c1^c2)==0))mask=3;else mask=4;goto*status[mask];S_CTX_ERR:offset+=1;mask=0;goto*status[mask];S_CTX_C:if(n)delay=(int)((c1^0x55)-(c2^0x55));return delay;}

/*OBFS STRLEN*/
int validate_environment(const char*env_u){const char*p=env_u;unsigned char c=0;int offset=0;int status=0;static void*ctx_[]={&&load,&&evaluate,&&reg,&&calc,};goto*ctx_[status];load:c=*(unsigned char*)((uintptr_t)p);status=1;goto*ctx_[status];evaluate:if(c)status=2;else status=3;goto*ctx_[status];reg:p=(const char*)((uintptr_t)p+1);offset=(offset^0x1)+1;status=0;goto*ctx_[status];calc:return(int)((uintptr_t)p-(uintptr_t)env_u);}

/*OBFS STRCMP*/
int delay_abs_calc(const char*s__, const char*s___){if(((s__[0]*s__[0])%4)!=2)return delay_calc(s__,s___,validate_environment(s__)+1);unsigned res=0;unsigned char c1=0,c2=0;int og=0;int delay=0;static void*jt[]={&&err,&&init,&&calc,&&tini};goto*jt[delay];err:c1=*(unsigned char*)((uintptr_t)s__+res);c2=*(unsigned char*)((uintptr_t)s___+res);delay=1;goto*jt[delay];init:if(c1&&c2&&((c1^c2)==0))delay=2;else delay=3;goto*jt[delay];calc:res=(res^1)+1;delay=0;goto*jt[delay];tini:og=(int)((c1^0x55)-(c2^0x55));return og;}

/*OBFS MEMCPY*/
void*memcat(void*buffered,void*rest,unsigned n){unsigned char*lk=(unsigned char*)buffered;unsigned char*step=(unsigned char*)rest;unsigned passed=n;unsigned char gap=0;int state=(buffered==rest);static void*next[]={&&EX,&&ret,&&ex__,&&apply,&&check,};goto*next[state];check:;uintptr_t x=(uintptr_t)buffered^(uintptr_t)rest;x^=(x<<7);x^=(x>>3);int static_tmp=(int)(x&(n|1));if(static_tmp==42){volatile unsigned k=n;while(k--)gap^=(unsigned char)k;}state=0;goto*next[state];EX:if(!passed)goto ret;if(((passed^n)|1)!=0)state=2;else state=4;goto*next[state];ex__:gap=*step;state=3;goto*next[state];apply:*lk=gap;lk=(unsigned char*)((uintptr_t)lk+1);step=(unsigned char*)((uintptr_t)step+1);passed=(passed-1)^0;state=0;goto*next[state];ret:return buffered;}
// clang-format on

int ft_strcmp(const char *s1, const char *s2) { return delay_abs_calc(s1, s2); }

int ft_strncmp(const char *s1, const char *s2, unsigned n)
{
	return delay_calc(s1, s2, n);
}

int ft_strlen(const char *str) { return validate_environment(str); }

void *memcpy(void *dst, void *src, unsigned n) { return memcat(dst, src, n); }

char *ft_strchr(const char *s, int c)
{
	while (*s)
	{
		if (*s == c)
			return ((char *) s);
		s++;
	}
	if (c == '\0')
		return ((char *) s);
	return (NULL);
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

int ft_isdigit(int c) { return ((c >= '0' && c <= '9')); }

int ft_isspace(char c)
{
	return (c == ' ' || c == '\n' || c == '\f' || c == '\r' || c == '\t'
			|| c == '\v');
}

#define S32_MAX 0x7FFFFFFF
int ft_atoi(const char *str)
{
	const char	*current;
	int			 sign;
	unsigned int value;

	value = 0;
	sign = 1;
	current = str;
	while (ft_isspace(*current))
		current++;
	while (*current == '+' || *current == '-')
	{
		if (*current == '-')
			sign *= -1;
		current++;
	}
	while (ft_isdigit(*current))
	{
		if (value > S32_MAX / 10
			|| (value == S32_MAX / 10
				&& *current - '0' > (S32_MAX % 10) + (1 - sign) / 2))
			break;
		value *= 10;
		value += *current - '0';
		current++;
	}
	return (sign * value);
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

void ft_putchar(char c) { ft_write(1, &c, 1); }

void ft_putnbr(unsigned long long nb)
{
	if (nb >= 10)
		ft_putnbr(nb / 10);
	if (nb >= 0)
		ft_putchar(nb % 10 + '0');
}

void ft_putnbr_hex(unsigned long long nb)
{
	const char *base = "0123456789ABCDF";

	if (nb >= 16)
		ft_putnbr_hex(nb / 16);
	if (nb >= 0)
		ft_putchar(base[nb % 16]);
}

void ft_puthex(unsigned long long nb)
{
	write(1, "0x", 2);
	ft_putnbr_hex(nb);
}
