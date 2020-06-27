/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strcmp.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mli <mli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/27 15:12:52 by mli               #+#    #+#             */
/*   Updated: 2020/06/27 15:52:54 by mli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlibasm.h"

int g_fct = STRCMP;

int		test_strcmp(const char * const s1, const char * const s2)
{
	int err[2];
	int ret[2];
	int eq[2];
	int all_good;

	errno = 0; bzero(err_buff, sizeof(err_buff)); test[STRCMP].all++;
	ret[0] = ft_strcmp(s1, s2);
	err[0] = errno; errno = 0;
	ret[1] = strcmp(s1, s2);
	err[1] = errno;
	eq[0] = same_sign(ret[0], ret[1]); eq[1] = (err[0] == err[1]);
	if ((all_good = (eq[0] && eq[1])))
		test[STRCMP].done++;
	else
		sprintf(err_buff, "ft_strcmp('%s', '%s')", s1, s2);
	truefalse(all_good, ret, err);
	return (all_good);
}

int		main(void)
{
	test_strcmp("Hello", "Hello");
	test_strcmp("Hello!", "Hello");
	test_strcmp("Hello", "Hello!");
	test_strcmp("He!!o", "Hello");
	test_strcmp("Hello", "He!!o");

	test_strcmp("Hello\tHi", "Hello\tHi");
	test_strcmp("Hello\200Hi", "Hello\0Hi");
	test_strcmp("Hello\0Hi", "Hello\200Hi");
	test_strcmp("Hello\200Hi", "Hello\200Hi");
	test_strcmp("Hello\0Hi", "Hello\0Hi");

	test_strcmp("This string is longer", "This string is longer");
	test_strcmp("You might pass all these tests", "Or not");
	test_strcmp("or not", "Or not");
	test_strcmp("or noT", "or not");
}

