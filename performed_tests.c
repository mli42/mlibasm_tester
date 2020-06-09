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

}
