NAME	=	cub3D
CC		=	cc
CFLAGS	=	-Wall -Werror -Wextra
MATH_FLAGS	=	-lm

OBJ_DIR	=	obj
SRC_DIR	=	src
INC_DIR	=	include
LIB_DIR	=	libft
LIBFT	=	$(LIB_DIR)/libft.a

SRC = \
	$(SRC_DIR)/main.c \
	$(SRC_DIR)/error/error.c \
	$(SRC_DIR)/init/check_input.c \
	$(SRC_DIR)/init/init.c \
	$(SRC_DIR)/parsing/map.c


OBJ = $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

all: $(LIBFT) $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -o $(NAME) $(MATH_FLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -I$(INC_DIR) -I$(LIB_DIR) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(LIBFT):
	$(MAKE) -C $(LIB_DIR)

clean:
	rm -rf $(OBJ_DIR)
	$(MAKE) -C $(LIB_DIR) clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIB_DIR) fclean

re: fclean all

.PHONY: all clean fclean re