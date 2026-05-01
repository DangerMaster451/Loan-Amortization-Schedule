#pragma once
#include <vector>

class Payment {
private:
	const double VALUE;
	const double INTREST;
	const double REMAINING_PRINCIPAL;
	const int PAYMENT_NUMBER;
public:
	Payment(double value, double intrest, double remainingPrincipal, int paymentNumber) :
		VALUE(value), INTREST(intrest), REMAINING_PRINCIPAL(remainingPrincipal), PAYMENT_NUMBER(paymentNumber)
	{};

	void display();
	std::string toCSVRow();
	std::string toHTMLRow();
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

