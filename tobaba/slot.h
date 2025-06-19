#ifndef SLOT_H
# define SLOT_H

# include "./minilibx-linux/mlx.h"
# include <X11/X.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <time.h>
# include <stdbool.h>

# define WIDTH 960
# define HEIGHT 360
# define HOUSING 30
# define LINE 5
# define SIZE 10
# define FPS 32.0
# define ONE_SECONDS 1000000000LL
# define W_REEL (WIDTH - 2 * (HOUSING + LINE))
# define H_REEL (HEIGHT - 2 * HOUSING)
# define PLOT_W (W_REEL / 16)
# define MAG_RATE 15

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
	bool				is_up_left;
	bool				is_up_right;
	bool				is_up_senter;
	int					role[3];
} t_param;

int		exit_param(t_param *param);
void	create_param(t_param *param);
unsigned int	rgb_num(int r, int g, int b);
void	paint_color(t_img *img, int x, int y, int color);
long long get_time_in_ns(void);
int	key_press_hook(int keycode, t_param *param);

#endif