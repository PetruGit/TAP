// prob1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

const int NMAX = 1000;

struct piesa {
	int left, right;
};

int maxLength[NMAX];
int pred[NMAX];
piesa pieces[NMAX];

int main() {

	ifstream file("pieces.txt");
	int n; file >> n;

	for (int i = 1; i <= n; i++) {
		file >> pieces[i].left >> pieces[i].right;
		maxLength[i] = 1;
	}

	int maxStringLength = 1;
	int maxApparitions = n;
	int maxLengthPosition = 1;

	for (int i = 2; i <= n; i++) {

		for (int j = i - 1; j >= 1; j--)
			if (pieces[j].right == pieces[i].left) {

				if (maxLength[j] + 1 >= maxLength[i]) {
					maxLength[i] = maxLength[j] + 1;
					pred[i] = j;

					if (maxLength[i] > maxStringLength) {

						maxStringLength = maxLength[i];
						maxApparitions = 1;
						maxLengthPosition = i;
					}
					else
						if (maxLength[i] == maxStringLength)
							maxApparitions++;
				}
			}
	}

	vector <piesa> result;
	int position = maxLengthPosition;
	while (position != 0) {

		result.push_back(pieces[position]);
		position = pred[position];
	}

	for (int i = result.size() - 1; i >= 0; i--)
		cout << result[i].left << result[i].right << endl;

	cout << maxApparitions;

	cin.ignore();
	return 0;
}

