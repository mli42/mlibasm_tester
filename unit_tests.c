#include "mlibasm.h"

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
