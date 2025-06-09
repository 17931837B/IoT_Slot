#include "../slot.h"

int	key_press_hook(int keycode, t_param *param)
{
	if (keycode == 65307) //esc
		exit_param(param);
	if (keycode == 65363) //right
	{
		if (param->is_up_right)
			param->is_up_right = false;
		else
			param->is_up_right = true;
	}
	if (keycode == 65361) //left
	{
		if (param->is_up_left)
			param->is_up_left = false;
		else
			param->is_up_left = true;
	}
	if (keycode == 65362) //up
	{
		if (param->is_up_senter)
			param->is_up_senter = false;
		else
			param->is_up_senter = true;
	}
	if (keycode == 65364) //down
	{
		param->is_up_right = true;
		param->is_up_left = true;
		param->is_up_senter = true;
	}
	return (0);
}