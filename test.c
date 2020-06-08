#include <assert.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "libasm.h"

#define MAKEITABORT 0
// Globals
int g_all = 26, g_wr_all = 12, g_rd_all = 14;
int g_done = 0, g_fail = 0, g_wr = 0, g_rd = 0;
int wrfd = 0, rdfd = 0, rdfd_true = 0;
char	err_buff[1024];

void	__attribute__((destructor)) ft_destructor();

int		same_sign(int num1, int num2)
{
	return (((num1 == 0) == (num2 == 0)) && ((num1 < 0)  == (num2 < 0)));
}

void	done_on_all(char *str, int done, int all)
{
	char *color = (done == all ? "\e[0;92m" : "\e[0;91m");

	printf("\e[0;1;96m%s: %s%d\e[0;1m/\e[92m%d\e[0m\n", str, color, done, all);
}

void	ft_destructor(void)
{
	printf("\t\t\033[0;1;91mTESTS FINISHED!\n");
	done_on_all("Total", g_done - g_fail, g_all);
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

char	*tf_str(const int eq)
{
	return (eq ? "\e[0;92mTrue\e[0m" : "\e[0;91mFalse\e[0m");
}

void	truefalse(const int all_good, const int ret[2], const int err[2])
{
	g_done++;
	if (all_good) return ; g_fail++;

	int ret_eq = ret[0] == ret[1];
	int err_eq = err[0] == err[1];
	printf("\033[0;93m[%03d] " \
			"\033[0;95mReturn %s " \
			"\033[0;94mErrno %s : %s\n",
			g_done, tf_str(ret_eq), tf_str(err_eq), err_buff);
	if (!ret_eq)
		printf("Returned \e[91m%d\t\e[mExpected \e[92m%d\e[m\n", ret[0], ret[1]);
	if (!err_eq)
		printf("Errno is \e[91m%d\t\e[mExpected \e[92m%d\e[m\n", err[0], err[1]);
	printf("\n");
}

char	*which_fd(int fd)
{
	if (fd == 0) return ("stdin");
	if (fd == 1) return ("stdout");
	if (fd == 2) return ("stderr");
	if (fd == rdfd) return ("rdfd");
	if (fd == wrfd) return ("wrfd");
	return ("fakefd");
}

int		test_write(const int fd, const char * const str, const int size)
{
	int ret[2];
	int eq[2];
	int err[2];
	int all_good;

	errno = 0; bzero(err_buff, sizeof(err_buff));
	ret[0] = ft_write(fd, str, size);
	err[0] = errno; errno = 0;
	ret[1] = write(fd, str, size);
	err[1] = errno;
	eq[0] = (ret[0] == ret[1]); eq[1] = (err[0] == err[1]);
	if ((all_good = (eq[0] && eq[1] ? 1 : 0)))
		g_wr++;
	else
		sprintf(err_buff, "ft_write(%d[%s], '%s', %d)",
				fd, which_fd(fd), str, size);
	truefalse(all_good, ret, err);
	return (all_good);
}

int		test_read(const int fd_me, const int fd_true, const int size)
{
	char buf[2][1024];
	int err[2];
	int ret[2];
	int eq[2];
	int all_good;

	errno = 0; bzero(err_buff, sizeof(err_buff));
	bzero(buf[0], sizeof(buf[0]));
	bzero(buf[1], sizeof(buf[1]));
	ret[0] = ft_read(fd_me, buf[0], size);
	err[0] = errno; errno = 0;
	ret[1] = read(fd_true, buf[1], size);
	err[1] = errno;
	eq[0] = (ret[0] == ret[1]); eq[1] = (err[0] == err[1]);
	if ((all_good = (eq[0] && eq[1] && !strcmp(buf[0], buf[1]) ? 1 : 0)))
		g_rd++;
	else
		sprintf(err_buff, "ft_read(%d[%s], buff_eq:%s, %d)",
			fd_me, which_fd(fd_me), tf_str(all_good), size);
	truefalse(all_good, ret, err);
	return (all_good);
}

void	wr_tests(void)
{
	test_write(9, "Hello", 5);
	test_write(wrfd, "Hello!", 6);
	test_write(wrfd, NULL, 5);
	test_write(-1, NULL, 5);
	test_write(wrfd, "ABCEDFGEFGH", 9);
	test_write(9, "ABCEDFGEFGH", 9);
	test_write(wrfd, NULL, -1);
	test_write(wrfd, "A longer sentence!", 18);

	test_write(rdfd, "Hello!", 6);
	test_write(rdfd, NULL, 5);
	test_write(rdfd, NULL, -1);
	test_write(rdfd, "A longer sentence!", 18);
}

void	rd_tests(void)
{
	test_read(9, 9, 5);
	test_read(9, 9, 9);

	test_read(rdfd, rdfd_true, 5);
	test_read(rdfd, rdfd_true, 1);
	test_read(rdfd, rdfd_true, 9);
	test_read(rdfd, rdfd_true, 7);
	test_read(rdfd, rdfd_true, 18);
	test_read(rdfd, rdfd_true, 30);

	test_read(wrfd, wrfd, 5);
	test_read(wrfd, wrfd, 1);
	test_read(wrfd, wrfd, 9);
	test_read(wrfd, wrfd, 7);
	test_read(wrfd, wrfd, 18);
	test_read(wrfd, wrfd, 30);
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
//	if (!MAKEITABORT)
//		signal(SIGABRT, ft_signal);
	wr_tests();
	rd_tests();
}
