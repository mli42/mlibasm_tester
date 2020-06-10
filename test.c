#include "mlibasm.h"

t_tests	test[e_end];
int		wrfd = 0, rdfd = 0, rdfd_true = 0;
char	err_buff[1024];

void	__attribute__((constructor)) ft_constructor();
void	__attribute__((destructor)) ft_destructor();

void	ft_constructor(void)
{
	bzero(test, sizeof(test));
	test[TOTAL].fct_name = "TOTAL";
	test[WR].fct_name = "ft_write"; test[RD].fct_name = "ft_read";
	test[STRCMP].fct_name = "ft_strcmp"; test[STRCPY].fct_name = "ft_strcpy";
	test[STRLEN].fct_name = "ft_strlen"; test[STRDUP].fct_name = "ft_strdup";
}

void	ft_destructor(void)
{
	int i = -1;
	printf("\t\t\033[0;1;91mTESTS FINISHED!\n");
	while (++i < e_end)
		done_on_all(test[i].fct_name, test[i].done, test[i].all);

	close(wrfd);
	close(rdfd);
	close(rdfd_true);
	if (CHECKLEAKS)
		check_leaks();
}

void	truefalse(const int all_good, const int ret[2], const int err[2])
{
	test[TOTAL].all++;
	if (all_good) {test[TOTAL].done++; return ;}

	int ret_eq = ret[0] == ret[1];
	int err_eq = err[0] == err[1];
	printf("\033[0;93m[%03d] " \
			"\033[0;95mReturn %s " \
			"\033[0;94mErrno %s : %s\n",
			test[TOTAL].all, tf_str(ret_eq), tf_str(err_eq), err_buff);
	if (!ret_eq)
		printf("Returned \e[91m%d\t\e[mExpected \e[92m%d\e[m\n", ret[0], ret[1]);
	if (!err_eq)
		printf("Errno is \e[91m%d\t\e[mExpected \e[92m%d\e[m\n", err[0], err[1]);
	printf("\n");
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
	strcpy_tests();
}
