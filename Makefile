SRC=main.c math.c util.c transform.c img.c
OBJ=$(SRC:.c=.o)
CFLAGS=-Wall -Wextra -Werror -Og -g -fsanitize=address
NAME=fdf

all: $(NAME)

$(NAME): $(OBJ) mlx/libmlx.a
	$(CC) $(CFLAGS) -o $@ $^ -framework OpenGL -framework AppKit

%.o: %.c $(INC)
	$(CC) $(CFLAGS) -o $@ $< -c

mlx/libmlx.a:
	make -C libmlx

clean:
	rm -f $(OBJ)
	make -C liblx clean

fclean: clean
	rm -f $(NAME)

re: fclean all
