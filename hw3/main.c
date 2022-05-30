#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

typedef struct _poly {
	int coef;
	int exp;
	int flag;
	struct _poly* prev;
	struct _poly* next;
} Polynomial;

Polynomial* readPoly(FILE* fp, Polynomial* p, int* len);
Polynomial* pmult(Polynomial* temp_poly, Polynomial* p1, Polynomial* p2, int p1Len, int p2Len);
Polynomial* get_result(Polynomial* result, Polynomial* temp_poly);
void printPoly(Polynomial* p);

void main() {
	int aLen, bLen, resLen;
	Polynomial* A = NULL;
	Polynomial* B = NULL;
	Polynomial* result = NULL;
	Polynomial* temp_poly = NULL;

	FILE* fpa = fopen("A.txt", "r");
	FILE* fpb = fopen("B.txt", "r");
	if (fpa == NULL || fpb == NULL) {
		printf("NOT VALID FILE!\n");
		return;
	}

	A = readPoly(fpa, A, &aLen);
	B = readPoly(fpb, B, &bLen);
	temp_poly = pmult(temp_poly, A, B, aLen, bLen);
	result = get_result(result, temp_poly);
	printPoly(result);

	free(A);
	free(B);
	free(temp_poly);
	free(result);
}

Polynomial* readPoly(FILE* fp, Polynomial* p, int* len){
	int coef, exp;
	Polynomial *trail;
	trail = p;
	*len = 0;

	while (1) {
		int res = fscanf(fp, "%d %d", &coef, &exp);
		if (res == EOF) break;
		Polynomial* newnode;
		newnode = (Polynomial*)malloc(sizeof(Polynomial));
		newnode->coef = coef;
		newnode->exp = exp;
		newnode->flag = 0;
		newnode->prev = NULL;
		newnode->next = NULL;
		if (p == NULL) {
			p = newnode;
			trail = p;
		}
		else {
			trail->next = newnode;
			newnode->prev = trail;
			trail = trail->next;
		}
		(*len)++;
	}

	return p;
}

Polynomial* pmult(Polynomial* temp_poly, Polynomial* p1, Polynomial* p2, int p1Len, int p2Len) {
	Polynomial* trail1;
	Polynomial* trail2;
	Polynomial* trail_temp;

	trail1 = p1;
	trail2 = p2;
	trail_temp = temp_poly;

	for (int i = 0; i < p1Len; i++) {
		for (int j = 0; j < p2Len; j++) {
			Polynomial* newnode;
			newnode = (Polynomial*)malloc(sizeof(Polynomial));
			newnode->coef = trail1->coef * trail2->coef;
			newnode->exp = trail1->exp + trail2->exp;
			newnode->flag = 0;
			newnode->prev = NULL;
			newnode->next = NULL;

			if (temp_poly == NULL) {
				temp_poly = newnode;
				trail_temp = temp_poly;
			}
			else {
				trail_temp->next = newnode;
				newnode->prev = trail_temp;
				trail_temp = trail_temp->next;
			}
			trail2 = trail2->next;
		}
		trail1 = trail1->next;
		trail2 = p2;
	}

	
	return temp_poly;
}

Polynomial* get_result(Polynomial* result, Polynomial* temp_poly) {
	int standard_exp, res_coef = 0;
	Polynomial* trail_result;
	Polynomial* trail_temp;
	Polynomial* most;

	trail_temp = temp_poly;
	trail_result = result;

	while (1) {
		while (trail_temp != NULL) {
			if (trail_temp->flag == 0)
				break;
			trail_temp = trail_temp->next;
		}
		if (trail_temp == NULL) {
			break;
		}

		trail_temp = temp_poly;
		while (trail_temp->flag == 1) {
			trail_temp = trail_temp->next;
		}
		most = trail_temp;
		standard_exp = most->exp;
		while (trail_temp != NULL) {
			if (trail_temp->exp > standard_exp && trail_temp->flag == 0) {
				most = trail_temp;
				standard_exp = most->exp;
			}
			trail_temp = trail_temp->next;
		}
		standard_exp = most->exp;
		res_coef += most->coef;
		most->flag = 1;

		trail_temp = temp_poly;
		while (trail_temp != NULL) {
			if (trail_temp->exp == standard_exp && trail_temp->flag == 0) {
				res_coef += trail_temp->coef;
				trail_temp->flag = 1;
			}
			trail_temp = trail_temp->next;
		}

		Polynomial* newnode;
		newnode = (Polynomial*)malloc(sizeof(Polynomial));
		newnode->coef = res_coef;
		newnode->exp = standard_exp;
		newnode->flag = 0;
		newnode->prev = NULL;
		newnode->next = NULL;

		if (result == NULL) {
			result = newnode;
			trail_result = result;
		}
		else {
			trail_result->next = newnode;
			newnode->prev = trail_result;
			trail_result = trail_result->next;
		}

		res_coef = 0;
		trail_temp = temp_poly;
	}
	return result;
}

void printPoly(Polynomial* p) {
	Polynomial* trail;

	trail = p;
	while (trail != NULL) {
		if (trail->next == NULL) {
			printf("%dx^%d\n\n", trail->coef, trail->exp);
		}
		else {
			printf("%dx^%d + ", trail->coef, trail->exp);
		}
		trail = trail->next;
	}
}