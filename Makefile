SRC=main.c math.c util.c transform.c img.c matrix.c
OBJ=$(SRC:.c=.o)
CFLAGS=-Wall -Wextra -Werror -Og -g -fsanitize=address
NAME=fdf

all: $(NAME)

$(NAME): $(OBJ) mlx/libmlx.a libft/libft.a
	$(CC) $(CFLAGS) -o $@ $^ -framework OpenGL -framework AppKit

%.o: %.c $(INC)
	$(CC) $(CFLAGS) -o $@ $< -c

mlx/libmlx.a:
	make -C mlx

libft/libft.a:
	make -C libft

clean:
	rm -f $(OBJ)
	make -C mlx clean
	make -C libft clean

fclean: clean
	rm -f $(NAME)
	make -C libft fclean

re: fclean all
