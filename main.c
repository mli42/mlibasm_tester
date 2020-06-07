/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mli <mli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/24 21:00:58 by mli               #+#    #+#             */
/*   Updated: 2020/05/20 16:10:36 by mli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libasm.h"
// int		printf(const char *str, ...);

void	ft_wr_len(char *str)
{
	printf("The sentence tested : [%s] | len : [%lu]\n", str, strlen(str));
	printf("\nWrite [%lu]\n", ft_write(1, str, strlen(str)));
	printf("Strlen [%lu]\n\n", ft_strlen(str));
}

void	ft_test_strcpy(char *s2)
{
	char s1[1024];

	memset(s1, '-', 1024);
	printf("%s\n", ft_strcpy(s1, s2));
}

void	ft_test_strcmp(char *s1, char *s2)
{
	printf("Mine %d\n", ft_strcmp(s1, s2));
	printf("True %d\n", strcmp(s1, s2));
}

void	ft_test_read(int fd, int count)
{
	char buff[1024];

	memset(buff, 0, 1024);
	printf("%d\n", (int)ft_read(fd, buff, count));
	printf("%s\n", buff);
}

void	ft_test_strdup(char *s1)
{
	printf("%s\n%s\n", s1, ft_strdup(s1));
}

int		main(void)
{
//	ft_wr_len("123");
//	ft_wr_len("");
//	ft_wr_len("123456789ABCDEFGHIJKLMNOPQRSUVWXYZ");

//	ft_test_strcpy("");
//	ft_test_strcpy("12345");

//	ft_test_strcmp("12345", "12346");
//	ft_test_strcmp("", "");
//	ft_test_strcmp("12349", "12346");

//	ft_test_read(open("main.c", O_RDONLY), 5);

//	ft_test_strdup("123456789ABCDEF");

	return (0);
}
