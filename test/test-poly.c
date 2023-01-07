#include <check.h>

#include "../poly.h"
#include <stdbool.h>

START_TEST(test_poly_print)
{
	polynomial *poly_term = poly_create_term(-103, 11);
	poly_print(poly_term);
	putchar('\n');
	ck_assert(true);
	poly_destroy(poly_term);
}

END_TEST 

START_TEST(test_poly_string)
{
	polynomial *poly_term = poly_create_term(103, 11);
	char *end_str = poly_to_string(poly_term);
	ck_assert_str_eq("103x^11", end_str);
	polynomial *poly_term_2 = poly_create_term(-100, 10);
	polynomial *poly_combined_term = poly_add(poly_term, poly_term_2);
	free(end_str);
	end_str = poly_to_string(poly_combined_term);
	ck_assert_str_eq("103x^11 -100x^10", end_str);
	poly_destroy(poly_term);
	poly_destroy(poly_term_2);
	poly_destroy(poly_combined_term);
	free(end_str);
} END_TEST 

START_TEST(test_poly_add)
{
	polynomial *poly_term_1 = poly_create_term(2, 5);
	polynomial *poly_term_2 = poly_create_term(1, 3);
	polynomial *poly_result = poly_add(poly_term_1, poly_term_2);
	polynomial *poly_term_3 = poly_create_term(2, 5);
	polynomial *poly_result_2 = poly_add(poly_result, poly_term_3);

	ck_assert_int_eq(1, poly_result->next->coeff);
	ck_assert_uint_eq(3, poly_result->next->exp);
	ck_assert_int_eq(4, poly_result_2->coeff);
	ck_assert_uint_eq(5, poly_result_2->exp);

	poly_destroy(poly_term_1);
	poly_destroy(poly_term_2);
	poly_destroy(poly_term_3);
	poly_destroy(poly_result);
	poly_destroy(poly_result_2);
} END_TEST 

START_TEST(test_poly_sub)
{
	polynomial *poly_term_1 = poly_create_term(2, 5);
	polynomial *poly_term_2 = poly_create_term(1, 3);
	polynomial *poly_result = poly_sub(poly_term_1, poly_term_2);
	polynomial *poly_term_3 = poly_create_term(3, 5);
	polynomial *poly_result_2 = poly_sub(poly_result, poly_term_3);

	ck_assert_int_eq(-1, poly_result->next->coeff);
	ck_assert_uint_eq(3, poly_result->next->exp);
	ck_assert_int_eq(-1, poly_result_2->coeff);
	ck_assert_uint_eq(5, poly_result_2->exp);

	poly_destroy(poly_term_1);
	poly_destroy(poly_term_2);
	poly_destroy(poly_term_3);
	poly_destroy(poly_result);
	poly_destroy(poly_result_2);
} END_TEST 

START_TEST(test_poly_sort)
{
	polynomial *poly_term_1 = poly_create_term(2, 5);
	polynomial *poly_term_2 = poly_create_term(1, 3);
	polynomial *poly_result = poly_add(poly_term_1, poly_term_2);
	polynomial *poly_term_3 = poly_create_term(3, 5);
	polynomial *poly_result_2 = poly_add(poly_result, poly_term_3);
	polynomial *poly_term_4 = poly_create_term(5, 7);
	polynomial *poly_result_3 = poly_add(poly_result_2, poly_term_4);

	putchar('\n');
	poly_print(poly_result_3);
	putchar('\n');
	poly_destroy(poly_term_1);
	poly_destroy(poly_term_2);
	poly_destroy(poly_term_3);
	poly_destroy(poly_term_4);
	poly_destroy(poly_result);
	poly_destroy(poly_result_2);
	poly_destroy(poly_result_3);
} END_TEST 

Suite * poly_test_suite(void)
{
	Suite *s1 = suite_create("Poly");

	TCase *tc1 = tcase_create("TC 1");

	suite_add_tcase(s1, tc1);

	tcase_add_test(tc1, test_poly_print);
	tcase_add_test(tc1, test_poly_string);
	tcase_add_test(tc1, test_poly_add);
	tcase_add_test(tc1, test_poly_sub);
	tcase_add_test(tc1, test_poly_sort);
	return s1;
}
