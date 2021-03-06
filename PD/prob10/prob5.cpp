#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>

using namespace std;
typedef int* vect;
typedef vect* matrix;

struct activity {
	int g, d, t;
	int index;
};

int min(int a, int b) {
	return (a < b) ? a : b;
}

int max(int a, int b) {
	return (a > b) ? a : b;
}

void print(matrix mat, int n, int m) {
	for (int i = 0; i <= n; i++) {
		for (int j = 0; j <= m; j++)
			cout << mat[i][j] << " ";
		cout << endl;
	}
}

bool compByDeadline(activity a1, activity a2) {
	return (a1.d < a2.d) ? true : false;
}

void printOutput(vector<activity> activities, matrix mat, int n, int m, int i, int t) {
	if (i == 0) return;
	if (mat[i][t] == mat[i - 1][t])
		printOutput(activities, mat, n, m, i - 1, t);
	else {
		int ti = min(t, activities[i - 1].d) - activities[i - 1].t;
		printOutput(activities, mat, n, m, i - 1, ti);
		cout << "Schedule activity " << activities[i - 1].index << " at time " << ti << endl;
	}
}

int main()
{
	vector<activity> activities;

	ifstream file("activities.txt");
	int nr; file >> nr;

	for (int i = 0; i < nr; i++) {
		activity a;
		file >> a.g >> a.d >> a.t;
		a.index = i + 1;
		activities.push_back(a);
	}

	// sortez crescator dupa deadline
	sort(activities.begin(), activities.end(), compByDeadline);
	int maxDeadline = activities[nr - 1].d;

	matrix mat = new vect[nr + 1];
	for (int i = 0; i <= nr; i++)
		mat[i] = new int[maxDeadline + 1];

	// initializez prima linie la '0'
	for (int i = 0; i <= maxDeadline; i++)
		mat[0][i] = 0;

	// completez matricea pe linii
	for (int i = 1; i <= nr; i++)
		for (int t = 0; t <= maxDeadline; t++) {
			int ti = min(t, activities[i - 1].d) - activities[i - 1].t;
			if (ti < 0)
				mat[i][t] = mat[i - 1][t];
			else
				mat[i][t] = max(mat[i - 1][t], activities[i-1].g + mat[i - 1][ti]);
		}

	print(mat,nr,maxDeadline);
	printOutput(activities, mat, nr, maxDeadline, nr, maxDeadline);

	cin.ignore();
	return 0;
}

