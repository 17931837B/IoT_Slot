#include "../slot.h"

int	plot_reel1(t_param *param)
{
	int	i;
	int	j;
	int	k, l;
	int	o_x = HOUSING + 10;
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
		now_pos_s = count_time;
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
	int	o_x = 640;
	int	o_y = HOUSING;

	if (param->is_up_right || !reel[(H_REEL / MAG_RATE / 2 - (now_pos_r % REEL_Y) + REEL_Y) % REEL_Y][16])
		now_pos_r = count_time;
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