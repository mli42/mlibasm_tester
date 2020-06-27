/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strlen.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mli <mli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/27 15:15:24 by mli               #+#    #+#             */
/*   Updated: 2020/06/27 15:53:04 by mli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlibasm.h"

int g_fct = STRLEN;

int		test_strlen(const char *str)
{
	int err[2];
	int eq[2];
	int ret[2];
	int all_good;

	errno = 0; bzero(err_buff, sizeof(err_buff)); test[STRLEN].all++;
	ret[0] = ft_strlen(str);
	err[0] = errno; errno = 0;
	ret[1] = strlen(str);
	err[1] = errno;
	eq[0] = (ret[0] == ret[1]); eq[1] = (err[0] == err[1]);
	if ((all_good = (eq[0] && eq[1] ? 1 : 0)))
		test[STRLEN].done++;
	else
		sprintf(err_buff, "ft_strlen('%s')", str);
	truefalse(all_good, ret, err);
	return (all_good);
}

int		main(void)
{
	test_strlen("");
	test_strlen("heyho");
	test_strlen("heyyyyy!");
	test_strlen("Hello this should work");
}
