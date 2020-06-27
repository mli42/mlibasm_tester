/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strcpy.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mli <mli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/27 15:13:47 by mli               #+#    #+#             */
/*   Updated: 2020/06/27 15:53:13 by mli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlibasm.h"

int g_fct = STRCPY;

int		test_strcpy(char const * const dst, const char * const source)
{
	char dest[2][STRCPY_SIZE]; char src[2][STRCPY_SIZE];
	int err[2];
	int ret[2];
	int eq[2];
	int all_good;

	strcpy(dest[0], dst); strcpy(src[0], source);
	strcpy(dest[1], dst); strcpy(src[1], source);
	errno = 0; bzero(err_buff, sizeof(err_buff)); test[STRCPY].all++;
	ret[0] = ft_strcpy(dest[0], src[0]) == dest[0];
	err[0] = errno; errno = 0;
	ret[1] = strcpy(dest[1], src[1]) == dest[1];
	err[1] = errno;
	eq[0] = (ret[0] == ret[1]); eq[1] = (err[0] == err[1]);
	if ((all_good = (eq[0] && eq[1] && !strcmp(dest[0], dest[1]) ? 1 : 0)))
		test[STRCPY].done++;
	else
		sprintf(err_buff, "ft_strcpy('%s', '%s')", dst, source);
	truefalse(all_good, ret, err);
	return (all_good);
}

int		main(void)
{
	test_strcpy("", "");
	test_strcpy("ah", "");
	test_strcpy("hey", "ho");
	test_strcpy("Ok this is more normal", "Yeayah");
	test_strcpy("Ok this is more normal", "as it is written, normal.");
}
