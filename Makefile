NAME=ft_ls

OS			:=	$(shell uname -s)
SRC			:=	main.c
HEADERS		:=  ft_ls.h
LIBFT		=	./libft/libft.a
LIBFT_DIR	=	./libft
INC_DIR		=	./includes
OBJ_DIR		=	./obj
SRC_DIR		=	./src

CC=gcc
CC_FLAGS=-Wall -Wextra -Werror

OBJ=$(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))
HEADERS_FILES=$(addprefix $(INC_DIR)/, $(HEADERS))
LIBS=-L$(LIBFT_DIR) -lft
INCLUDES=-I $(LIBFT_DIR) -I $(INC_DIR)
TEST_NAMES=
TEST_SRC:=$(shell find src/ -maxdepth 1 -type f \( -regex ".*\.c" ! -name "main.c" \))

all: $(NAME)

$(OBJ_DIR)/%.o:$(SRC_DIR)/%.c $(HEADERS_FILES)
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ -c $<

$(LIBFT): FAKE
	@$(MAKE) -C $(LIBFT_DIR)/ --no-print-directory

$(NAME): $(LIBFT) $(OBJ)
	$(info Compile $(NAME))
	@$(CC)  $(CC_FLAGS) -o $(NAME) $(OBJ) $(INCLUDES) $(LIBS);

clean :
	@/bin/rm -rf $(OBJ_DIR)
	@make clean -C $(info $(OS))$(LIBFT_DIR) --no-print-directory

fclean : clean
	@/bin/rm -f $(NAME) $(addprefix tests/test_,$(FILE_NAMES))
	@make fclean -C $(LIBFT_DIR) --no-print-directory
	@/bin/rm -f $(addprefix tests/,$(TEST_NAMES))

re : fclean all

test-all:
	@for s in $(TEST_NAMES) ; do \
		$(MAKE) test name=$$s --no-print-directory;\
	done

test: $(LIBFT)
	@gcc  $(CC_FLAGS) $(INCLUDES) $(TEST_SRC) tests/$(name).c $(LIBS) -o tests/$(name);
	$(info ************ $(name) *************)
	@tests/$(name)

.PHONY: FAKE
