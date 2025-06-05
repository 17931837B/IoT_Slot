#include "../slot.h"

int	exit_param(t_param *param)
{
	mlx_destroy_window(param->mlx, param->win);
	exit(0);
}

void	create_param(t_param *param)
{
	param->mlx = mlx_init();
	if (param->mlx == NULL)
		exit(1);
	param->win = mlx_new_window(param->mlx, WIDTH, HEIGHT, "Casino sloT");
	param->img.img = mlx_new_image(param->mlx, WIDTH, HEIGHT);
	param->img.addr = mlx_get_data_addr(param->img.img,
			&param->img.bits_per_pixel,
			&param->img.size_line, &param->img.endian);
}