/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atoi_base.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mli <mli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/27 15:15:24 by mli               #+#    #+#             */
/*   Updated: 2020/07/08 21:29:35 by mli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlibasm.h"

int g_fct = ATOI_BASE;

int		test_atoi_base(char *str, char *base, int expect)
{
	int err[2];
	int eq[2];
	int ret[2];
	int all_good;

	errno = 0; bzero(err_buff, sizeof(err_buff)); test[ATOI_BASE].all++;
	ret[0] = ft_atoi_base(str, base);
	err[0] = errno; errno = 0;
	ret[1] = expect;
	err[1] = errno;
	eq[0] = (ret[0] == ret[1]); eq[1] = (err[0] == err[1]);
	if ((all_good = (eq[0] && eq[1] ? 1 : 0)))
		test[ATOI_BASE].done++;
	else
		sprintf(err_buff, "ft_atoi_base('%s', '%s')", str, base);
	truefalse(all_good, ret, err);
	return (all_good);
}

int		main(void)
{
	// PoneyVif
	test_atoi_base("vn", "poneyvif", 42);
	test_atoi_base("vn36", "poneyvif", 42);
	test_atoi_base("offffffffff", "poneyvif", 2147483647);
	test_atoi_base("-npppppppppp", "poneyvif", -2147483648);
	// Binary
	test_atoi_base("101010", "01", 42);
	test_atoi_base("101010ABCD", "01", 42);
	test_atoi_base("1010+10ABCD", "01", 10);
	test_atoi_base("-1010+10ABCD", "01", -10);
	test_atoi_base("01111111111111111111111111111111", "01", 2147483647);
	test_atoi_base("10000000000000000000000000000000", "01", -2147483648);
	// Hexa
	test_atoi_base("2A", "0123456789ABCDEF", 42);
	test_atoi_base("+2Aabcdef", "0123456789ABCDEF", 42);
	test_atoi_base("-2Aabcdef", "0123456789ABCDEF", -42);
	test_atoi_base("-10abcdef", "0123456789ABCDEF", -16);
	test_atoi_base("10abcdef", "0123456789ABCDEF", 16);
	// Decimal
	test_atoi_base("42", "0123456789", 42);
	test_atoi_base(" \t \n \v \f \r 42", "0123456789", 42);
	test_atoi_base(" \t \n \v \f \r 42+38", "0123456789", 42);
	test_atoi_base("-42abcdef", "0123456789", -42);
	test_atoi_base("28abcdef", "0123456789", 28);
	test_atoi_base("2147483647abcdef", "0123456789", 2147483647);
	test_atoi_base("-2147483648", "0123456789", -2147483648);
	//		 Wrong
	// base len is 0 or 1
	test_atoi_base("-42abcdef", "", 0);
	test_atoi_base("-42abcdef", "H", 0);
	// base contains +/-/whitespace
	test_atoi_base("-42abcdef", "HEY-", 0);
	test_atoi_base("-42abcdef", "HE+Y", 0);
	test_atoi_base("-42abcdef", "H EY", 0);
	test_atoi_base("-42abcdef", "HEY ", 0);
	test_atoi_base("-42abcdef", " HEY", 0);
	test_atoi_base("-42abcdef", "H\tEY", 0);
	test_atoi_base("-42abcdef", "H\nEY", 0);
	test_atoi_base("-42abcdef", "H\vEY", 0);
	test_atoi_base("-42abcdef", "H\fEY", 0);
	test_atoi_base("-42abcdef", "H\rEY", 0);
	// Base contains the same char twice
	test_atoi_base("-42abcdef", "HHEY", 0);
	test_atoi_base("-42abcdef", "HEYY", 0);
	test_atoi_base("-42abcdef", "HEYYO", 0);
	test_atoi_base("-42abcdef", "ABC011234", 0);
	test_atoi_base("-42abcdef", "ABC012344", 0);
	// Several {+/-}
	test_atoi_base("-+42abcdef", "0123456789", -42);
	test_atoi_base("-+-42abcdef", "0123456789", 42);
	test_atoi_base("-+-++-+-+--+42abcdef", "0123456789", 42);
}
