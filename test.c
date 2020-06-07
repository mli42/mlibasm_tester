#include <assert.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "libasm.h"

#define MAKEITABORT 0
// Globals
int g_all = 2, g_done = 0, g_wr = 0, g_rd = 0;
int fd;

void	__attribute__((destructor)) ft_destructor();

void	ft_destructor(void)
{
	printf("\n");
	printf("\033[0;94mTests finished!\n");
	printf("\033[0;96mTotal:\033[0;91m%d\033[0;1m/\033[92m%d\n", g_done, g_all);
	printf("\033[0;96mft_write: \033[92m%d\n", g_wr);
	printf("\033[0;96mft_read: \033[92m%d\n", g_rd);

	printf("\033[0m");
	close(fd);
}

void	ft_signal(int sign)
{
	(void)sign;
	exit(1);
}

void	truefalse(const int eq[2])
{
	printf("\033[0;93m[%d]" \
			"\033[0;95mReturn \033[0;%s " \
			"\033[0;94mErrno \033[0;%s\033[0m\n", ++g_done,
			eq[0] ? "92mTrue" : "91mFalse", eq[1] ? "92mTrue" : "91mFalse");
}

int		test_write(const int fd, const char * const str, const int size)
{
	int err;
	int ret[2];
	int eq[2];

	errno = 0;
	ret[0] = ft_write(fd, str, size);
	err = errno;
	ret[1] = write(fd, str, size);
	eq[0] = ret[0] == ret[1]; eq[1] = err == errno;
	truefalse(eq);
	g_wr++;
	return (eq[0] && eq[1] ? 1 : 0);
}

int		test_read(const int fd, const int size)
{
	char buf[2][1024];
	int err;
	int ret[2];
	int eq[2];

	errno = 0;
	bzero(buf[0], sizeof(buf[0]));
	bzero(buf[1], sizeof(buf[1]));
	ret[0] = ft_read(fd, buf[0], size);
	err = errno;
	ret[1] = read(fd, buf[1], size);
	eq[0] = (ret[0] == ret[1]); eq[1] = (err == errno);
	truefalse(eq);
	g_rd++;
	return (eq[0] && eq[1] && !strcmp(buf[0], buf[1]) ? 1 : 0);
}

void	wr_tests(void)
{
	assert(test_write(9, "Hello", 5));
	assert(test_write(fd, "Hello\n", 6));
	assert(test_write(fd, NULL, 5));
	assert(test_write(-1, NULL, 5));
	assert(test_write(fd, "ABCEDFGEFGH", 9));
	assert(test_write(9, "ABCEDFGEFGH", 9));
	assert(test_write(fd, NULL, -1));
	assert(test_write(fd, "A longer sentence\n", 18));
}

void	rd_tests(void)
{
	assert(test_read(9, 5));
	assert(test_read(9, 9));
	assert(test_read(fd, 5));
	assert(test_read(fd, 1));
	assert(test_read(fd, 9));
	assert(test_read(fd, 7));
	assert(test_read(fd, 18));
}

int		main(void)
{
	if ((fd = open("output", O_WRONLY | O_CREAT | O_TRUNC,
					S_IRWXU | S_IRGRP | S_IROTH)) < 0)
	{
		perror(NULL);
		exit (1);
	}
	if (!MAKEITABORT)
		signal(SIGABRT, ft_signal);
	wr_tests();
	rd_tests();
}
