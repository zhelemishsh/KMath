#include <iostream>
#include <string>

using namespace std;

long pow(long num, long power) {
	long res = 0;
	for (int i = 1; i <= power; i++) {
		res *= num;
	}
	return res;
}

void toBin(string &str, long num) {
	if (num > 0) {
		toBin(str, num / 2);
		if (num % 2 == 0) {
			str += '0';
		}
		else {
			str += '1';
		}
	}
}

void addNulls(string &str, long len) {
	while (str.length() != len) {
		str += '0';
	}
}

void printPerm(string str) {
	cout << "{ ";
	for (long j = 0; j < str.length(); j++) {
		if (str[j] == '1') {
			cout << j << ' ';
		}
	}
	cout << "}\n";
}

int main() {
	long n;
	cin >> n;
	for (long i = 0; i <= pow(2, n); i++) {
		string str;
		toBin(str, i);
		addNulls(str, n);
		printPerm(str);
	}
	return 0;
}