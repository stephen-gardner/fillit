#!/usr/bin/make -f
NAME = fillit
CC = gcc
CFLAGS = -Wall -Werror -Wextra -I libft 
LIBFT = libft/libft.a
SRC = \
	fillit\
	load\
	map\
	solve\
	verify
OBJ = $(patsubst %, %.o, $(SRC))

all: $(NAME)

$(NAME): $(LIBFT) $(OBJ)
	@echo "Building $@..."
	@$(CC) $(CFLAGS) $(LIBFT) $(OBJ) -o $@
	@echo "Done."

$(LIBFT):
	@echo "Building $@..."
	@make -C libft

%.o: %.c
	@echo "Compiling $<..."
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -rf $(OBJ)
	@make -C libft clean
	@echo "Object files removed."

fclean: clean
	@rm -f $(NAME)
	@make -C libft fclean
	@echo "$(NAME) removed."

re: fclean all
