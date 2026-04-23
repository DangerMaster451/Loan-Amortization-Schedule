#include "loan.h"
#include <vector>
#include <cmath>
#include <iostream>

void Payment::display()
{
	std::cout << "Payment: " << VALUE << "\n";
	std::cout << "Intrest: " << INTREST << "\n";
	std::cout << "Remaining Principal: " << REMAINING_PRINCIPAL << "\n";
}

double Loan::getPaymentValue()
{
	double n = PRINCIPAL * RATE * pow((1 + RATE), TOTAL_MONTHS);
	double d = pow((1 + RATE), TOTAL_MONTHS) - 1;
	return n / d;
}


std::vector<Payment*> Loan::generatePayments()
{
	const double PAYMENT_VALUE = getPaymentValue();
	double remainingPrincipal = PRINCIPAL;
	std::vector<Payment*> payments;
	double intrest = PRINCIPAL * RATE;

	for (int i = 0; i < TOTAL_MONTHS; i++)
	{
		intrest = remainingPrincipal * RATE;
		remainingPrincipal -= PAYMENT_VALUE-intrest;
		payments.push_back(new Payment(PAYMENT_VALUE, intrest, remainingPrincipal));
	}
	return payments;
}
