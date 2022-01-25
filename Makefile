SRC=main.c math.c util.c transform.c img.c matrix.c render.c mouse.c vector.c \
	get_next_line/get_next_line.c get_next_line/get_next_line_utils.c
OBJ=$(SRC:.c=.o)
CFLAGS=-Wall -Wextra -Werror -O3 -flto -march=native -DBUFFER_SIZE=1024
NAME=fdf

all: $(NAME)

$(NAME): $(OBJ) mlx/libmlx.a libft/libft.a
	$(CC) $(CFLAGS) -o $@ $^ -framework OpenGL -framework AppKit

%.o: %.c
	$(CC) $(CFLAGS) -o $@ $< -c

mlx/libmlx.a:
	make -C mlx CFLAGS="-DGL_SILENCE_DEPRECATION -Wno-deprecated-declarations"

libft/libft.a:
	make -C libft CFLAGS="-O3 -flto -march=native"

clean:
	rm -f $(OBJ)
	make -C mlx clean
	make -C libft fclean

fclean: clean
	rm -f $(NAME)

norm:
	norminette *.c *.h libft/*.c libft/*.h get_next_line/*.c get_next_line/*.h

re: fclean all
