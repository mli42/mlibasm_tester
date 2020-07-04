/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_remove_if.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mli <mli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/27 15:15:24 by mli               #+#    #+#             */
/*   Updated: 2020/07/04 15:28:28 by mli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlibasm.h"

int g_fct = LIST_REMOVE_IF;

int		test_list_remove_if(t_list *lst, t_list *good, void *ref, int (*cmp)(),
		void (*free_fct)(void *))
{
	int err[2];
	int eq[2];
	int ret[2];
	int all_good;

	errno = 0; bzero(err_buff, sizeof(err_buff)); test[LIST_REMOVE_IF].all++;
	ret[0] = 0;
	ft_list_remove_if(&lst, ref, cmp, free_fct);
	err[0] = errno; errno = 0;
	ret[1] = ft_lstcmp(lst, good);
	err[1] = errno;
	eq[0] = (ret[0] == ret[1]); eq[1] = (err[0] == err[1]);
	if ((all_good = (eq[0] && eq[1] ? 1 : 0)))
		test[LIST_REMOVE_IF].done++;
	else
		sprintf(err_buff, "ft_list_remove_if()");
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

int		greater_cmp(char *a, char *b)
{
	return (a[0] >= b[0] ? 1 : 0);
}

int		less_cmp(char *a, char *b)
{
	return (a[0] < b[0] ? 1 : 0);
}

int		even(char *a, char *b)
{
	(void)b;
	return (a[0] % 2 ? 1 : 0);
}

void free_fct(void *a)
{
	(void)a;
}

int		main(void)
{
	test_list_remove_if(NULL, NULL, NULL, even, free_fct);
	test_list_remove_if(ft_list_push_strs(1, (char *[]){"0"}), NULL, NULL,
			even, free_fct);
	test_list_remove_if(ft_list_push_strs(2, (char *[]){"0", "2"}), NULL, NULL,
			even, free_fct);
	test_list_remove_if(ft_list_push_strs(4, (char *[]){"0", "2", "4", "6"}),
			NULL, NULL, even, free_fct);

	test_list_remove_if(ft_list_push_strs(5, (char *[]){"3", "4", "5", "6", "7"}),
		ft_list_push_strs(2, (char *[]){"3", "4"}),
			"5", less_cmp, free_fct);
	test_list_remove_if(ft_list_push_strs(5, (char *[]){"3", "4", "5", "6", "7"}),
		ft_list_push_strs(3, (char *[]){"5", "6", "7"}),
			"5", greater_cmp, free_fct);
	test_list_remove_if(ft_list_push_strs(5, (char *[]){"2", "3", "4", "5", "6"}),
		ft_list_push_strs(2, (char *[]){"3", "5"}),
			NULL, even, free_fct);
}
