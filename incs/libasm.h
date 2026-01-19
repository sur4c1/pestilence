/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libasm.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyyyyy <yyyyyy@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 13:20:22 by yyyyyy            #+#    #+#             */
/*   Updated: 2024/10/16 13:47:37 by yyyyyy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBASM_H
#define LIBASM_H

struct stat;

int		ft_setsid(void);
int		ft_fork(void);
int		ft_open(char *path, int flags, ...);
int		ft_getdents64(int fd, char *buffer, int buff_size);
int		ft_lstat(const char *pathname, struct stat *statbuf);
int		ft_close(int fd);
int		ft_munmap(void *addr, unsigned long length);
void	*ft_mmap(void *addr, unsigned long length, int prot, int flags,
			int fd, off_t offset);
int		ft_msync(void *addr, unsigned long length, int flags);
int		ft_fstat(int fd, struct stat *statbuf);
int		ft_ftruncate(int fd, off_t length);
void	*ft_mremap(void *old_address, unsigned long old_size,
			unsigned long new_size, int flags, ... /* void *new_address */);
void	ft_exit(int status);
void	ft_write(int fd, void *buf, unsigned count);

#endif
