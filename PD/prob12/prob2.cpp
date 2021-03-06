// prob2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <fstream>

using namespace std;

struct point {
	int x, y;
};

typedef int* vect;
typedef vect* matrice;
typedef point* traseu;

void print(matrice mat, int n, int m) {
	for (int i = 1; i<n; i++) {
		for (int j = 1; j<m; j++)
			cout << mat[i][j] << " ";
		cout << endl;
	}
	cout << endl;
}

int max(int a, int b, int c) {
	if (a > b)
		if (a > c)
			return a;
		else
			return c;
	else if (b < c)
		return c;
	return b;
}

int main()
{
	ifstream file("matrice.txt");
	int n, m;
	file >> n >> m;

	// citesc si aloc matricea
	matrice mat = new vect[n + 2];
	for (int i = 0; i < n + 2; i++)
		mat[i] = new int[m + 2];

	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
			file >> mat[i][j];

	print(mat, n + 1, m + 1);

	// bordez matricea cu '-1'

	for (int i = 0; i < n + 2; i++)
		mat[i][0] = mat[i][m + 1] = -1;
	for (int i = 0; i < m + 2; i++)
		mat[0][i] = mat[n + 1][i] = -1;

	// completez si restul matricei

	for (int j = 2; j < m + 1; j++)
		for (int i = 1; i < n + 1; i++)
		 {
			int maxim = max(mat[i - 1][j - 1], mat[i][j - 1], mat[i + 1][j - 1]);
			if (maxim == mat[i - 1][j - 1])
				mat[i][j] += mat[i - 1][j - 1];
			else if (maxim == mat[i][j - 1])
				mat[i][j] += mat[i][j - 1];
			else
				mat[i][j] += mat[i + 1][j - 1];
		}

	print(mat, n + 1, m + 1);

	// afisam maximul format pe ultima linie

	int maxim = 1;
	for (int i = 1; i < n + 1; i++)
		if (mat[i][m] > mat[maxim][m])
			maxim = i;
	cout << mat[maxim][m] << endl;

	// cautam drumul inapoi, pornind de la maximul gasit
	traseu tr = new point[m];

	// ultimul punct va fi maximul gasit
	point p;
	p.x = maxim;
	p.y = m;

	tr[m - 1] = p;

	// adaugam restul punctelor in traseu. Adaugam maximul dintre 'stanga' si 'sus'.
	// adaugarea se face de la sfarsit spre inceput

	for (int i = m - 2; i >= 0; i--) {
		int maxim = max(mat[p.x - 1][p.y - 1], mat[p.x][p.y - 1], mat[p.x + 1][p.y]);
		if (mat[p.x - 1][p.y - 1] == maxim) {
			p.x--; p.y--;
		}
		else if (mat[p.x][p.y - 1] == maxim)
			p.y--;
		else
			p.x++;

		tr[i].x = p.x;
		tr[i].y = p.y;
	}

	// afisam traseul

	cout << "Traseul este: " << endl;
	for (int i = 0; i<m; i++)
		cout << tr[i].x << " " << tr[i].y << endl;

	cin.ignore();
	return 0;
}

