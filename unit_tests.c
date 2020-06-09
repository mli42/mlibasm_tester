#include "mlibasm_test.h"

int		test_write(const int fd, const char * const str, const int size)
{
	int ret[2];
	int eq[2];
	int err[2];
	int all_good;

	errno = 0; bzero(err_buff, sizeof(err_buff));
	ret[0] = ft_write(fd, str, size);
	err[0] = errno; errno = 0;
	ret[1] = write(fd, str, size);
	err[1] = errno;
	eq[0] = (ret[0] == ret[1]); eq[1] = (err[0] == err[1]);
	if ((all_good = (eq[0] && eq[1] ? 1 : 0)))
		g_wr++;
	else
		sprintf(err_buff, "ft_write(%d[%s], '%s', %d)",
				fd, which_fd(fd), str, size);
	truefalse(all_good, ret, err);
	return (all_good);
}

int		test_read(const int fd_me, const int fd_true, const int size)
{
	char buf[2][1024];
	int err[2];
	int ret[2];
	int eq[2];
	int all_good;

	errno = 0; bzero(err_buff, sizeof(err_buff));
	bzero(buf[0], sizeof(buf[0]));
	bzero(buf[1], sizeof(buf[1]));
	ret[0] = ft_read(fd_me, buf[0], size);
	err[0] = errno; errno = 0;
	ret[1] = read(fd_true, buf[1], size);
	err[1] = errno;
	eq[0] = (ret[0] == ret[1]); eq[1] = (err[0] == err[1]);
	if ((all_good = (eq[0] && eq[1] && !strcmp(buf[0], buf[1]) ? 1 : 0)))
		g_rd++;
	else
		sprintf(err_buff, "ft_read(%d[%s], buff_eq:%s, %d)",
			fd_me, which_fd(fd_me), tf_str(all_good), size);
	truefalse(all_good, ret, err);
	return (all_good);
}

int		test_strcmp(const char * const s1, const char * const s2)
{
	(void)s1; (void)s2;
	return (1);
}
