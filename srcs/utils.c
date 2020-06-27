#include "mlibasm.h"

extern char **environ;
extern char *const __progname;

void	check_leaks(void)
{
	char * const *a = (char * const []){"leaks", __progname, NULL};

	if (fork() != 0)
		sleep(1);
	else
	{
		if (execve("/usr/bin/leaks", a, environ) == -1)
			perror("NO, couldn't check leaks");
		exit(1);
	}
}

void	done_on_all(char *str, int done, int all)
{
	char *color = (done == all ? "\e[0;92m" : "\e[0;91m");

	printf("\e[0;1;96m%s: %s%d\e[0;1m/\e[92m%d\e[0m\n", str, color, done, all);
}

int		same_sign(int num1, int num2)
{
	return (((num1 == 0) == (num2 == 0)) && ((num1 < 0)  == (num2 < 0)));
}

void	ft_signal(int sign)
{
	(void)sign;
	exit(1);
}

char	*tf_str(const int eq)
{
	return (eq ? "\e[0;92mTrue\e[0m" : "\e[0;91mFalse\e[0m");
}

char	*which_fd(int fd)
{
	if (fd == 0) return ("stdin");
	if (fd == 1) return ("stdout");
	if (fd == 2) return ("stderr");
	if (fd == rdfd) return ("rdfd");
	if (fd == wrfd) return ("wrfd");
	return ("fakefd");
}
