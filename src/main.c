#include "../slot.h"
#include "../reel.h"

long long current_time;
long long last_time;
long long count_time = 0;

void	plot_reel(t_param *param)
{
	int	i;
	int	j;
	int	k, l;
	int	o_x = HOUSING + 10;
	int	o_y = HOUSING;
	// int	o_y = count_time;

	i = 0;
	while (i < H_REEL / MAG_RATE)
	{
		j = 0;
		while (j < REEL_X)
		{
			l = 0;
			while (l < MAG_RATE)
			{
				k = 0;
				while (k < REEL_X)
				{
					if (reel[(i - (count_time % REEL_Y) + REEL_Y) % REEL_Y][j] == 2)
						paint_color(&param->img, o_x + j * MAG_RATE + k, o_y + i * MAG_RATE + l, rgb_num(255, 0, 0));
					else if (reel[(i - (count_time % REEL_Y) + REEL_Y) % REEL_Y][j] == 1)
						paint_color(&param->img, o_x + j * MAG_RATE + k, o_y + i * MAG_RATE + l, rgb_num(0, 0, 0));
					else if (reel[(i - (count_time % REEL_Y) + REEL_Y) % REEL_Y][j] == 3)
						paint_color(&param->img, o_x + j * MAG_RATE + k, o_y + i * MAG_RATE + l, rgb_num(255, 255, 0));
					else if (reel[(i - (count_time % REEL_Y) + REEL_Y) % REEL_Y][j] == 4)
						paint_color(&param->img, o_x + j * MAG_RATE + k, o_y + i * MAG_RATE + l, rgb_num(0, 255, 0));
					k++;
				}
				l++;
			}
			j++;
		}
		i++;
	}
}

static int	main_loop(t_param *param)
{
	int	x;
	int	y;

	current_time = get_time_in_ns();
	if (current_time - last_time > ONE_SECONDS / FPS)
	{
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
				x++;
			}
			y++;
		}
		plot_reel1(param);
		mlx_put_image_to_window(param->mlx, param->win, param->img.img, 0, 0);
		count_time++;
		last_time = current_time;
	}
	// count_time++;
	printf("%lld\n", count_time % HEIGHT);
	return (0);
}

int main(void)
{
	t_param	param;

	create_param(&param);
	// mlx_hook(param.win, KeyPress, KeyPressMask, key_press_hook, &param);
	mlx_hook(param.win, ClientMessage, StructureNotifyMask, exit_param, &param);
	mlx_loop_hook(param.mlx, &main_loop, &param);
	last_time = get_time_in_ns();
	mlx_loop(param.mlx);
	return (0);
}	