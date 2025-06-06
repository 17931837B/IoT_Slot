#include <stdio.h>
#include <sys/time.h>
#include <time.h>

time_t	get_time_in_ms(void)
{
	struct timeval		tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

long long get_time_in_ns(void)
{
	struct timespec	ts;

	clock_gettime(CLOCK_MONOTONIC, &ts);
	return ((long long)ts.tv_sec * 1000000000 + ts.tv_nsec);
}

int main(void) {

	time_t start_time = get_time_in_ns();
	int i = 0;
	while (i < 10000)
		i++;
	time_t end_time = get_time_in_ns();
	printf("%ld\n", end_time - start_time);
    return 0;
}