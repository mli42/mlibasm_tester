/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_size.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mli <mli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/27 15:15:24 by mli               #+#    #+#             */
/*   Updated: 2020/06/27 20:53:17 by mli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlibasm.h"

int g_fct = LIST_SIZE;

int		test_list_size(t_list *lst, int res)
{
	int err[2];
	int eq[2];
	int ret[2];
	int all_good;

	errno = 0; bzero(err_buff, sizeof(err_buff)); test[LIST_SIZE].all++;
	ret[0] = ft_list_size(lst);
	err[0] = errno; errno = 0;
	ret[1] = res;
	err[1] = errno;
	eq[0] = (ret[0] == ret[1]); eq[1] = (err[0] == err[1]);
	if ((all_good = (eq[0] && eq[1] ? 1 : 0)))
		test[LIST_SIZE].done++;
	else
		sprintf(err_buff, "ft_list_size(%d)", res);
	truefalse(all_good, ret, err);
	ft_lstclear(&lst, NULL);
	return (all_good);
}

int		main(void)
{
	test_list_size(NULL, 0);
	test_list_size(ft_list_push_strs(3, (char *[]){"A", "B", "C"}), 3);
	test_list_size(ft_list_push_strs(5, (char *[]){"A", "B", "C", "D", "E"}), 5);
}
