// prob1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <vector>

using namespace std;

void findPeak(vector<int> input, int left, int right) {
	int med = (right + left) / 2;
	if (left == right) {
		cout << "Mountain peak: "<<input[left] << endl;
		return;
	}

	if (input[med] < input[med + 1])
		findPeak(input, med + 1, right);
	else
		findPeak(input, left, med);
}

int main()
{
	vector<int> input;
	int n; cin >> n;
	cout << "Now give me the numbers: " << endl;

	for (int i = 0; i < n; i++) {
		int x; cin >> x;
		input.push_back(x);
	}
	
	findPeak(input, 0, input.size()-1);

	cin.ignore();
	cin.ignore();
    return 0;
}

