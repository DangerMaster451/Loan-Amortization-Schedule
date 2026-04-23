#include "loan.h"
#include <cmath>
#include <iostream>

Loan::Loan(double principal, int termInYears, double APR)
{
	this->principal = principal;
	this->termInYears = termInYears;
	this->APR = APR;
}

double Loan::getPrincipal()
{
	return this->principal;
}

int Loan::getTermInYears()
{
	return this->termInYears;
}

double Loan::getAPR()
{
	return this->APR;
}

int Loan::convertTermToMonths()
{
	return getTermInYears() * 12;
}

double Loan::convertAPRToRate()
{
	return getAPR() / 100.0 / 12.0;
}

double Loan::calculateIntrest()
{
	return getPrincipal() * convertAPRToRate();
}

double Loan::calculatePayment()
{
	double n = getPrincipal() * convertAPRToRate() * pow(1 + convertAPRToRate(), convertTermToMonths());
	double d = pow((1 + convertAPRToRate()), convertTermToMonths()) - 1;

	return n / d;
}

std::vector<Payment*> Loan::generatePayments()
{
	std::vector<Payment*> payments;
	double intrest = calculateIntrest();
	double total = calculatePayment();
	double remainingPrincipal = getPrincipal();
	Payment* p = new Payment(intrest, total, remainingPrincipal);
	for (int i = 0; i < convertTermToMonths(); i++)
	{
		intrest = p->getIntrest();
		total = p->getTotal();
		remainingPrincipal = p->getRemainingPrincipal();
		p = p->nextPayment();
	}
}

Payment::Payment(double intrest, double total, double remainingPricipal)
{
	this->intrest = intrest;
	this->total = total;
	this->remainingPrincipal = remainingPrincipal;
}

double Payment::getIntrest()
{
	return intrest;
}

double Payment::getTotal()
{
	return total;
}

double Payment::getRemainingPrincipal()
{
	return remainingPrincipal;
}

Payment* Payment::nextPayment()
{
	double intrest = loan.calculateIntrest();
	double payment = loan.calculatePayment();
	double remainingPrincipal = getRemainingPrincipal() - payment - intrest;
	return new Payment(intrest, payment, remainingPrincipal);
}

void Payment::display()
{
	std::cout << "Intrest: " << getIntrest() << std::endl;
	std::cout << "Total Payment: " << getTotal() << std::endl;
	std::cout << "Remaining Principal: " << getRemainingPrincipal() << std::endl;
}