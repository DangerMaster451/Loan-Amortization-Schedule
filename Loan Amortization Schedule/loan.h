#pragma once
#include<vector>

class Loan {
private:
	double principal;
	int termInYears;
	double APR;
public:
	Loan(double principal, int termInYears, double APR);
	double getPrincipal();
	int getTermInYears();
	double getAPR();
	int convertTermToMonths();
	double convertAPRToRate();
	double calculateIntrest();
	double calculatePayment();
	std::vector<Payment*> generatePayments();
};

class Payment {
private:
	double intrest;
	double total;
	double remainingPrincipal;
public:
	Payment(double intrest, double total, double remainingPrincipal);
	double getIntrest();
	double getTotal();
	double getRemainingPrincipal();
	Payment* nextPayment();
	void display();

};