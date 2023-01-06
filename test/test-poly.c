#include <check.h>

#include "../poly.h"
#include <stdbool.h>

START_TEST(test_poly_print)
{
	polynomial *poly_term = poly_create_term(-103,11);
	poly_print(poly_term);
	putchar('\n');
	ck_assert(true);
	poly_destroy(poly_term);
} END_TEST

START_TEST(test_poly_string)
{
	polynomial *poly_term = poly_create_term(-103,11);
	char *end_str = poly_to_string(poly_term);
	ck_assert_str_eq("-103x^11", end_str);
	poly_destroy(poly_term);
	free(end_str);
} END_TEST

Suite *poly_test_suite(void)
{
	Suite *s1 = suite_create("Poly");

	TCase *tc1 = tcase_create("TC 1");

	suite_add_tcase(s1, tc1);

	tcase_add_test(tc1, test_poly_print);
	tcase_add_test(tc1, test_poly_string);
	
	return s1;
}
