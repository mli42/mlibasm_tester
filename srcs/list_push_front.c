/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_push_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mli <mli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/27 15:15:24 by mli               #+#    #+#             */
/*   Updated: 2020/06/27 22:58:17 by mli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlibasm.h"

int g_fct = LIST_PUSH_FRONT;

int		test_push_front(t_list *lst, t_list *good, void *newdata)
{
	int err[2];
	int eq[2];
	int ret[2];
	int all_good;

	errno = 0; bzero(err_buff, sizeof(err_buff)); test[LIST_PUSH_FRONT].all++;
	ret[0] = 0;
	ft_list_push_front(&lst, newdata);
	err[0] = errno; errno = 0;
	ret[1] = ft_lstcmp(lst, good);
	err[1] = errno;
	eq[0] = (ret[0] == ret[1]); eq[1] = (err[0] == err[1]);
	if ((all_good = (eq[0] && eq[1] ? 1 : 0)))
		test[LIST_PUSH_FRONT].done++;
	else
		sprintf(err_buff, "ft_list_push_front()");
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

int		main(void)
{
	test_push_front(NULL, ft_list_push_strs(1, (char *[]){"A"}), "A");
	test_push_front(ft_list_push_strs(3, (char *[]){"D", "C", "B"}),
			ft_list_push_strs(4, (char *[]){"D", "C", "B", "A"}), "A");
}
