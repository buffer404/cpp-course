#include <iostream>
#include <typeinfo>
using namespace std;
int f() {
	int var1 = 1;
	float var2 {3};
	cout << typeid(var1).name() << '(' << var1 << ") " << "+" << ' ' << typeid(var2).name() << '(' << var2 << ") = " << typeid(var1 +var2).name() << '(' << (var1 + var2) << ')' << endl;
	cout << typeid(var1).name() << '(' << var1 << ") " << "-" << ' ' << typeid(var2).name() << '(' << var2 << ") = " << typeid(var1 -var2).name() << '(' << (var1 - var2) << ')' << endl;
	cout << typeid(var1).name() << '(' << var1 << ") " << "/" << ' ' << typeid(var2).name() << '(' << var2 << ") = " << typeid(var1 /var2).name() << '(' << (var1 / var2) << ')' << endl;
	cout << typeid(var1).name() << '(' << var1 << ") " << "*" << ' ' << typeid(var2).name() << '(' << var2 << ") = " << typeid(var1 *var2).name() << '(' << (var1 * var2) << ')' << endl;
	cout << typeid(var1).name() << '(' << var1 << ") " << "|" << ' ' << typeid(var2).name() << '(' << var2 << ") = " << typeid(var1 |var2).name() << '(' << (var1 | var2) << ')' << endl;
	return 0;
}
