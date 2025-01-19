//Trey Wendell
//tdw0042
//Project 1
//Compile with g++ -o project1_Wendell_tdw0042 project1_Wendell_tdw0042.cpp
//Comp 3240
//github copilot was used to help write this code

/* Goals of program
calc months till loan is paid off
calc total amount of interest paid over lifetime of loan
calc remaining debt
*/

#include <iostream>
using namespace std;

int main() {
	
	float loan_Amount = -1;
	float interest = -1;
	float payment = -1;
	
	cout.setf(ios::fixed);
	cout.setf(ios::showpoint);
	cout.precision(2);


	
	while (loan_Amount <= 0) {
		cout << "\nLoan Amount: ";
		cin >> loan_Amount;
	}

	while (interest <= -1) {
		cout << "Interest Rate (% per year): ";
		cin >> interest;
	}

	float interest_rate = interest / 12 / 100;

	while (payment <= 0 || payment <= loan_Amount * interest_rate) {
		cout << "Monthly Payments: ";
		cin >> payment;
	}

	cout << endl;

	cout << "*****************************************************************\n"
	     << "\tAmortization Table\n"
	     << "*****************************************************************\n"
	     << "Month\tBalance\t  Payment\tRate\tInterest\tPrincipal\n";

	
	float interest_total = 0;
	int current_month = 0;

	while (loan_Amount > 0) {
		if (current_month == 0) {
			cout << current_month++ << "\t$" << loan_Amount;
			if (loan_Amount < 1000) cout << "\t";
			cout << "  N/A\t\tN/A\tN/A\t\tN/A\n";
		}
		else {
			float interest_payment = loan_Amount * interest_rate;
			float principal_payment = payment - interest_payment;
			loan_Amount -= principal_payment;
			interest_total += interest_payment;

			if (loan_Amount < 0) {
				principal_payment += loan_Amount;
				payment += loan_Amount;
				loan_Amount = 0;
			}

			cout << current_month++ << "\t$" << loan_Amount;
			if (loan_Amount < 1000) cout << "\t";
			cout << "  $" << payment << "\t" << interest_rate * 100 << "\t$" << interest_payment << "\t\t$" << principal_payment << "\n"; 
		}
	}

	cout << "****************************************************************\n";
	cout << "\nIt takes " << --current_month << " months to pay off "
	     << "the loan.\n"
	     << "Total interest paid is: $" << interest_total;
	cout << endl << endl;

	return 0;
}