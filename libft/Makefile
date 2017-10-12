#!/usr/bin/make -f
NAME = libft.a
CC = gcc
CFLAGS = -Wall -Werror -Wextra
SRC = \
	memalloc\
	memset\
	putstr\
	putstr_fd\
	strlen
OBJ = $(patsubst %, ft_%.o, $(SRC))

all: $(NAME)

$(NAME): $(OBJ)
	@ar -rcs $@ $(OBJ)
	@echo "$(NAME) compiled."

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@ -I ./

clean:
	@rm -rf $(OBJ)

fclean: clean
	@rm -f $(NAME)
	@echo "$(NAME) removed."

re: fclean all
