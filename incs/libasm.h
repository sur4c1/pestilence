/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libasm.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyyyyy <yyyyyy@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 13:20:22 by yyyyyy            #+#    #+#             */
/*   Updated: 2026/02/10 17:49:24 by yyyyyy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBASM_H
#define LIBASM_H

struct stat;

int proc_detach(void);											// ft_setsid
int proc_spawn(void);											// ft_fork
int proc_control(int request, int pid, void *addr, void *data); // ft_ptrace
int fs_handle(char *path, int flags, ...);						// ft_open
int fs_enumerate(int fd, char *buffer, int buff_size);			// ft_getdents64
int fs_query(const char *pathname, struct stat *statbuf);		// ft_lstat
int fs_release(int fd);											// ft_close
int vm_release(void *addr, unsigned long length);				// ft_munmap
void *vm_reserve(void *addr, unsigned long length, int prot, int flags, int fd,
				 off_t offset);							   // ft_mmap
int vm_flush(void *addr, unsigned long length, int flags); // ft_msync
int io_query(int fd, struct stat *statbuf);				   // ft_fstat
int io_resize(int fd, off_t length);					   // ft_ftruncate
void *vm_resize(void *old_address, unsigned long old_size,
				unsigned long new_size, int flags,
				... /* void *new_address */);			// ft_mremap
void proc_terminate(int status);						// ft_exit
void io_send(int fd, void *buf, unsigned count);		// ft_write
ssize_t io_recv(int fd, const void *buf, size_t count); // ft_read

#endif
