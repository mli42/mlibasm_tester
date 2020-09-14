#include "mlibasm.h"

t_tests	test[e_end];
int		wrfd = 0, rdfd = 0, rdfd_true = 0;
char	err_buff[1024];
extern int g_fct;
int		fct_check_leaks = 0;

void	__attribute__((constructor)) ft_constructor();
void	__attribute__((destructor)) ft_destructor();

void	ft_constructor(void)
{
	if ((wrfd = open("output", O_WRONLY | O_CREAT,
					S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)) < 0)
		exit (1);
	if ((rdfd = open("output", O_RDONLY)) < 0)
		exit (1);
	if ((rdfd_true = open("output", O_RDONLY)) < 0)
		exit (1);
	bzero(test, sizeof(test));
	test[TOTAL].fct_name = "TOTAL";
	test[WR].fct_name = "ft_write"; test[RD].fct_name = "ft_read";
	test[STRCMP].fct_name = "ft_strcmp"; test[STRCPY].fct_name = "ft_strcpy";
	test[STRLEN].fct_name = "ft_strlen"; test[STRDUP].fct_name = "ft_strdup";

	test[ATOI_BASE].fct_name = "ft_atoi_base";
	test[LIST_PUSH_FRONT].fct_name = "ft_list_push_front";
	test[LIST_REMOVE_IF].fct_name = "ft_list_remove_if";
	test[LIST_SIZE].fct_name = "ft_list_size"; test[LIST_SORT].fct_name = "ft_list_sort";
}

void	ft_destructor(void)
{
	done_on_all(test[g_fct].fct_name, test[g_fct].done, test[g_fct].all);

	close(wrfd);
	close(rdfd);
	close(rdfd_true);
	if (CHECKLEAKS && fct_check_leaks)
	{
		printf("\n\e[93mWhat about %s's LEAKS ?!\e[0m\n\n", test[g_fct].fct_name); 
		check_leaks();
	}
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
