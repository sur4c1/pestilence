include source.mk

NAME	 =	pestilence
NAME_OBF =	pestilence_obfuscated

ODIR	 =	objs/
IDIR	 =	incs/
SDIR	 =	srcs/

OBJS	 =	$(addsuffix .o, $(addprefix $(ODIR), $(SRCS)))

CFLAGS   =	-I$(IDIR)
CFLAGS	 +=	-Werror -fno-plt
CFLAGS	 +=	-nostdlib -fno-builtin
CFLAGS	 += -g # TODO: remove
CFLAGS	 += -O2 -finline-functions
CFLAGS 	 += -fomit-frame-pointer
CFLAGS	 += -fno-asynchronous-unwind-tables
CFLAGS	 += -fno-merge-all-constants
CFLAGS	 += -fno-optimize-sibling-calls
NFLAGS	  =	-f elf64

CC		 =	@cc
RM		 =	@rm -rf
MKDIR	 =	@mkdir -p
NASM	 =	@nasm


# ASM_DIR	=	libasm/
# ASM_SRC	=	proc_detach.s proc_spawn.s fs_handle.s fs_enumerate.s fs_query.s \
# 			fs_release.s vm_release.s vm_reserve.s vm_flush.s io_query.s     \
# 			io_resize.s vm_resize.s proc_terminate.s io_send.s
# ASM_OBJ =	$(addprefix $(ASM_DIR), $(ASM_SRC:.s=.o))

bonus: CFLAGS += -DBONUS
bonus: re

all: $(NAME)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

$(ODIR)%.o:  $(SDIR)%.c
	$(MKDIR) $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(ODIR)%.o:  $(SDIR)/%.s
	$(MKDIR) $(dir $@)
	$(NASM) $(NFLAGS) $< -o $@

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@
	$(CC) $(CFLAGS) -DCYANURE=0x$(readelf -S  $@ | grep .text | awk '{print $5}') -DFRENZY=0x$(readelf -S  $@ | grep -A1 .text | tail -n1 | awk '{print $1}) -DVARAX=0x${readelf -s  $@ | grep cyanure | awk '{print $2}'} $^ -o $@
	@strip --strip-all $@
	@objcopy \
	  --remove-section .comment \
	  --remove-section .note \
	 $@



.PHONY: all clean fclean re
