#include <check.h>

#include "../poly.h"
#include <stdbool.h>

START_TEST(test_poly_print)
{
	polynomial *poly_term = poly_create_term(1,1);
	poly_print(poly_term);
	putchar('\n');
	ck_assert(true);
} END_TEST

Suite *poly_test_suite(void)
{
	Suite *s1 = suite_create("Poly");

	TCase *tc1 = tcase_create("TC 1");

	suite_add_tcase(s1, tc1);

	tcase_add_test(tc1, test_poly_print);
	
	return s1;
}
