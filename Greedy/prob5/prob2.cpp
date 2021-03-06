// prob2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

typedef  int* vect;
typedef vect* matrice;

struct text {
	int len;
	int fr;
	int index;
};

struct fragment {
	int len;
	int index;
};

bool compare1(text t1, text t2) {
	return t1.fr / t1.len>t2.fr / t2.len;
}

bool compare2(fragment f1, fragment f2) {
	return f1.len<f2.len;
}

void print(vector<text> vect) {
	for (int i = 0; i<vect.size(); i++)
		cout << vect[i].len << " " << vect[i].fr << " " << vect[i].index << endl;
}

void prob2(const char *file) {
	ifstream f(file);
	int n; f >> n;
	vector<text> vect;

	// citire
	for (int i = 0; i<n; i++) {
		text t;
		f >> t.len >> t.fr;
		t.index = i + 1;
		vect.push_back(t);
	}

	// sortam vectorul de texte descrescator dupa ratia lungime/frecventa
	sort(vect.begin(), vect.end(), compare1);
	print(vect);

	for (int i = 0; i<vect.size(); i++)
		cout << vect[i].index << " ";
}

void prob2_b(const char *file) {
	ifstream f(file);
	int n, p; f >> n >> p;

	// salvam textele
	vector<fragment> v;
	for (int i = 0; i<n; i++) {
		fragment frag;
		f >> frag.len;
		frag.index = i + 1;
		v.push_back(frag);
	}

	// sortam crescator dupa lungime
	sort(v.begin(), v.end(), compare2);

	// creem matricea unde vor sta benzile
	matrice mat = new vect[p];
	for (int i = 0; i<p; i++)
		mat[i] = new int[(n / p) + 1];

	for (int i = 0; i<p; i++)
		for (int j = 0; j<n / p + 1; j++)
			mat[i][j] = 0;

	// adaugam pe rand textele pe benzi
	for (int j = 0; j<n / p + 1; j++)
		for (int i = 0; i<p && v.size(); i++) {
			mat[i][j] = v[0].index;
			v.erase(v.begin());
		}

	// print
	for (int i = 0; i<p; i++) {
		for (int j = 0; j<n / p + 1; j++) {
			if (mat[i][j] == 0)
				break;
			cout << mat[i][j] << " ";
		}
		cout << endl;
	}
}

int main()
{

	cin.ignore();
    return 0;
}

