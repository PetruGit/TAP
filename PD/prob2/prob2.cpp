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

	// completez prima linie

	for (int j = 2; j < m + 1; j++)
		mat[1][j] += mat[1][j - 1];

	// completez prima coloana

	for (int i = 2; i < n + 1; i++)
		mat[i][1] += mat[i - 1][1];

	print(mat, n + 1, m + 1);

	// completez si restul matricei

	for (int i = 2; i < n + 1; i++)
		for (int j = 2; j < m + 1; j++)
			mat[i][j] += (mat[i - 1][j] > mat[i][j - 1]) ? mat[i - 1][j] : mat[i][j - 1];

	print(mat, n + 1, m + 1);

	// afisam maximul format pe ultima linie

	int maxim = 1;
	for (int j = 1; j < m + 1; j++)
		if (mat[m][j] > mat[m][maxim])
			maxim = j;
	cout << mat[m][maxim] << endl;

	// cautam drumul inapoi, pornind de la maximul gasit
	traseu tr = new point[n + m - 1];

	// ultimul punct va fi maximul gasit
	point p;
	p.x = m;
	p.y = maxim;

	tr[n + m - 2] = p;

	// adaugam restul punctelor in traseu. Adaugam maximul dintre 'stanga' si 'sus'.
	// adaugarea se face de la sfarsit spre inceput

	for (int i = n + m - 3; i >= 0; i--) {
		if (mat[p.x - 1][p.y] > mat[p.x][p.y - 1])
			p.x--;
		else
			p.y--;
		tr[i].x = p.x;
		tr[i].y = p.y;
	}

	// afisam traseul

	cout << "Traseul este: " << endl;
	for (int i = 0; i<n + m - 1; i++)
		cout << tr[i].x << " " << tr[i].y << endl;

	cin.ignore();
	return 0;
}

