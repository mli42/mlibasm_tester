/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_sort.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mli <mli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/27 15:15:24 by mli               #+#    #+#             */
/*   Updated: 2021/04/09 17:07:28 by mli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlibasm.h"

int g_fct = LIST_SORT;

int		test_list_sort(t_list *lst, t_list *good, int (*cmp)())
{
	int err[2];
	int eq[2];
	int ret[2];
	int all_good;

	errno = 0; bzero(err_buff, sizeof(err_buff)); test[LIST_SORT].all++;
	ret[0] = 0;
	ft_list_sort(&lst, cmp);
	err[0] = errno; errno = 0;
	ret[1] = ft_lstcmp(lst, good);
	err[1] = errno;
	eq[0] = (ret[0] == ret[1]); eq[1] = (err[0] == err[1]);
	if ((all_good = (eq[0] && eq[1] ? 1 : 0)))
		test[LIST_SORT].done++;
	else
		sprintf(err_buff, "ft_list_sort()");
	truefalse(all_good, ret, err);
	if (!all_good)
	{
		printf("Has : ");
		ft_print_list(lst);
		printf("Expected : ");
		ft_print_list(good);
	}
	ft_lstclear(&lst, NULL);
	ft_lstclear(&good, NULL);
	return (all_good);
}

static int	greater_cmp(char *a, char *b)
{
	return (a[0] > b[0] ? 1 : 0);
}

int		main(void)
{
	test_list_sort(NULL, NULL, greater_cmp);
	test_list_sort(ft_list_push_strs(1, (char *[]){"A"}),
			ft_list_push_strs(1, (char *[]){"A"}), greater_cmp);
	test_list_sort(ft_list_push_strs(2, (char *[]){"A", "B"}),
			ft_list_push_strs(2, (char *[]){"B", "A"}), greater_cmp);
	test_list_sort(ft_list_push_strs(4, (char *[]){"D", "C", "B", "A"}),
			ft_list_push_strs(4, (char *[]){"D", "C", "B", "A"}), greater_cmp);
	test_list_sort(ft_list_push_strs(4, (char *[]){"A", "B", "C", "D"}),
			ft_list_push_strs(4, (char *[]){"D", "C", "B", "A"}), greater_cmp);
	test_list_sort(ft_list_push_strs(4, (char *[]){"D", "B", "C", "A"}),
			ft_list_push_strs(4, (char *[]){"D", "C", "B", "A"}), greater_cmp);
	test_list_sort(ft_list_push_strs(4, (char *[]){"D", "C", "A", "B"}),
			ft_list_push_strs(4, (char *[]){"D", "C", "B", "A"}), greater_cmp);
	test_list_sort(ft_list_push_strs(4, (char *[]){"C", "D", "B", "A"}),
			ft_list_push_strs(4, (char *[]){"D", "C", "B", "A"}), greater_cmp);
	test_list_sort(ft_list_push_strs(26, (char *[]){
	"A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O",
	"P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z"}),
			ft_list_push_strs(26, (char *[]){
	"Z", "Y", "X", "W", "V", "U", "T", "S", "R", "Q", "P", "O", "N", "M", "L",
	"K", "J", "I", "H", "G", "F", "E", "D", "C", "B", "A"}), greater_cmp);
	test_list_sort(ft_list_push_strs(4, (char *[]){"A", "C", "A", "B"}),
			ft_list_push_strs(4, (char *[]){"C", "B", "A", "A"}), greater_cmp);
}
