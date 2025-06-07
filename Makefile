NAME	=	sloT
SRCS	=	./src/main.c ./src/param_utils.c ./src/utils.c ./src/mlx_hook.c
OBJS	=	$(SRCS:.c=.o)
CC		=	cc
MLXDIR	= ./minilibx-linux
LIB_MLX	= $(MLXDIR)/libmlx.a
LIBX_FLAGS = $(LIB_MLX) -lXext -lX11 -lm -L/usr/lib -L$(MLXDIR)/obj 

all:		$(NAME)

$(NAME):	$(OBJS)
			$(MAKE) -C minilibx-linux
			$(CC) $(OBJS) $(LIBX_FLAGS) -o $(NAME)

clean:
			$(RM) $(OBJS)

fclean:		clean
			$(RM) $(NAME)

git:
			git clone git@github.com:42Paris/minilibx-linux.git minilibx-linux

rm:
			rm -rf minilibx-linux

re:			fclean all

.PHONY:		all clean fclean re
