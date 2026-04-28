#include "loan.h"
#include "services.h"
#include <iostream>
#include <vector>


int main()
{
	Loan l = Loan(30000, 5, 4.2);
	std::vector<Payment*> payments = l.generatePayments();

	for (Payment* p : payments)
	{
		p->toCSVRow();
	}

	CSVService::generateFile(payments, "test.csv");

	ServerService::run();
	
	return 0;
}