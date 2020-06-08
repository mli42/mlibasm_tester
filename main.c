void	ft_test_strcpy(char *s2)
{
	char s1[1024];

	memset(s1, '-', 1023);
	s1[1023] = '\0';
	printf("%s\n", ft_strcpy(s1, s2));
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

	return (0);
}
