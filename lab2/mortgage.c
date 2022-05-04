// Eamon Tracey
// Lab 2 mortgage.c

#include <stdio.h>

int main() {
	float principal, interest_rate, monthly_payment;
	int months = 0;
	printf("Mortgage Calculator\n\n");

	printf("Enter principal ($): ");
	scanf("%f", &principal);
	while (principal <= 0) {
		printf("ERROR: Please enter positive principal ($): ");
		scanf("%f", &principal);
	}

	printf("Enter interest rate (%%): ");
	scanf("%f", &interest_rate);
	while (interest_rate <= 0) {
		printf("ERROR: Please enter positive interest rate (%%): ");
		scanf("%f", &interest_rate);
	}
	interest_rate /= 1200;

	printf("Enter monthly payment: ");
	scanf("%f", &monthly_payment);
	while (monthly_payment <= 0) {
		printf("ERROR: Please enter positive monthly payment: ");
		scanf("%f", &monthly_payment);
	}

	if (monthly_payment < interest_rate * principal) {
		printf("ERROR: Monthly payment will never cover mortgage loan.\n");
		return 1;
	}

	float interest, payment, balance = principal, total;
	printf("\nMonths    Payment      Interest      Balance\n");
	while (balance != 0) {
		months++;
		interest = interest_rate * balance;
		balance += interest;
		payment = monthly_payment < balance ? monthly_payment : balance;
		balance -= payment;
		total += payment;
		printf("%4d     $ %8.2f     $ %8.2f     $ %8.2f", months, payment, interest, balance);
		printf("\n");
	}
	
	int years = months / 12;
	months %= 12;
	printf("\nYou paid a total of $%.2f over %d years and %d months.\n", total, years, months);
}
