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

long long get_time_in_ns(void)
{
	struct timespec	ts;

	clock_gettime(CLOCK_MONOTONIC, &ts);
	return ((long long)ts.tv_sec * 1000000000 + ts.tv_nsec);
}