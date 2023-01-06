#include <check.h>

Suite *poly_test_suite(void);

int main(void)
{
	SRunner *sr = srunner_create(NULL);

	srunner_add_suite(sr, poly_test_suite());

	srunner_run_all(sr, CK_NORMAL);

	srunner_free(sr);
}


