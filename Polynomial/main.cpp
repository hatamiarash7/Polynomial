#include <iostream>
#include <conio.h>
#include <process.h>
#include <cstdlib>

using namespace std;

int exponent(int, int);

struct node
{
	int coe, exp;
	struct node *next;
};

class polynomial
{
	struct node *start, *ptrn, *ptrp;
public:
	void get();
	void show();
	void add(polynomial, polynomial);
	void subtract(polynomial, polynomial);
	void multiply(polynomial, polynomial);
	void sort();
	int calculate(int);
};

void polynomial::get()
{
	char c = 'y';
	ptrn = ptrp = start = NULL;
	while (c == 'y' || c == 'Y')
	{
		ptrn = new node;
		if (ptrp != NULL)
			ptrp->next = ptrn;
		if (start == NULL)
			start = ptrn;
		ptrp = ptrn;
		cout << "\n coefficient: ";
		cin >> ptrn->coe;
		cout << " exponent: ";
		cin >> ptrn->exp;
		ptrn->next = NULL;
		cout << " add more ? (y/n) ";
		cin >> c;
	}
	return;
}

void polynomial::show()
{
	struct node *ptr;
	ptr = start;
	while (ptr != NULL)
	{
		cout << ptr->coe << "X^" << ptr->exp << " + ";
		ptr = ptr->next;
	}
	cout << " ";
}

void polynomial::add(polynomial p1, polynomial p2)
{
	struct node *p1ptr, *p2ptr;
	int coe, exp;
	ptrn = ptrp = start = NULL;
	p1ptr = p1.start;
	p2ptr = p2.start;
	while (p1ptr != NULL && p2ptr != NULL)
	{
		if (p1ptr->exp == p2ptr->exp) // If coefficients are equal
		{
			coe = p1ptr->coe + p2ptr->coe;
			exp = p1ptr->exp;
			p1ptr = p1ptr->next;
			p2ptr = p2ptr->next;
		}
		else if (p1ptr->exp > p2ptr->exp)
		{
			coe = p1ptr->coe;
			exp = p1ptr->exp;
			p1ptr = p1ptr->next;
		}
		else if (p1ptr->exp < p2ptr->exp)
		{
			coe = p2ptr->coe;
			exp = p2ptr->exp;
			p2ptr = p2ptr->next;
		}
		ptrn = new node;
		if (start == NULL)
			start = ptrn;
		ptrn->coe = coe;
		ptrn->exp = exp;
		ptrn->next = NULL;
		if (ptrp != NULL)
			ptrp->next = ptrn;
		ptrp = ptrn;
	}
	if (p1ptr == NULL)
	{
		while (p2ptr != NULL)
		{
			coe = p2ptr->coe;
			exp = p2ptr->exp;
			p2ptr = p2ptr->next;
			ptrn = new node;
			if (start == NULL)
				start = ptrn;
			ptrn->coe = coe;
			ptrn->exp = exp;
			ptrn->next = NULL;
			ptrp->next = ptrn;
			ptrp = ptrn;
		}
	}
	else if (p2ptr == NULL)
	{
		while (p1ptr != NULL)
		{
			coe = p1ptr->coe;
			exp = p1ptr->exp;
			p1ptr = p1ptr->next;
			ptrn = new node;
			if (start == NULL)
				start = ptrn;
			ptrn->coe = coe;
			ptrn->exp = exp;
			ptrn->next = NULL;
			ptrp->next = ptrn;
			ptrp = ptrn;
		}
	}
}

void polynomial::subtract(polynomial p1, polynomial p2)
{
	struct node *p1ptr, *p2ptr;
	int coe, exp;
	ptrn = ptrp = start = NULL;
	p1ptr = p1.start;
	p2ptr = p2.start;
	while (p1ptr != NULL && p2ptr != NULL)
	{
		if (p1ptr->exp == p2ptr->exp) // If coefficients are equal
		{
			coe = p1ptr->coe - p2ptr->coe;
			exp = p1ptr->exp;
			p1ptr = p1ptr->next;
			p2ptr = p2ptr->next;
		}
		else if (p1ptr->exp > p2ptr->exp)
		{
			coe = p1ptr->coe;
			exp = p1ptr->exp;
			p1ptr = p1ptr->next;
		}
		else if (p1ptr->exp < p2ptr->exp)
		{
			coe = 0 - p2ptr->coe;
			exp = p2ptr->exp;
			p2ptr = p2ptr->next;
		}
		ptrn = new node;
		if (start == NULL)
			start = ptrn;
		ptrn->coe = coe;
		ptrn->exp = exp;
		ptrn->next = NULL;
		if (ptrp != NULL)
			ptrp->next = ptrn;
		ptrp = ptrn;
	}
	if (p1ptr == NULL)
	{
		while (p2ptr != NULL)
		{
			coe = 0 - p2ptr->coe;
			exp = p2ptr->exp;
			p2ptr = p2ptr->next;
			ptrn = new node;
			if (start == NULL)
				start = ptrn;
			ptrn->coe = coe;
			ptrn->exp = exp;
			ptrn->next = NULL;
			ptrp->next = ptrn;
			ptrp = ptrn;
		}
	}
	else if (p2ptr == NULL)
	{
		while (p1ptr != NULL)
		{
			coe = p1ptr->coe;
			exp = p1ptr->exp;
			p1ptr = p1ptr->next;
			ptrn = new node;
			if (start == NULL)
				start = ptrn;
			ptrn->coe = coe;
			ptrn->exp = exp;
			ptrn->next = NULL;
			ptrp->next = ptrn;
			ptrp = ptrn;
		}
	}
}

void polynomial::multiply(polynomial p1, polynomial p2)
{
	struct node *p1ptr, *p2ptr, *ptri, *ptrj;
	int exp, coe;
	ptrn = ptrp = start = NULL;
	p1ptr = p1.start;
	p2ptr = p2.start;
	while (p1ptr != NULL)   // Start multiplying
	{
		p2ptr = p2.start;
		while (p2ptr != NULL)
		{
			ptrn = new node;
			ptrn->next = NULL;
			if (start == NULL)
				start = ptrn;
			if (ptrp != NULL)
				ptrp->next = ptrn;
			ptrn->coe = p1ptr->coe*p2ptr->coe;
			ptrn->exp = p1ptr->exp + p2ptr->exp;
			ptrp = ptrn;
			p2ptr = p2ptr->next;
		}
		p1ptr = p1ptr->next;
	}                    // end of multiplication
	ptri = ptrj = start;     // Normalising
	ptrn = ptrp = start = NULL;
	while (ptri != NULL)
	{
		exp = ptri->exp;
		coe = ptri->coe;
		ptrj = ptri->next;
		while (ptrj != NULL)
		{
			if (ptrj->exp == ptri->exp)
			{
				coe = coe + ptrj->coe;
				ptrj->coe = 0;//ptrj_p->next=ptrj->next;
			}
			ptrj = ptrj->next;
		}
		if (coe != 0)
		{
			ptrn = new node;
			ptrn->next = NULL;
			if (start == NULL)
				start = ptrn;
			if (ptrp != NULL)
				ptrp->next = ptrn;
			ptrn->coe = coe;
			ptrn->exp = exp;
			ptrp = ptrn;
		}
		ptri = ptri->next;
	}
	return;
}

void polynomial::sort()
{
	struct node *ptri, *ptrj;
	int coe, exp;
	ptri = ptrj = start;
	while (ptri->next != NULL)
	{
		ptrj = ptri->next;
		while (ptrj != NULL)
		{
			if (ptri->exp)
			{
				coe = ptri->coe;
				exp = ptri->exp;
				ptri->coe = ptrj->coe;
				ptri->exp = ptrj->exp;
				ptrj->coe = coe;
				ptrj->exp = exp;
			}
			ptrj = ptrj->next;
		}
		ptri = ptri->next;
	}
	return;
}

int polynomial::calculate(int x) {
	struct node *ptr;
	ptr = start;
	int answer = 0;
	while (ptr != NULL)
	{
		answer += (ptr->coe * exponent(x, ptr->exp));
		ptr = ptr->next;
	}
	return answer;
}

int exponent(int number, int exp) {
	int temp = 1;
	for (int i = 0; i < exp; i++)
		temp *= number;
	return temp;
}

int main()
{
	system("cls");
	polynomial p1, p2, sum, diff, product;
	int x;
	cout << "\n First Polynomial : ";
	p1.get();
	cout << "\n\n Second polynomial.";
	p2.get();
	cout << "\n\n Enter X : ";
	cin >> x;
	system("cls");
	cout << "\n First : ";
	p1.show();
	cout << "\n\n second : ";
	p2.show();
	cout << "\n\n Sum : ";
	sum.add(p1, p2);
	sum.show();
	cout << "\n\n Difference : ";
	diff.subtract(p1, p2);
	diff.show();
	cout << "\n\n product : ";
	product.multiply(p1, p2);
	product.sort();
	product.show();
	cout << "\n\n Calculated : ";
	cout << p1.calculate(x);
	cout << "\n\n ";
	system("pause");
	return 0;
}
