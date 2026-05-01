#include "loan.h"
#include <vector>
#include <cmath>
#include <iostream>
#include <sstream>
#include <iomanip>

void Payment::display()
{
	std::cout << "Payment: " << VALUE << "\n";
	std::cout << "Intrest: " << INTEREST << "\n";
	std::cout << "Remaining Principal: " << REMAINING_PRINCIPAL << "\n";
}

std::string Payment::toCSVRow()
{
	std::ostringstream oss;
		oss << std::fixed << std::setprecision(2)
    	<< PAYMENT_NUMBER << ","
    	<< VALUE << ","
    	<< (VALUE - INTEREST) << ","
    	<< INTEREST << ","
   		<< REMAINING_PRINCIPAL;

return oss.str();
}

std::string Payment::toHTMLRow()
{
	std::ostringstream oss;
		oss << std::fixed << std::setprecision(2)
		<< "<tr>"
    	<< "<td>" << PAYMENT_NUMBER << "</td>"
    	<< "<td>" << VALUE << "</td>"
    	<< "<td>" << (VALUE - INTEREST) << "</td>"
    	<< "<td>" << INTEREST << "</td>"
   		<< "<td>" << REMAINING_PRINCIPAL << "</td>"
		<< "</tr>";

return oss.str();
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
		payments.push_back(new Payment(PAYMENT_VALUE, intrest, remainingPrincipal, i+1));
	}
	return payments;
}