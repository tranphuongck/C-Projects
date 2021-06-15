/*
Compile: make money
Run: ./money
make money && ./money
*/

#include "base.h"


const double BITCOIN_USD = 4273.38; // 1 Bitcoin = 4273.38 USD
const double EURO_USD = 1.14; 		// 1 EURO = 1.14 USD
const double DKK_USD = 0.15; 		// 1 Dansk Krone (DKK) = 0.15 USD

enum Currency { BITCOIN, DOLLAR, EURO, DANSK_KRONE }; 
typedef enum Currency Currency;

struct Money { double amount; Currency currency; }; 
typedef struct Money Money;

// double, Currency -> Money
// Initialize a Money structure.
Money make_money(double amount, Currency currency) {
    Money m = { amount, currency };
    return m;
}

// int Money, Money, double -> bool
// Test wheather the actual value of the money is within +/- tolerance of the expected value of the money.
bool test_value(int line, Money a, Money e, double tolerance) {
    bool x = base_test_within_d(__FILE__, line, a.amount, e.amount, tolerance);
    bool u = base_test_equal_i(__FILE__, line, a.currency, e.currency);
    return x && u;
}

void print_money(Money m);

void print_money_test() {
    print_money(make_money(1234, DOLLAR));
    print_money(make_money(1.234, BITCOIN));
    print_money(make_money(1.34, EURO));
    print_money(make_money(27.50, DANSK_KRONE));
}

// Money -> void
// Print the ammount of money.
void print_money(Money m) {
    // todo: implement
	if(m.currency == DOLLAR){
		printf("%.2f $\n", m.amount);
	} else if(m.currency == BITCOIN){
		printf("%.8f Bitcoin\n", m.amount);
	} else if(m.currency == EURO){
		printf("%.2f Euro\n", m.amount);
	} else if(m.currency == DANSK_KRONE){
		printf("%.2f DKK\n", m.amount);
	}
}

Money to_currency(Money m, Currency currency);

void to_currency_test(void) {
    test_value(__LINE__, to_currency(make_money(1, BITCOIN), DOLLAR), make_money(4273.38, DOLLAR), 1e-3);
	test_value(__LINE__, to_currency(make_money(1000, DOLLAR), BITCOIN), make_money(0.234, BITCOIN), 1e-3);
	test_value(__LINE__, to_currency(make_money(100000, DANSK_KRONE), EURO), make_money(13157.895, EURO), 1e-3);
	test_value(__LINE__, to_currency(make_money(1000, EURO), DOLLAR), make_money(1140, DOLLAR), 1e-3);
	test_value(__LINE__, to_currency(make_money(10000, DANSK_KRONE), BITCOIN), make_money(0.351, BITCOIN), 1e-3);
    // todo: add tests (at least 5)
	
    
}


// Money, Currency -> Money
// Convert an amount of money to the given target currency.
Money to_currency(Money m, Currency target_currency) {
    // todo: implement
	if(m.currency == DOLLAR && target_currency == DANSK_KRONE){
		return make_money(m.amount/DKK_USD, DANSK_KRONE);
	}
	if (m.currency == DOLLAR && target_currency == BITCOIN){
		return make_money(m.amount/BITCOIN_USD, BITCOIN);
	}
	if (m.currency == DOLLAR && target_currency == EURO){
		return make_money(m.amount/EURO_USD, EURO);
	}
	
	if (m.currency == BITCOIN && target_currency == DOLLAR){
		return make_money(m.amount*BITCOIN_USD, DOLLAR);
	}
	if (m.currency == BITCOIN && target_currency == EURO){
		return make_money(m.amount*BITCOIN_USD/EURO_USD, EURO);
	}
	if (m.currency == BITCOIN && target_currency == DANSK_KRONE){
		return make_money(m.amount*BITCOIN_USD/DKK_USD, DANSK_KRONE);
	}
	
	if (m.currency == EURO && target_currency == DOLLAR){
		return make_money(m.amount*EURO_USD, DOLLAR);
	}
	if (m.currency == EURO && target_currency == BITCOIN){
		return make_money(m.amount*EURO_USD/BITCOIN_USD, BITCOIN);
	}
	if (m.currency == EURO && target_currency == DANSK_KRONE){
		return make_money(m.amount*EURO_USD/DKK_USD, DANSK_KRONE);
	}
	
	if (m.currency == DANSK_KRONE && target_currency == DOLLAR){
		return make_money(m.amount*DKK_USD, DOLLAR);
	}
	if (m.currency == DANSK_KRONE && target_currency == BITCOIN){
		return make_money(m.amount*DKK_USD/BITCOIN_USD, BITCOIN);
	}
	if (m.currency == DANSK_KRONE && target_currency == EURO){
		return make_money(m.amount*DKK_USD/EURO_USD, EURO);
	}
	
    return make_money(1, EURO);
}

int compare(Money m, Money v);

void compare_test(void) {
	test_equal_i(compare(make_money(1, BITCOIN), make_money(4273.38, DOLLAR)), 0);
	test_equal_i(compare(make_money(1, BITCOIN), make_money(1000, EURO)), 1);
	test_equal_i(compare(make_money(150, DANSK_KRONE), make_money(22.5, DOLLAR)), 0);
	test_equal_i(compare(make_money(600, EURO), make_money(800, DOLLAR)), -1);
	test_equal_i(compare(make_money(1000, DOLLAR), make_money(0.178, BITCOIN)), 1);
    // todo: add tests (at least 5)
    
}
    
// Money, Money -> int
// Compares two amounts of money. Returns 0 if the two amount of money are equal, 
// -1 if w is smaller than v and +1 otherwise.
int compare(Money m, Money v) {
    // todo: implement. May use the fabs function. fabs(double input) returns the absolute value of input.
    m = to_currency(make_money(m.amount, m.currency), v.currency);
	
	if(m.amount < v.amount){
		return -1;
	} else if(m.amount > v.amount){
		return 1;
	} else {
		return 0;
	}
    return 0;
}

int main(void) {
	printf("%.2f\n", 22.3);
	printf("Test print value \n");
	printf("**************************\n");
    print_money_test();
	printf("**************************\n");
	printf("Test to_currency\n");
    to_currency_test();
	printf("**************************\n");
	printf("Test compare_test\n");
    compare_test();
    return 0;
}
