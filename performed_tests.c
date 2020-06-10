#include "mlibasm.h"

void	wr_tests(void)
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

void	rd_tests(void)
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

void	strcmp_tests(void)
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

void	strcpy_tests()
{
	test_strcpy("", "");
	test_strcpy("ah", "");
	test_strcpy("hey", "ho");
	test_strcpy("Ok this is more normal", "Yeayah");
	test_strcpy("Ok this is more normal", "as it is written, normal.");
}

void	strdup_tests()
{
	test_strdup("");
	test_strdup("heyho");
	test_strdup("heyyyyy!");
	test_strdup("Hello this should work");
}

void	strlen_tests()
{
	test_strlen("");
	test_strlen("heyho");
	test_strlen("heyyyyy!");
	test_strlen("Hello this should work");
}
