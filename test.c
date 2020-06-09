#include "mlibasm_test.h"

// Globals
int g_all = 26, g_wr_all = 12, g_rd_all = 14, g_strcmp_all = 0;
int g_done = 0, g_fail = 0, g_wr = 0, g_rd = 0, g_strcmp = 0;
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
	done_on_all("ft_strcmp", g_strcmp, g_strcmp_all);

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
	strcmp_tests();
}
