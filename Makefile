include source.mk

NAME	 =	pestilence
NAME_OBF =	pestilence_obfuscated

ODIR	 =	objs/
IDIR	 =	incs/
SDIR	 =	srcs/

OBJS	 =	$(addsuffix .o, $(addprefix $(ODIR), $(SRCS)))

CFLAGS   =	-I$(IDIR)
CFLAGS	 +=	-Wall -Werror -fno-plt
CFLAGS	 +=	-nostdlib -fno-builtin
CFLAGS	 += -g # TODO: remove
CFLAGS	 += -O2 -finline-functions
CFLAGS 	 += -fomit-frame-pointer
CFLAGS	 += -fno-asynchronous-unwind-tables
CFLAGS	 += -fno-merge-all-constants
NFLAGS  	=	-f elf64

CC		 =	@cc
RM		 =	@rm -rf
MKDIR	 =	@mkdir -p
NASM	 =	@nasm

# ASM_DIR	=	libasm/
# ASM_SRC	=	ft_setsid.s ft_fork.s ft_open.s ft_getdents64.s ft_lstat.s \
# 			ft_close.s ft_munmap.s ft_mmap.s ft_msync.s ft_fstat.s     \
# 			ft_ftruncate.s ft_mremap.s ft_exit.s ft_write.s
# ASM_OBJ =	$(addprefix $(ASM_DIR), $(ASM_SRC:.s=.o))

bonus: CFLAGS += -DBONUS
bonus: re

all: $(NAME)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@

$(ODIR)%.o:  $(SDIR)/%.c
	$(MKDIR) $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(ODIR)%.o:  $(SDIR)/%.s
	$(MKDIR) $(dir $@)
	$(NASM) $(NFLAGS) $< -o $@

$(NAME_OBF): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@
	strip --strip-all $(NAME_OBF)
	objcopy \
	  --remove-section .comment \
	  --remove-section .note \
	 $(NAME_OBF)


.PHONY: all clean fclean re

