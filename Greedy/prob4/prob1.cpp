// prob1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

struct cub {
	float lat;
	int cul;
	int index;
};

bool compare1(cub c1, cub c2) {
	return c1.lat>c2.lat;
}

void print(vector<int> vect) {
	for (int i = 0; i<vect.size(); i++)
		cout << vect[i] << " ";
	cout << endl;
}

int main()
{
	ifstream f("cuburi.txt");
	int n, p; f >> n >> p;
	vector<cub> vect;
	for (int i = 0; i<n; i++) {
		int l, c;
		f >> l >> c;
		cub x;
		x.lat = l;
		x.cul = c;
		x.index = i + 1;
		vect.push_back(x);
	}

	// sortam vectorul descrescator dupa latura
	sort(vect.begin(), vect.end(), compare1);

	vector<int> indexi;
	int lastColor = vect[0].cul;
	float lastLat = vect[0].lat;
	float sum = lastLat;
	indexi.push_back(vect[0].index);

	// parcurgem vectorul sortat si asezam cubul urmator daca are culoare diferita
	for (int i = 1; i<vect.size(); i++)
		if (vect[i].cul != lastColor) {
			indexi.push_back(vect[i].index);
			lastColor = vect[i].cul;
			lastLat = vect[i].lat;
			sum += vect[i].lat;
		}

	cout << sum << endl;
	print(indexi);

	cin.ignore();
	return 0;
}

