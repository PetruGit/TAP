// prob3.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

struct info {
	int codeIndex;
	int prev;
};

ofstream g("date.out");

int max(int a, int b) {
	return (a < b) ? b : a;
}

void readData(vector<string> &smallStrings, string &bigString) {
	string sampleString;
	
	sampleString = '0';
	smallStrings.push_back(sampleString);
	sampleString = '1';
	smallStrings.push_back(sampleString);

	ifstream date("date.in.txt");
	int n;  date >> n;
	for (int i = 0; i < n; i++) {
		date >> sampleString;
		smallStrings.push_back(sampleString);
	}
	date.close();

	ifstream code("cod.in.txt");
	code >> bigString;
	code.close();
}

bool compatible(string smallString, int startPosition, string bigString) {
	if (startPosition < 0)
		return false;

	int j = 0;
	for (int i = startPosition; i < startPosition + smallString.length(); i++) {
		if (smallString[j] != bigString[i]) {
			return false;
		}
		j++;
	}
	return true;
}

void display(string bigString, vector<string> smallStrings, info *codeAndIndex, int p) {
	if (p <= 0)
		return;

	display(bigString, smallStrings, codeAndIndex, codeAndIndex[p].prev);
	cout << smallStrings[codeAndIndex[p].codeIndex] << " ";
}

void decompose(vector<string> smallStrings, string bigString) {
	string aux;
	int n = bigString.length();
	int *d = new int[n + 1];
	info *codeAndPrev = new info[n + 1];

	d[0] = 0; 
	codeAndPrev[1].codeIndex = (bigString[0] == '0') ? 0 : 1;
	codeAndPrev[1].prev = -1;

	for (int rightIndex = 1; rightIndex <= n; rightIndex++) {
		int min = numeric_limits<int>::max();
		int pos, index;

		for (int i = 0; i < smallStrings.size(); i++)
			if (compatible(smallStrings[i], rightIndex - smallStrings[i].length(), bigString)) {
				int decNr = d[rightIndex - smallStrings[i].length()] + 1;
				if (decNr < min) {
					min = decNr;
					pos = rightIndex - smallStrings[i].length();
					index = i;
				}
			}
		d[rightIndex] = min;
		codeAndPrev[rightIndex].prev = pos;
		codeAndPrev[rightIndex].codeIndex = index;
	}

	display(bigString, smallStrings, codeAndPrev, n);
}

int main()
{
	vector<string> smallStrings;
	string bigString;
	readData(smallStrings, bigString);
	decompose(smallStrings, bigString);

	cin.ignore();
	return 0;
}