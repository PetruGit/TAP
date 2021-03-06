// prob3.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

struct activ {
	float profit;
	int t;
	int index;
};

bool compare3(activ a1, activ a2) {
	return a1.t>a2.t;
}

struct compare3_4 {
	bool operator()(const activ& a1, const activ& a2) {
		return a1.profit<a2.profit;
	}
};

void print(vector<activ> vect) {
	for (int i = 0; i<vect.size(); i++)
		cout << vect[i].profit << " " << vect[i].t << endl;
	cout << endl;
}

int main()
{
	ifstream file("activitati.txt");
	int n; file >> n;

	// citim activitatile
	vector<activ> vect;
	for (int i = 0; i<n; i++) {
		activ a;
		file >> a.profit >> a.t;
		a.index = i + 1;
		vect.push_back(a);
	}

	sort(vect.begin(), vect.end(), compare3);
	print(vect);
	int time = vect.begin()->t;

	priority_queue<activ, vector<activ>, compare3_4> pq;
	vector<activ> result;
	int sum = 0;

	int i = 0;
	// adaugam activitatile cu deadline maxim;
	while (vect[i].t == time) {
		pq.push(vect[i]);
		i++;
	}

	while (time) {
		sum += pq.top().profit;
		result.push_back(pq.top());
		pq.pop();
		time--;
		while (vect[i].t == time) {
			pq.push(vect[i]);
			i++;
		}
	}

	cout << sum << endl;
	for (int i = 0; i<result.size(); i++)
		cout << result[i].index << " ";
	cout << endl;

	cin.ignore();
    return 0;
}

