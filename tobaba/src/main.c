#include "../slot.h"
#include "../reel.h"

long long current_time;
long long last_time;
long long count_time = 0;
int	now_pos_l = 0;
int	now_pos_r = 0;
int	now_pos_s = 0;

int	plot_reel1(t_param *param)
{
	int	i;
	int	j;
	int	k, l;
	int	o_x = HOUSING + 15;
	int	o_y = HOUSING;

	if (param->is_up_left || !reel[(H_REEL / MAG_RATE / 2 - (now_pos_l % REEL_Y) + REEL_Y) % REEL_Y][16])
		now_pos_l = count_time;
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
					if (reel[(i - (now_pos_l % REEL_Y) + REEL_Y) % REEL_Y][j] == 2)
						paint_color(&param->img, o_x + j * MAG_RATE + k, o_y + i * MAG_RATE + l, rgb_num(255, 0, 0));
					else if (reel[(i - (now_pos_l % REEL_Y) + REEL_Y) % REEL_Y][j] == 1)
						paint_color(&param->img, o_x + j * MAG_RATE + k, o_y + i * MAG_RATE + l, rgb_num(0, 0, 0));
					else if (reel[(i - (now_pos_l % REEL_Y) + REEL_Y) % REEL_Y][j] == 3)
						paint_color(&param->img, o_x + j * MAG_RATE + k, o_y + i * MAG_RATE + l, rgb_num(255, 255, 0));
					else if (reel[(i - (now_pos_l % REEL_Y) + REEL_Y) % REEL_Y][j] == 4)
						paint_color(&param->img, o_x + j * MAG_RATE + k, o_y + i * MAG_RATE + l, rgb_num(0, 255, 0));
					else if (param->role[0] == param->role[1] && param->role[1] == param->role[2] && param->role[0] != 0 && count_time % 20 >= 10)
					{
						if (count_time % 30 >= 20)
							paint_color(&param->img, o_x + j * MAG_RATE + k, o_y + i * MAG_RATE + l, rgb_num(180, 240, 0));
						else if (count_time % 30 >= 10)
							paint_color(&param->img, o_x + j * MAG_RATE + k, o_y + i * MAG_RATE + l, rgb_num(180, 240, 0));
						else
							paint_color(&param->img, o_x + j * MAG_RATE + k, o_y + i * MAG_RATE + l, rgb_num(255, 0, 255));
					}
					k++;
				}
				l++;
			}
			j++;
		}
		i++;
	}
	if (param->is_up_left)
		return (0);
	else
		return (reel[(H_REEL / MAG_RATE / 2 - (now_pos_l % REEL_Y) + REEL_Y) % REEL_Y][16]);
}

int	plot_reel2(t_param *param)
{
	int	i;
	int	j;
	int	k, l;
	int	o_x = 360;
	int	o_y = HOUSING;

	if (param->is_up_senter || !reel[(H_REEL / MAG_RATE / 2 - (now_pos_s % REEL_Y) + REEL_Y) % REEL_Y][16])
		now_pos_s = count_time + 10;
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
					if (reel[(i - (now_pos_s % REEL_Y) + REEL_Y) % REEL_Y][j] == 2)
						paint_color(&param->img, o_x + j * MAG_RATE + k, o_y + i * MAG_RATE + l, rgb_num(255, 0, 0));
					else if (reel[(i - (now_pos_s % REEL_Y) + REEL_Y) % REEL_Y][j] == 1)
						paint_color(&param->img, o_x + j * MAG_RATE + k, o_y + i * MAG_RATE + l, rgb_num(0, 0, 0));
					else if (reel[(i - (now_pos_s % REEL_Y) + REEL_Y) % REEL_Y][j] == 3)
						paint_color(&param->img, o_x + j * MAG_RATE + k, o_y + i * MAG_RATE + l, rgb_num(255, 255, 0));
					else if (reel[(i - (now_pos_s % REEL_Y) + REEL_Y) % REEL_Y][j] == 4)
						paint_color(&param->img, o_x + j * MAG_RATE + k, o_y + i * MAG_RATE + l, rgb_num(0, 255, 0));
					else if (param->role[0] == param->role[1] && param->role[1] == param->role[2] && param->role[0] != 0 && count_time % 20 >= 10)
					{
						if (count_time % 30 >= 20)
							paint_color(&param->img, o_x + j * MAG_RATE + k, o_y + i * MAG_RATE + l, rgb_num(180, 240, 0));
						else if (count_time % 30 >= 10)
							paint_color(&param->img, o_x + j * MAG_RATE + k, o_y + i * MAG_RATE + l, rgb_num(255, 0, 255));
						else
							paint_color(&param->img, o_x + j * MAG_RATE + k, o_y + i * MAG_RATE + l, rgb_num(180, 240, 0));
					}
					k++;
				}
				l++;
			}
			j++;
		}
		i++;
	}
	if (param->is_up_senter)
		return (0);
	else
		return (reel[(H_REEL / MAG_RATE / 2 - (now_pos_s % REEL_Y) + REEL_Y) % REEL_Y][16]);
}

int	plot_reel3(t_param *param)
{
	int	i;
	int	j;
	int	k, l;
	int	o_x = 660;
	int	o_y = HOUSING;

	if (param->is_up_right || !reel[(H_REEL / MAG_RATE / 2 - (now_pos_r % REEL_Y) + REEL_Y) % REEL_Y][16])
		now_pos_r = count_time + 20;
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
					if (reel[(i - (now_pos_r % REEL_Y) + REEL_Y) % REEL_Y][j] == 2)
						paint_color(&param->img, o_x + j * MAG_RATE + k, o_y + i * MAG_RATE + l, rgb_num(255, 0, 0));
					else if (reel[(i - (now_pos_r % REEL_Y) + REEL_Y) % REEL_Y][j] == 1)
						paint_color(&param->img, o_x + j * MAG_RATE + k, o_y + i * MAG_RATE + l, rgb_num(0, 0, 0));
					else if (reel[(i - (now_pos_r % REEL_Y) + REEL_Y) % REEL_Y][j] == 3)
						paint_color(&param->img, o_x + j * MAG_RATE + k, o_y + i * MAG_RATE + l, rgb_num(255, 255, 0));
					else if (reel[(i - (now_pos_r % REEL_Y) + REEL_Y) % REEL_Y][j] == 4)
						paint_color(&param->img, o_x + j * MAG_RATE + k, o_y + i * MAG_RATE + l, rgb_num(0, 255, 0));
					else if (param->role[0] == param->role[1] && param->role[1] == param->role[2] && param->role[0] != 0 && count_time % 20 >= 10)
					{
						if (count_time % 30 >= 20)
							paint_color(&param->img, o_x + j * MAG_RATE + k, o_y + i * MAG_RATE + l, rgb_num(255, 0, 255));
						else if (count_time % 30 >= 10)
							paint_color(&param->img, o_x + j * MAG_RATE + k, o_y + i * MAG_RATE + l, rgb_num(180, 240, 0));
						else
							paint_color(&param->img, o_x + j * MAG_RATE + k, o_y + i * MAG_RATE + l, rgb_num(180, 240, 0));
					}
					k++;
				}
				l++;
			}
			j++;
		}
		i++;
	}
	if (param->is_up_right)
		return (0);
	else
		return (reel[(H_REEL / MAG_RATE / 2 - (now_pos_r % REEL_Y) + REEL_Y) % REEL_Y][16]);
}

static int	main_loop(t_param *param)
{
	int	x;
	int	y;
	int	role[3];

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
				else if (y == HEIGHT / 2)
					paint_color(&param->img, x, y, rgb_num(255, 0, 0));
				else if (!((WIDTH - 2 * (HOUSING + LINE)) / 3 + HOUSING <= x && x < (WIDTH - 2 * (HOUSING + LINE)) / 3 + HOUSING + LINE) && !((WIDTH - 2 * (HOUSING + LINE)) * 2 / 3 + HOUSING + LINE <= x && x < (WIDTH - 2 * (HOUSING + LINE)) * 2 / 3 + HOUSING + 2 * LINE))
					paint_color(&param->img, x, y, rgb_num(255, 255, 255));
				x++;
			}
			y++;
		}
		param->role[0] = plot_reel1(param);
		param->role[1] = plot_reel2(param);
		param->role[2] = plot_reel3(param);
		// printf("%d, %d, %d\n", role[0], role[1], role[2]);
		mlx_put_image_to_window(param->mlx, param->win, param->img.img, 0, 0);
		count_time++;
		last_time = current_time;
	}
	return (0);
}

int main(void)
{
	t_param	param;

	create_param(&param);
	mlx_hook(param.win, KeyPress, KeyPressMask, key_press_hook, &param);
	mlx_hook(param.win, ClientMessage, StructureNotifyMask, exit_param, &param);
	mlx_loop_hook(param.mlx, &main_loop, &param);
	last_time = get_time_in_ns();
	mlx_loop(param.mlx);
	return (0);
}	