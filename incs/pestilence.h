/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pestilence.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyyyyy <yyyyyy@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 17:16:00 by yyyyyy            #+#    #+#             */
/*   Updated: 2026/01/23 18:07:44 by yyyyyy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PESTILENCE_H
#define PESTILENCE_H

#include <elf.h>
#include <fcntl.h>
#include <stdbool.h>
#include <stdio.h>
#include <sys/mman.h>
#include <sys/ptrace.h>
#include <sys/stat.h>
#include <sys/types.h>

#include "libasm.h"

#define ElfW(type)	   Elf64_##type
#define FORMAT		   2
#define PATH_MAX	   4096
#define SIGNATURE_SIZE 43
#define FORK_SIZE	   29
#define MACHINE_SIZE   0x8f1
#define JMPABLE_SIZE   4

/********************************* STRUCTURES *********************************/

typedef enum e_stat
{
	OK,
	KO,
} t_stat;

struct linux_dirent64
{
	uint64_t	   d_ino;	 /* 64-bit inode number */
	int64_t		   d_off;	 /* 64-bit offset to the next dirent */
	unsigned short d_reclen; /* Length of this `linux_dirent64` */
	unsigned char  d_type;	 /* File type */
	char		   d_name[]; /* Filename (null-terminated) */
};

typedef struct s_elf
{
	ElfW(Ehdr) * header;
	ElfW(Shdr) * sections;
	ElfW(Shdr) * text_section;
	ElfW(Phdr) * segments;
	ElfW(Phdr) * executed_segment;
	t_stat stat;
} t_elf;

#define write ft_write

/********************************* PROTOTYPES *********************************/

// TODO: protos from famine
/*
void clean(t_file file);
*/
void infect(char *path, void *begin_ptr);
void processDirectory(char *folder, void *begin_ptr);
/*
char *get_section_name(ElfW(Shdr) str_section, ElfW(Shdr) section, char *data);
int is_elf_binary(t_file file);
ElfW(Shdr) * find_text_section(t_elf elf, t_file file);
ElfW(Phdr) * find_executed_segment(t_elf elf);
void inject(t_file file, t_elf elf, void *begin_ptr);
void edit_elf_header(t_elf elf);
*/
int is_program_running(const char *target);
int is_debugged(void);
void signature(char str[]);
int ft_strncmp(const char *s1, const char *s2, unsigned n);
int ft_strcmp(const char *s1, const char *s2);
void *memcpy(void *dst, void *src, unsigned n);
char *ft_strchr(const char *s, int c);
void *ft_memmove(void *dst, const void *src, size_t len);
char *ft_strcpy(char *dest, char *src);
char *ft_strcat(char *dest, char *src);
void ft_bzero(void *s, unsigned n);
int ft_strlen(const char *str);
int ft_atoi(const char *str);
uint64_t ft_syscall(uint64_t syscall_number, uint64_t arg1, uint64_t arg2,
					uint64_t arg3, uint64_t arg4, uint64_t arg5, uint64_t arg6);
void ft_putchar(char c);
void ft_putnbr(unsigned long long nb);
void ft_puthex(unsigned long long nb);
#endif
