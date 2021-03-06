// prob1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <vector>
#include <fstream>
#include <iostream>

using namespace std;

vector <int> v;

int bs(int left, int right) {
	if (left > right)
		return -1;

	int mediana = (left + right) / 2;
	if (v[mediana] == mediana)
		return mediana;
	if (v[mediana] > mediana) {
		right = mediana;
		bs(left, right);
	}
	if (v[mediana] < mediana) {
		left = mediana + 1;
		bs(left, right);
	}
}

int main() {

	ifstream file("date.txt");
	int n; file >> n;

	v.assign(n + 1, 0);
	for (int i = 0; i < n; i++)
		file >> v[i];
	int result = bs(0, n);
	if (result == -1)
		cout << "Nu exista valoarea." << endl;
	else
		cout << result << endl;

	cin.ignore();
	return 0;
}

