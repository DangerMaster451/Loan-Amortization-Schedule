#include "loan.h"
#include<iostream>

int main()
{
	Loan l = Loan(30000, 5, 4.2);

	std::cout << "Interest: ";
	std::cout << l.calculateIntrest() << std::endl;
	std::cout << "Payment: ";
	std::cout << l.calculatePayment() << std::endl;

	return 0;
}