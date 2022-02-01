SRC=main.c math.c util.c transform.c img.c matrix.c \
	render.c mouse.c vector.c keyboard.c clip.c \
	get_next_line/get_next_line.c get_next_line/get_next_line_utils.c
OBJ=$(SRC:.c=.o)
OPTARGS=-Ofast -flto -march=native
#OPTARGS=-Og -g -fsanitize=address
CFLAGS=-Wall -Wextra -Werror $(OPTARGS) -DBUFFER_SIZE=1048576
NAME=fdf
INC=fdf.h

all: $(NAME)

$(NAME): $(OBJ) mlx/libmlx.a libft/libft.a
	$(CC) $(CFLAGS) -o $@ $^ -framework OpenGL -framework AppKit

%.o: %.c $(INC)
	$(CC) $(CFLAGS) -o $@ $< -c -ansi -pedantic

mlx/libmlx.a:
	make -C mlx CFLAGS="-DGL_SILENCE_DEPRECATION -Wno-deprecated-declarations"

libft/libft.a:
	make -C libft CFLAGS="$(OPTARGS)"

clean:
	rm -f $(OBJ)
	make -C mlx clean
	make -C libft fclean

fclean: clean
	rm -f $(NAME)

norm:
	norminette *.c *.h libft/*.c libft/*.h get_next_line/*.c get_next_line/*.h

re: fclean all
