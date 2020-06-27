/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mli <mli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/27 15:12:59 by mli               #+#    #+#             */
/*   Updated: 2020/06/27 15:52:36 by mli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlibasm.h"

int g_fct = RD;

int		test_read(const int fd_me, const int fd_true, const int size)
{
	char buf[2][1024];
	int err[2];
	int ret[2];
	int eq[2];
	int all_good;

	errno = 0; bzero(err_buff, sizeof(err_buff)); test[RD].all++;
	bzero(buf[0], sizeof(buf[0]));
	bzero(buf[1], sizeof(buf[1]));
	ret[0] = ft_read(fd_me, buf[0], size);
	err[0] = errno; errno = 0;
	ret[1] = read(fd_true, buf[1], size);
	err[1] = errno;
	eq[0] = (ret[0] == ret[1]); eq[1] = (err[0] == err[1]);
	if ((all_good = (eq[0] && eq[1] && !strcmp(buf[0], buf[1]) ? 1 : 0)))
		test[RD].done++;
	else
		sprintf(err_buff, "ft_read(%d[%s], buff_eq:%s, %d)",
			fd_me, which_fd(fd_me), tf_str(all_good), size);
	truefalse(all_good, ret, err);
	return (all_good);
}

int		main(void)
{
	test_read(9, 9, 5);
	test_read(9, 9, 9);

	test_read(rdfd, rdfd_true, 5);
	test_read(rdfd, rdfd_true, 1);
	test_read(rdfd, rdfd_true, 9);
	test_read(rdfd, rdfd_true, 7);
	test_read(rdfd, rdfd_true, 18);
	test_read(rdfd, rdfd_true, 30);

	test_read(wrfd, wrfd, 5);
	test_read(wrfd, wrfd, 1);
	test_read(wrfd, wrfd, 9);
	test_read(wrfd, wrfd, 7);
	test_read(wrfd, wrfd, 18);
	test_read(wrfd, wrfd, 30);
}
