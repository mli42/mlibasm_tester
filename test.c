#include <assert.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "libasm.h"

#define MAKEITABORT 0
// Globals
int g_all = 26, g_wr_all = 12, g_rd_all = 14;
int g_done = 0, g_wr = 0, g_rd = 0;
int wrfd = 0, rdfd = 0, rdfd_true = 0;

void	__attribute__((destructor)) ft_destructor();

int		same_sign(int num1, int num2)
{
	return (((num1 == 0) == (num2 == 0)) && ((num1 < 0)  == (num2 < 0)));
}

void	done_on_all(char *str, int done, int all)
{
	char *color = (done == all ? "\e[0;92m" : "\e[0;91m");

	printf("\e[0;96m%s: %s%d\e[0;1m/\e[92m%d\e[0m\n", str, color, done, all);
}

void	ft_destructor(void)
{
	printf("\n");
	printf("\033[0;94mTests finished!\n");
	done_on_all("Total", g_done, g_all);
	done_on_all("ft_write", g_wr, g_wr_all);
	done_on_all("ft_read", g_rd, g_rd_all);

	close(wrfd);
	close(rdfd);
	close(rdfd_true);
}

void	ft_signal(int sign)
{
	(void)sign;
	exit(1);
}

void	truefalse(const int eq[2])
{
	printf("\033[0;93m[%03d] " \
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

int		test_read(const int fd_me, const int fd_true, const int size)
{
	char buf[2][1024];
	int err;
	int ret[2];
	int eq[2];

	errno = 0;
	bzero(buf[0], sizeof(buf[0]));
	bzero(buf[1], sizeof(buf[1]));
	ret[0] = ft_read(fd_me, buf[0], size);
	err = errno;
	ret[1] = read(fd_true, buf[1], size);
	eq[0] = (ret[0] == ret[1]); eq[1] = (err == errno);
	truefalse(eq);
	g_rd++;
	return (eq[0] && eq[1] && !strcmp(buf[0], buf[1]) ? 1 : 0);
}

void	wr_tests(void)
{
	assert(test_write(9, "Hello", 5));
	assert(test_write(wrfd, "Hello\n", 6));
	assert(test_write(wrfd, NULL, 5));
	assert(test_write(-1, NULL, 5));
	assert(test_write(wrfd, "ABCEDFGEFGH", 9));
	assert(test_write(9, "ABCEDFGEFGH", 9));
	assert(test_write(wrfd, NULL, -1));
	assert(test_write(wrfd, "A longer sentence\n", 18));

	assert(test_write(rdfd, "Hello\n", 6));
	assert(test_write(rdfd, NULL, 5));
	assert(test_write(rdfd, NULL, -1));
	assert(test_write(rdfd, "A longer sentence\n", 18));
}

void	rd_tests(void)
{
	assert(test_read(9, 9, 5));
	assert(test_read(9, 9, 9));

	assert(test_read(rdfd, rdfd_true, 5));
	assert(test_read(rdfd, rdfd_true, 1));
	assert(test_read(rdfd, rdfd_true, 9));
	assert(test_read(rdfd, rdfd_true, 7));
	assert(test_read(rdfd, rdfd_true, 18));
	assert(test_read(rdfd, rdfd_true, 30));

	assert(test_read(wrfd, wrfd, 5));
	assert(test_read(wrfd, wrfd, 1));
	assert(test_read(wrfd, wrfd, 9));
	assert(test_read(wrfd, wrfd, 7));
	assert(test_read(wrfd, wrfd, 18));
	assert(test_read(wrfd, wrfd, 30));
}

static int	init(void)
{
	if ((wrfd = open("output", O_WRONLY | O_CREAT | O_TRUNC,
					S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)) < 0)
		return (0);
	if ((rdfd = open("output", O_RDONLY)) < 0)
		return (0);
	if ((rdfd_true = open("output", O_RDONLY)) < 0)
		return (0);
	return (1);
}

int		main(void)
{
	if (!init())
	{
		perror("Couldn't init tester");
		exit(1);
	}
	if (!MAKEITABORT)
		signal(SIGABRT, ft_signal);
	wr_tests();
	rd_tests();
}
