# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lucmarti <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/03/28 15:42:43 by lucmarti          #+#    #+#              #
#    Updated: 2019/11/07 12:32:31 by lucmarti         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

Red=\x1b[31m
Green=\x1b[32m
Cyan=\x1b[36m
Yellow=\x1b[34m
End=\x1b[0m

NAME = rtv1

SRC_PATH = ./src
SRC_FILE = main.c init.c event.c error.c parser.c parse_objs.c free.c obj.c\
		   vector_tools.c parse_cc.c ray.c math.c rotation.c
SRC_FILE += light.c shadow.c draw.c
SRC_FILE += sphere.c plane.c cone.c cylinder.c

OBJ_PATH = ./objs
OBJ_FILE = $(SRC_FILE:.c=.o)
DEPS_FILE = $(SRC_FILE:.c=.d)

SRC = $(addprefix $(SRC_PATH)/,$(SRC_FILE))
OBJ = $(addprefix $(OBJ_PATH)/,$(OBJ_FILE))
DEPS = $(addprefix $(OBJ_PATH)/,$(DEPS_FILE))

LIB_OBJ = libft.a libmlx.a
LIBS = $(addprefix $(OBJ_PATH)/,$(LIB_OBJ))

CFLAGS = -Wall -Wextra -Werror -g3 -I./includes -I./libs/libft -I./libs/mlx\
		 -O3 -mfpmath=sse -march=native -funroll-loops
MLXFLAGS = -framework OpenGL -framework AppKit -lm
CPPFLAGS = -MMD -MP 

ifndef VERBOSE
.SILENT:
VERBOSE=0
endif

all: $(NAME)

libft:
	@mkdir $(OBJ_PATH) 2> /dev/null || true
	@$(MAKE) -C ./libs/libft "VERBOSE=$(VERBOSE)"
	@cp -a ./libs/libft/libft.a $(OBJ_PATH)/libft.a

mlx:
	@mkdir $(OBJ_PATH) 2> /dev/null || true
	@$(MAKE) -C ./libs/mlx "VERBOSE=$(VERBOSE)"
	@cp -a ./libs/mlx/libmlx.a $(OBJ_PATH)/libmlx.a

$(NAME): $(OBJ)
	@mkdir $(OBJ_PATH) 2> /dev/null || true
	@$(MAKE) -C ./libs/libft "VERBOSE=$(VERBOSE)"
	@cp -a ./libs/libft/libft.a $(OBJ_PATH)/libft.a
	@mkdir $(OBJ_PATH) 2> /dev/null || true
	@$(MAKE) -C ./libs/mlx "VERBOSE=$(VERBOSE)"
	@cp -a ./libs/mlx/libmlx.a $(OBJ_PATH)/libmlx.a
	@gcc $(CFLAGS) $(MLXFLAGS) -o $(NAME) $(OBJ) $(LIBS)
	@echo "Compilation of $(Cyan)$(NAME)$(End)   :    ${Green}Done${End}"

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c
	@mkdir -p $(OBJ_PATH) 2> /dev/null || true
	@gcc $(CFLAGS) $(CPPFLAGS) -o $@ -c $<
	@echo "[${Green}Compiled${End}] : $<"

.PHONY: clean fclean miniclean minire re

clean:
	@rm -f $(OBJ)
	@rm -f $(LIBS)
	@$(RM) $(DEPS)
	@$(MAKE) -C ./libs/libft/ clean 
	@$(MAKE) -C ./libs/mlx/ clean 
	@rmdir $(OBJ_PATH) 2> /dev/null || (true && if [ -d "$(OBJ_PATH)" ]; then\
		echo "$(Red)ERROR$(End)	: $(OBJ_PATH) is not empty."; fi)
	@echo "$(Red)$(NAME)$(End) : Removing objects"

fclean: clean
	@rm -f $(NAME)
	@$(MAKE) -C ./libs/libft/ fclean 
	@echo "$(Red)$(NAME)$(End) : Removing $(NAME)"

miniclean:
	@rm -f $(OBJ)

minire: miniclean all

re: fclean all
-include $(DEPS)
