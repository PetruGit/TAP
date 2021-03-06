// prob3.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <vector>
#include <iostream>
#include <fstream>

using namespace std;

const int max = 1000;
vector<int> subArray[max];

int binarySearch(int left, int right, int value) {
	int median, length;
	while (left < right) {
		median = (left + right) / 2;
		length = subArray[median].size() - 1;
		if (subArray[median][length] <= value)
			left = median + 1;
		else
			right = median;
	}
	return left;
}

int main() {

	ifstream file("array.txt");

	int n, x;
	int pos, subArrayNumber = 0;

	file >> n;

	for (int i = 0; i < n; i++) {
		file >> x;
		pos = binarySearch(0, subArrayNumber, x);
		if (pos == subArrayNumber) {
			subArrayNumber++;
			subArray[subArrayNumber - 1].push_back(x);
		}
		else
			subArray[pos].push_back(x);
	}

	for (int i = 0; i < subArrayNumber; i++) {
		for (int j = 0; j < subArray[i].size(); j++)
			cout << subArray[i][j] << " ";
		cout << endl;
	}

	cin.ignore();
	return 0;
}

