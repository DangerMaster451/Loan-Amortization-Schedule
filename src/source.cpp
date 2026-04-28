#include "loan.h"
#include "CSVService.h"
#include <iostream>
#include <vector>

int main()
{
	Loan l = Loan(30000, 5, 4.2);
	std::vector<Payment*> payments = l.generatePayments();

	for (Payment* p : payments)
	{
		std::cout << p->toCSVRow() << std::endl;
	}

	CSVService::generateFile(payments, "test.csv");
	
	return 0;
}