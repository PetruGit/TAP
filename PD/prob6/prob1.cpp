// prob1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

static int nrTowers = 1;
static bool *isVisited;

struct Cube {
	int length;
	int color;
};

void print(vector<Cube> Cubes) {
	for (int i = 0; i < Cubes.size(); i++)
		cout << Cubes[i].length << " " << Cubes[i].color << endl;
	cout << endl;
}

void print(Cube c) {
	cout << c.length << " " << c.color << endl;
}

void print(vector<int> lengths) {
	for (int i = 0; i < lengths.size(); i++)
		cout << lengths[i] << " ";
	cout << endl << endl;
}

bool compare(Cube c1, Cube c2) {
	return (c1.length > c2.length) ? true : false;
}

bool compatible(Cube c1, Cube c2) {
	return (c1.length > c2.length && c1.color != c2.color) ? true : false;
}

int max(vector<int> vect) {
	int max = 0;
	for (int i = 0; i < vect.size(); i++)
		if (max < vect[i])
			max = vect[i];
	return max;
}

void recursiveWay(vector<Cube> Cubes, vector<int> lengths, int index) {
	if (lengths[index] == Cubes[index].length) {
		print(Cubes[index]);
		return;
	}

	for (int i = 0; i < index; i++)
		if (lengths[i] == lengths[index] - Cubes[index].length && compatible(Cubes[i], Cubes[index])) {
			recursiveWay(Cubes, lengths, i);
			print(Cubes[index]);
			break;
		}
}

void recursiveNrTowers(vector<Cube> Cubes, vector<int> lengths, int index) {
	int numberToFind = lengths[index] - Cubes[index].length;
	if (numberToFind == 0)
		return;

	int k = 0;
	for (int i = index - 1; i >= 0; i--)
		if (lengths[i] == numberToFind && compatible(Cubes[i],Cubes[index]) && !isVisited[i]) {
			recursiveNrTowers(Cubes, lengths, i);
			k++;
		}
	k--;
	nrTowers += k;
}

int main()
{
	ifstream file("cuburi.txt");
	int cubesNumber, colorRange;
	file >> cubesNumber >> colorRange;

	// aloc un vector de vizitati
	isVisited = new bool[cubesNumber];
	for (int i = 0; i < cubesNumber; i++)
		isVisited[i] = false;

	// READ
	vector<Cube> Cubes;
	for (int i = 0; i < cubesNumber; i++) {
		Cube c;
		file >> c.length >> c.color;
		Cubes.push_back(c);
	}

	// sortez descrescator cuburile dupa lungime
	sort(Cubes.begin(), Cubes.end(), compare);

	// initializez lungimile maxime chiar cu lungimile cuburilor respective
	vector<int> towerEndingIn;
	towerEndingIn.assign(cubesNumber, 0);
	for (int i = 0; i < cubesNumber; i++)
		towerEndingIn[i] = Cubes[i].length;

	// Parcurg sirul de lungimi maxime si pentru fiecare aleg maximul precedent ca baza
	for (int i = 0; i < cubesNumber; i++) {
		int max = i;
		for (int j = 0; j < i; j++)
			if (compatible(Cubes[j], Cubes[i]) && towerEndingIn[j] > towerEndingIn[max])
				max = j;
		(max != i) ? towerEndingIn[i] += towerEndingIn[max] : NULL;
	}

	print(towerEndingIn);

	// Apelez recursiv cu toate maximele gasite
	int maxim = max(towerEndingIn); cout << "maxim " << maxim << endl;
	int k = 0;
	for (int i = 0; i < towerEndingIn.size(); i++)
		if (maxim == towerEndingIn[i]) {
			k++;
			recursiveNrTowers(Cubes, towerEndingIn, i);
		}
	k--;
	nrTowers += k;

	// Afisez un turn de lungime maxima si numarul de turnuri
	for (int i = 0; i < towerEndingIn.size(); i++)
		if (towerEndingIn[i] == maxim) {
			recursiveWay(Cubes, towerEndingIn, i);
			break;
		}
	cout << "Number of maximal towers: "<< nrTowers << endl;

	cin.ignore();
	return 0;
}

