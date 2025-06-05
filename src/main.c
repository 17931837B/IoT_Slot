#include "../slot.h"

unsigned int	rgb_num(int r, int g, int b)
{
	unsigned int	res;

	res = r * 65536 + g * 256 + b;
	return (res);
}

void	paint_color(t_img *img, int x, int y, int color)
{
	char	*pos;

	pos = img->addr + (y * img->size_line
			+ x * (img->bits_per_pixel / 8));
	*(unsigned int *)pos = color;
}

void	plot_reel(t_param *param, int x, int y)
{
	static int	one[5][3] = {
		{1,1,1},
		{1,0,1},
		{0,0,1},
		{0,0,1},
		{0,0,1}
	};

	if (80 <= x && x < 90 && 105 <= y && y < 115)
		paint_color(&param->img, x, y, rgb_num(0, 0, 0));
	else if (80 <= x && x < 90 && 115 <= y && y < 125)
		paint_color(&param->img, x, y, rgb_num(0, 0, 0));
	else if (90 <= x && x < 100 && 105 <= y && y < 115)
		paint_color(&param->img, x, y, rgb_num(0, 0, 0));
	else if (100 <= x && x < 110 && 105 <= y && y < 115)
		paint_color(&param->img, x, y, rgb_num(0, 0, 0));
	else if (100 <= x && x < 110 && 115 <= y && y < 125)
		paint_color(&param->img, x, y, rgb_num(0, 0, 0));
	else if (100 <= x && x < 110 && 125 <= y && y < 135)
		paint_color(&param->img, x, y, rgb_num(0, 0, 0));
	else if (100 <= x && x < 110 && 135 <= y && y < 145)
		paint_color(&param->img, x, y, rgb_num(0, 0, 0));
	else if (100 <= x && x < 110 && 145 <= y && y < 155)
		paint_color(&param->img, x, y, rgb_num(0, 0, 0));
}

static int	main_loop(t_param *param)
{
	int	x;
	int	y;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			if (x < HOUSING || WIDTH - HOUSING < x || y < HOUSING || HEIGHT - HOUSING < y)
				paint_color(&param->img, x, y, rgb_num(255, 0, 0));
			else if (!((WIDTH - 2 * (HOUSING + LINE)) / 3 + HOUSING <= x && x < (WIDTH - 2 * (HOUSING + LINE)) / 3 + HOUSING + LINE) && !((WIDTH - 2 * (HOUSING + LINE)) * 2 / 3 + HOUSING + LINE <= x && x < (WIDTH - 2 * (HOUSING + LINE)) * 2 / 3 + HOUSING + 2 * LINE))
				paint_color(&param->img, x, y, rgb_num(255, 255, 255));
			plot_reel(param, x, y);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(param->mlx, param->win, param->img.img, 0, 0);
	return (0);
}

int main(void)
{
	t_param	param;

	create_param(&param);
	// mlx_hook(param.win, KeyPress, KeyPressMask, key_press_hook, &param);
	mlx_hook(param.win, ClientMessage, StructureNotifyMask, exit_param, &param);
	mlx_loop_hook(param.mlx, &main_loop, &param);
	mlx_loop(param.mlx);
}	