#ifndef SLOT_H
# define SLOT_H

# include "./minilibx-linux/mlx.h"
# include <X11/X.h>
# include <stdlib.h>
# include <unistd.h>

# define WIDTH 640
# define HEIGHT 320
# define HOUSING 30
# define LINE 5
# define SIZE 10

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

#endif