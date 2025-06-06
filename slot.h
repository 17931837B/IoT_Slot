#ifndef SLOT_H
# define SLOT_H

# include "./minilibx-linux/mlx.h"
# include <X11/X.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <time.h>

# define WIDTH 640
# define HEIGHT 320
# define HOUSING 30
# define LINE 5
# define SIZE 10
# define FPS 2000.0
# define ONE_SECONDS 1000000000LL

typedef struct s_img
{
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			size_line;
	int			endian;
	int			width;
	int			height;
} t_img;

typedef struct s_param
{
	void				*mlx;
	void				*win;
	t_img				img;
} t_param;

int		exit_param(t_param *param);
void	create_param(t_param *param);
unsigned int	rgb_num(int r, int g, int b);
void	paint_color(t_img *img, int x, int y, int color);
long long get_time_in_ns(void);

#endif