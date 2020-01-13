# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lucmarti <lucmarti@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/11/09 15:37:09 by lucmarti          #+#    #+#              #
#    Updated: 2019/09/24 16:19:22 by lucmarti         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

UNAME_S = $(shell uname -s)
ifeq ($(UNAME_S),Linux)
ECHOc = echo -e
else
ECHOc = echo
endif

ifndef ECHO
T = $(words $(SRC))
N := x
C = $(words $N)$(eval N := x $N)
ECHO = $(ECHOc) "\r	[`expr $C '*' 100 / $T`%]\c"
endif

NAME = libft.a

OBJ_PATH = ./objs

# NORMAL FUNCTION PART

SRC := 	./ft_atoi.c ./ft_atoi_base.c ./ft_itoa.c ./ft_ltoa.c ./ft_ultoa.c\
	./ft_ftoa.c ./ft_atod.c
SRC += 	./ft_bzero.c
SRC += 	./ft_isalnum.c ./ft_isdigit.c ./ft_isalpha.c ./ft_isascii.c\
		./ft_isblank.c ./ft_isprint.c ./ft_isupper.c ./ft_iscinstr.c\
		./ft_isspace.c
SRC +=	./ft_lstadd.c ./ft_lstadd_back.c ./ft_lstdel.c ./ft_lstdelone.c\
		./ft_lstiter.c ./ft_lstmap.c ./ft_lstnew.c ./ft_lstfree_all.c\
		./ft_lstfree_at.c ./ft_lstsize.c ./ft_lstreplace.c
SRC +=	./ft_memalloc.c ./ft_memccpy.c ./ft_memchr.c ./ft_memcmp.c\
		./ft_memcpy.c ./ft_memdel.c ./ft_memmove.c ./ft_memset.c
SRC +=	./ft_putchar.c ./ft_putchar_fd.c
SRC +=	./ft_putendl.c ./ft_putendl_fd.c
SRC +=	./ft_putnbr.c ./ft_putnbr_fd.c
SRC +=	./ft_putstr.c ./ft_putstr_fd.c ./ft_putstrn.c
SRC +=	./ft_strcapitalize.c ./ft_strcat.c ./ft_strchr.c ./ft_strclr.c\
		./ft_strcmp.c ./ft_strcpy.c ./ft_strdel.c ./ft_strdup.c\
		./ft_strndup.c ./ft_strequ.c ./ft_striter.c ./ft_striteri.c\
		./ft_strjoin.c ./ft_strnjoin.c ./ft_strlcat.c ./ft_strlen.c\
		./ft_strreplace.c ./ft_strmap.c ./ft_strmapi.c ./ft_strncat.c\
		./ft_strncmp.c ./ft_strncpy.c ./ft_strnequ.c ./ft_strnew.c\
		./ft_strnstr.c ./ft_strrchr.c ./ft_strsplit.c ./ft_strstr.c\
		./ft_strsub.c ./ft_strtrim.c ./ft_strfchr.c	./ft_strjoinf.c\
		./ft_strjoinfn.c ./ft_straddc.c ./ft_strarray.c ./ft_strarray_add.c\
		./ft_strarray_free.c ./ft_strcnt.c ./ft_strocnt.c
SRC +=	./ft_tolower.c ./ft_toupper.c
SRC +=	./ft_vector2.c ./ft_dvector2.c ./ft_vector3.c ./ft_vector2cp.c\
		./ft_vector3cp.c ./ft_vector3_aux.c ./ft_vector3_aux2.c
SRC +=  ./ft_max.c
SRC +=	./ft_mat.c ./ft_mat_op.c ./ft_mat_mul.c	./ft_power.c ./ft_abs.c
SRC +=	./ft_arraylength.c ./ft_arraycpy.c
SRC +=	./ft_strrm_at.c ./ft_stradd_at.c ./ft_stradd_bf.c
SRC +=  ./gnl.c ./ft_arrayfree.c ./ft_arrayinit.c
SRC +=	./mat44.c ./mat44_invert.c ./mat44_op.c

OBJ_NF = $(SRC:.c=.o)
DEPS_NF = $(SRC:.c=.d)
OBJ := $(addprefix $(OBJ_PATH)/,$(OBJ_NF))
DEPS := $(addprefix $(OBJ_PATH)/,$(DEPS_NF))

# END OF NORMAL FUNCTION PART
# PRINTF FUNCTION PART

SRC_PFPATH = ./printf
SRC_PFILE = ft_printf.c error.c parser.c bool.c peacemaker.c\
		   hex.c print.c get_csp.c get_iuo.c get_x.c print_int.c print_hf.c\
		   print_ptr.c get_f.c init.c

SRC_TPFILE = $(addprefix $(SRC_PFPATH)/,$(SRC_PFILE))
OBJ_PFILE = $(SRC_TPFILE:.c=.o)
DEPS_PFILE = $(SRC_TPFILE:.c=.d)
SRC += $(SRC_TPFILE)
OBJ += $(addprefix $(OBJ_PATH)/,$(OBJ_PFILE))
DEPS += $(addprefix $(OBJ_PATH)/,$(DEPS_PFILE))

# This is a minimal set of ANSI/VT100 color codes
_END=\x1b[0m
_BOLD=\x1b[1m
_UNDER=\x1b[4m
_REV=\x1b[7m

# Colors
_GREY=\x1b[30m
_RED=\x1b[31m
_GREEN=\x1b[32m
_YELLOW=\x1b[33m
_BLUE=\x1b[34m
_PURPLE=\x1b[35m
_CYAN=\x1b[36m
_WHITE=\x1b[37m

ifndef VERBOSE
.SILENT:
VERBOSE = 0
endif

all: $(NAME)

$(NAME): $(OBJ)
	@ar -rc $(NAME) $(OBJ) libft.h
	@$(ECHOc) "\rCompilation of $(CYAN)libft$(_END)   :    $(_GREEN)Done${_END}"
	@ranlib $(NAME)

$(OBJ_PATH)/%.o: %.c libft.h 	
	@mkdir $(OBJ_PATH) 2> /dev/null || true
	@mkdir -p $(OBJ_PATH)/printf 2> /dev/null || true
	@gcc -g -Wall -Wextra -Werror -o $@ -c $<
	@$(ECHO)
ifeq ("$(VERBOSE)","1")
	@$(ECHOc) "[${_YELLOW}libft${_END}][${_GREEN}Compiled${_END}] : $<"
endif

.PHONY: clean fclean re

clean:
	@rm -f $(OBJ)
	@rm -f $(DEP)
	@rmdir $(OBJ_PATH)/printf 2> /dev/null\
	|| (true && if [ -d "$(OBJ_PATH)/printf" ]; then\
		$(ECHOc) "$(Red)ERROR$(End)	: $(OBJ_PATH)/printf is not empty."; fi)
	@rmdir $(OBJ_PATH) 2> /dev/null || (true && if [ -d "$(OBJ_PATH)" ]; then\
		$(ECHOc) "$(Red)ERROR$(End)	: $(OBJ_PATH) is not empty."; fi)

fclean: clean
	@rm -f $(NAME)

re: fclean all

-include $(DEP)
