
#include "libasm.h"
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

void	test(void)
{
	write(1, "DEBUG\n", 6);
}

int		main(int argc, char **argv)
{
	(void)argc; (void)argv;

	int old;
	char *hey;

	hey = ft_strdup("HEYHO");
	old = errno;
	printf("Your \e[91merrno\e[0m is [\e[93m%d\e[0m]\n", old);
	printf("Ptr: %p => '%s'\n", hey, hey);
	printf("\e[92mENOMEM is %d\e[0m\n", ENOMEM);
	if (errno) perror("perror gives");
	free(hey); return (0);
}
