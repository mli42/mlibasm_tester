/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strdup.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mli <mli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/27 15:14:35 by mli               #+#    #+#             */
/*   Updated: 2020/07/08 23:40:17 by mli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlibasm.h"

int g_fct = STRDUP;
extern int fct_check_leaks;

int		test_strdup(const char *str)
{
	int err[2];
	char *strs[2];
	int eq[2];
	int ret[2];
	int all_good;

	errno = 0; bzero(err_buff, sizeof(err_buff)); test[STRDUP].all++;
	strs[0] = ft_strdup(str);
	err[0] = errno; errno = 0;
	strs[1] = strdup(str);
	err[1] = errno;
	ret[0] = 1; ret[1] = 1;
	eq[0] = 1; eq[1] = (err[0] == err[1]);
	if ((all_good = (eq[0] && eq[1] && !strcmp(strs[0], strs[1]) ? 1 : 0)))
		test[STRDUP].done++;
	else
		sprintf(err_buff, "ft_strdup('%s')\n" \
			"Has'\e[91m%s\e[0m'\nExpected '\e[92m%s\e[0m'",
				str, strs[0], strs[1]);
	truefalse(all_good, ret, err);
	free(strs[0]); free(strs[1]);
	return (all_good);
}

int		main(void)
{
	fct_check_leaks = 1;

	test_strdup("");
	test_strdup("heyho");
	test_strdup("heyyyyy!");
	test_strdup("Hello this should work");
}
