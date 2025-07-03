NAME			= sloT
SOCEDS_DEST_ROOT = /mnt/c/intelFPGA/22.1/embedded
SRCS			= ./src/main.c ./src/param_utils.c ./src/utils.c ./src/mlx_hook.c
OBJS			= $(SRCS:.c=.o)
CROSS_COMPILE	= arm-linux-gnueabihf-
CFLAGS			= -Dsoc_cv_av -static -g -Wall  -I${SOCEDS_DEST_ROOT}/ip/altera/hps/altera_hps/hwlib/include -I${SOCEDS_DEST_ROOT}/ip/altera/hps/altera_hps/hwlib/include/soc_cv_av
LDFLAGS			= -g -Wall 
CC				= $(CROSS_COMPILE)gcc
MLXDIR			= ./minilibx-linux
LIB_MLX			= $(MLXDIR)/libmlx.a
LIBX_FLAGS		= $(LIB_MLX) -lXext -lX11 -lm -L/usr/lib -L$(MLXDIR)/obj 
ARCH= arm

all:		$(NAME)

$(NAME):	$(OBJS)
			$(MAKE) -C minilibx-linux
			$(CC) $(LDFLAGS) $(CFLAGS) $(OBJS) $(LIBX_FLAGS) -o $(NAME)

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
