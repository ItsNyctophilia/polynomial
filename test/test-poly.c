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

START_TEST(test_poly_equal)
{
	polynomial *poly_term_a1 = poly_create_term(2, 5);
	polynomial *poly_term_a2 = poly_create_term(1, 3);
	polynomial *poly_result_a1 = poly_add(poly_term_a1, poly_term_a2);
	polynomial *poly_term_b1 = poly_create_term(2, 5);
	polynomial *poly_term_b2 = poly_create_term(1, 3);
	polynomial *poly_result_b1 = poly_add(poly_term_b1, poly_term_b2);

	ck_assert(poly_equal(poly_result_a1, poly_result_b1));
	ck_assert(!(poly_equal(poly_result_a1, poly_term_a1)));
	ck_assert(!(poly_equal(NULL, poly_term_b1)));

	poly_destroy(poly_term_a1);
	poly_destroy(poly_term_a2);
	poly_destroy(poly_term_b1);
	poly_destroy(poly_term_b2);
	poly_destroy(poly_result_a1);
	poly_destroy(poly_result_b1);
} END_TEST 

START_TEST(test_poly_eval)
{
	polynomial *poly_term_a1 = poly_create_term(2, 5);
	polynomial *poly_term_a2 = poly_create_term(1, 3);
	polynomial *poly_result_a1 = poly_add(poly_term_a1, poly_term_a2);
	double answer = poly_eval(poly_result_a1, 5);
	ck_assert_double_eq_tol(6375, answer, 0.001);

	polynomial *poly_term_b1 = poly_create_term(-2, 5);
	polynomial *poly_term_b2 = poly_create_term(-1, 3);
	polynomial *poly_result_b1 = poly_add(poly_term_b1, poly_term_b2);
	answer = poly_eval(poly_result_b1, 5);
	ck_assert_double_eq_tol(-6375, answer, 0.001);

	poly_destroy(poly_term_a1);
	poly_destroy(poly_term_a2);
	poly_destroy(poly_term_b1);
	poly_destroy(poly_term_b2);
	poly_destroy(poly_result_a1);
	poly_destroy(poly_result_b1);
} END_TEST 

static void triple(struct term *t)
{
	t->coeff *=3;
	return;
}

START_TEST(test_poly_iterate)
{
	polynomial *poly_term_a1 = poly_create_term(2, 5);
	polynomial *poly_term_a2 = poly_create_term(1, 3);
	polynomial *poly_result_a1 = poly_add(poly_term_a1, poly_term_a2);
	poly_iterate(poly_result_a1, triple);
	ck_assert_int_eq(6, poly_result_a1->coeff);
	ck_assert_int_eq(3, poly_result_a1->next->coeff);

	poly_destroy(poly_term_a1);
	poly_destroy(poly_term_a2);
	poly_destroy(poly_result_a1);
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
	tcase_add_test(tc1, test_poly_equal);
	tcase_add_test(tc1, test_poly_eval);
	tcase_add_test(tc1, test_poly_iterate);
	tcase_add_test(tc1, test_poly_sort);
	return s1;
}
