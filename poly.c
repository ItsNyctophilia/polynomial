#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "poly.h"

struct term *poly_create_term(int coeff, unsigned int exp)
{
	struct term *node = malloc(sizeof(*node));
	if (node) {
		node->coeff = coeff;
		node->exp = exp;
		node->next = NULL;
		node->prev = NULL;
	}
	return node;
}

void poly_destroy(polynomial * eqn)
{
	while (eqn) {
		struct term *tmp = eqn->next;
		free(eqn);
		eqn = tmp;
	}
}

void poly_print(const polynomial * eqn)
{
	if (!eqn) {
		return;
	}
	if (eqn->coeff) {
		printf("%c%d", eqn->coeff > 0 ? '+' : '\0', eqn->coeff);
		if (eqn->exp > 1) {
			printf("x^%d", eqn->exp);
		} else if (eqn->exp == 1) {
			printf("x");
		}
		printf(" ");
	}
	poly_print(eqn->next);
}

static unsigned int sizeof_poly(const polynomial * p)
{
	unsigned int total_size = 1;	// Add first digit in coeff
	unsigned int coeff = abs(p->coeff);
	unsigned int exp = p->exp;

	while (coeff > 9) {	// Add number of digits in coeff
		coeff /= 10;
		++total_size;
	}
	if (p->coeff < 0) {
		++total_size;	// Add '-'
	}
	if (p->exp > 0) {
		++total_size;	// Add 'x'
	}
	if (p->exp > 1) {
		total_size += 2;	// Add '^' + first digit of exp
		while (exp > 9) {	// Add number of digits in exp
			exp /= 10;
			++total_size;
		}
	}
	return (total_size);
}

char *poly_to_string(const polynomial * p)
{
	// Syntax taken from Liam Echlin
	if (!p) {
		return (NULL);
	}

	char *end_poly_str = malloc(1);
	end_poly_str[0] = '\0';

	while (p) {
		while (!p->coeff) {
			p = p->next;
		}
		unsigned int poly_size = sizeof_poly(p);
		poly_size += 2;	// plus space for " +/-"
		char *curr_poly_str = malloc(poly_size + 1);	// Poly size plus '\0'
		snprintf(curr_poly_str, poly_size + 1, "%dx^%d", p->coeff,
			 p->exp);
		end_poly_str =
		    realloc(end_poly_str, strlen(end_poly_str) + poly_size + 1);
		if (!p->next) {
			snprintf(curr_poly_str, poly_size + 1, "%dx^%d",
				 p->coeff, p->exp);
			strncat(end_poly_str, curr_poly_str,
				strlen(curr_poly_str));
			free(curr_poly_str);
			break;
		}
		snprintf(curr_poly_str, poly_size + 1, "%dx^%d %s", p->coeff,
			 p->exp, p->next->coeff > 0 ? "+" : "");
		strncat(end_poly_str, curr_poly_str, strlen(curr_poly_str));
		free(curr_poly_str);
		p = p->next;
	}
	return (end_poly_str);
}

polynomial *poly_add(const polynomial * a, const polynomial * b)
{
	// Syntax taken from Liam Echlin

	polynomial *chain = NULL;
	polynomial **curr = &chain;
	polynomial *last = NULL;

	if (!a || !b) {
		return (NULL);
	}
	while (a && b) {
		if (a->exp > b->exp) {
			*curr = poly_create_term(a->coeff, a->exp);
			a = a->next;
		} else if (a->exp < b->exp) {
			*curr = poly_create_term(b->coeff, b->exp);
			b = b->next;
		} else {
			int coeff_total = a->coeff + b->coeff;
			*curr = poly_create_term(coeff_total, a->exp);
			a = a->next;
			b = b->next;
		}
		curr = &(*curr)->next;
	}
	while (a) {
		*curr = poly_create_term(a->coeff, a->exp);
		(*curr)->prev = last;
		last = *curr;
		a = a->next;
		curr = &(*curr)->next;
	}
	while (b) {
		*curr = poly_create_term(b->coeff, b->exp);
		b = b->next;
		(*curr)->prev = last;
		last = *curr;
		curr = &(*curr)->next;
	}
	return chain;
}

polynomial *poly_sub(const polynomial * a, const polynomial * b)
{
	// Syntax taken from Liam Echlin

	polynomial *chain = NULL;
	polynomial **curr = &chain;
	polynomial *last = NULL;

	if (!a || !b) {
		return (NULL);
	}
	while (a && b) {
		if (a->exp > b->exp) {
			*curr = poly_create_term(a->coeff, a->exp);
			a = a->next;
		} else if (a->exp < b->exp) {
			*curr = poly_create_term((-1) * b->coeff, b->exp);
			b = b->next;
		} else {
			int coeff_total = a->coeff - b->coeff;
			*curr = poly_create_term(coeff_total, a->exp);
			a = a->next;
			b = b->next;
		}
		curr = &(*curr)->next;
	}
	while (a) {
		*curr = poly_create_term(a->coeff, a->exp);
		(*curr)->prev = last;
		last = *curr;
		a = a->next;
		curr = &(*curr)->next;
	}
	while (b) {
		*curr = poly_create_term((-1) * b->coeff, b->exp);
		b = b->next;
		(*curr)->prev = last;
		last = *curr;
		curr = &(*curr)->next;
	}
	return chain;
}
