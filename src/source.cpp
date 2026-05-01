#include <iostream>
#include <vector>
#include <cmath>
#include <sstream>
#include <iomanip>
#include <fstream>

class Payment {
private:
	const double VALUE;
	const double INTEREST;
	const double REMAINING_PRINCIPAL;
	const int PAYMENT_NUMBER;
public:
	Payment(double value, double interest, double remainingPrincipal, int paymentNumber) :
		VALUE(value), INTEREST(interest), REMAINING_PRINCIPAL(remainingPrincipal), PAYMENT_NUMBER(paymentNumber)
	{};

	void display();
	std::string toCSVRow();
};

class Loan {
private:
	const double PRINCIPAL;
	const int TERM;
	const double APR;
	const int TOTAL_MONTHS;
	const double RATE;
public:
	Loan(double principal, int term, double APR) :
		PRINCIPAL(principal), TERM(term), APR(APR),
		TOTAL_MONTHS(term * 12), RATE(APR / 1200.0)
	{};

	double getPaymentValue();
	std::vector<Payment*> generatePayments();
};

void generateFile(std::vector<Payment*> payments, std::string fileName);

int main()
{
	double principle;
	int term;
	double APR;
	std::cout << "Loan Amortization App" << std::endl;
	std::cout << "Check out the github to see the full version!\n";
	std::cout << "https://github.com/DangerMaster451/Loan-Amortization-Schedule" << std::endl << std::endl;

	std::cout << "Principle: ";
	std::cin >> principle;
	std::cout << "Term (Years): ";
	std::cin >> term;
	std::cout << "APR: ";
	std::cin >> APR;

	Loan l = Loan(principle, term, APR);
	std::vector<Payment*> payments = l.generatePayments();

	for (Payment* p : payments) {
		p->display();
	
	}
	generateFile(payments, "loanSchedule.csv");
	return 0;
}

void Payment::display()
{
	std::ostringstream oss;
	oss << std::fixed << std::setprecision(2)
	<< "Payment: " << VALUE << "\n"
	<< "Interest: " << INTEREST << "\n"
	<< "Remaining Principal: " << REMAINING_PRINCIPAL << "\n";

	std::cout << oss.str();
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
	double interest = PRINCIPAL * RATE;

	for (int i = 0; i < TOTAL_MONTHS; i++)
	{
		interest = remainingPrincipal * RATE;
		remainingPrincipal -= PAYMENT_VALUE-interest;
		payments.push_back(new Payment(PAYMENT_VALUE, interest, remainingPrincipal, i+1));
	}
	return payments;
}

void generateFile(std::vector<Payment*> payments, std::string fileName)
{
    std::fstream fout;

    fout.open(fileName, std::ios::out);

    for (Payment* p : payments) {
        fout << p->toCSVRow() << std::endl;
    }
}