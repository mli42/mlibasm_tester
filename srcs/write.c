/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mli <mli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/27 15:09:47 by mli               #+#    #+#             */
/*   Updated: 2020/06/27 15:51:58 by mli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlibasm.h"

int g_fct = WR;

int		test_write(const int fd, const char * const str, const int size)
{
	int ret[2];
	int eq[2];
	int err[2];
	int all_good;

	errno = 0; bzero(err_buff, sizeof(err_buff)); test[WR].all++;
	ret[0] = ft_write(fd, str, size);
	err[0] = errno; errno = 0;
	ret[1] = write(fd, str, size);
	err[1] = errno;
	eq[0] = (ret[0] == ret[1]); eq[1] = (err[0] == err[1]);
	if ((all_good = (eq[0] && eq[1] ? 1 : 0)))
		test[WR].done++;
	else
		sprintf(err_buff, "ft_write(%d[%s], '%s', %d)",
				fd, which_fd(fd), str, size);
	truefalse(all_good, ret, err);
	return (all_good);
}

int		main(void)
{
	test_write(9, "Hello", 5);
	test_write(wrfd, "Hello!", 6);
	test_write(wrfd, NULL, 5);
	test_write(-1, NULL, 5);
	test_write(wrfd, "ABCEDFGEFGH", 9);
	test_write(9, "ABCEDFGEFGH", 9);
	test_write(wrfd, NULL, -1);
	test_write(wrfd, "A longer sentence!", 18);

	test_write(rdfd, "Hello!", 6);
	test_write(rdfd, NULL, 5);
	test_write(rdfd, NULL, -1);
	test_write(rdfd, "A longer sentence!", 18);
}
