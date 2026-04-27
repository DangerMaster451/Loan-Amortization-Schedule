#include "loan.h"
#include<iostream>

int main()
{
	Loan l = Loan(30000, 5, 4.2);
	std::vector<Payment*> payments = l.generatePayments();

	for (Payment* p : payments)
	{
		p->display();
		std::cout << std::endl;
	}
	

	return 0;
}