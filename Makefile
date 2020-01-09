# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bnesoi <bnesoi@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/03/11 15:11:22 by bnesoi            #+#    #+#              #
#    Updated: 2019/10/20 19:47:54 by bnesoi           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=ft_ls

OS			=	$(shell uname -s)
CC			=	gcc
CFLAGS		=	-Wall -Wextra -Werror

SRC_FILES	=			\
	file.c				\
	file_info.c			\
	main.c				\
	parse.c				\
	put.c				\
	sort.c				\
	utils.c	

HDR_FILES	=			\
	ft_ls.h

DIR_SRC		=	./src
DIR_INC		=	./includes
DIR_OBJ		=	./obj

LIBFT		=	./libft/libft.a
LIBFT_DIR	=	./libft

FT_PRINTF		=	./ft_printf/libftprintf.a
FT_PRINTF_DIR	=	./ft_printf

SRC			=	$(addprefix $(DIR_SRC)/, $(SRC_FILES))
HDR			=	$(addprefix $(DIR_INC)/, $(HDR_FILES))
OBJ			=	$(addprefix $(DIR_OBJ)/, $(SRC_FILES:.c=.o))

INCLUDES	=	-I $(LIBFT_DIR) -I $(FT_PRINTF_DIR)/include -I $(DIR_INC)
LIBS		:=	./libft/libft.a ./ft_printf/libftprintf.a

LIBS	:= $(LIBS)

all: $(NAME)

$(DIR_OBJ):
	@mkdir $(DIR_OBJ)
	@mkdir $(DIR_OBJ)/ocl

$(NAME): $(DIR_OBJ) $(OBJ) $(LIBFT) $(FT_PRINTF)
	$(CC) $(CFLAGS) $(OBJ) $(LIBS) -o $(NAME) $(SDL_LINK)

$(DIR_OBJ)/%.o:$(DIR_SRC)/%.c $(HDR)
	$(CC) $(CFLAGS) -c $(INCLUDES) $< -o $@

$(LIBFT): FAKE
	@$(MAKE) -C $(LIBFT_DIR)/ --no-print-directory

$(FT_PRINTF): FAKE
	@$(MAKE) -C $(FT_PRINTF_DIR)/ --no-print-directory

clean :
	@/bin/rm -rf $(DIR_OBJ)
	@$(MAKE) -C $(LIBFT_DIR) clean
	@$(MAKE) -C $(FT_PRINTF_DIR) clean

fclean : clean
	@/bin/rm -f $(NAME) $(addprefix tests/test_,$(FILE_NAMES))
	@$(MAKE) -C $(LIBFT_DIR) fclean
	@$(MAKE) -C $(FT_PRINTF_DIR) fclean
	@/bin/rm -f $(addprefix tests/,$(TEST_NAMES))

re : fclean all

.PHONY: FAKE
