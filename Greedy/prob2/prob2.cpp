// prob2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <vector>
#include <algorithm>
#include <iostream>
#include <fstream>

using namespace std;

struct event {
	int index;
	int length;
	int deadline;
};

vector <event> vect;

bool compare(event a, event b) {
	if (a.deadline < b.deadline)
		return true;
	if (a.deadline == b.deadline && a.length > b.length) 
		return true;
	return false;
}

int main() {

	ifstream file("events.txt");
	int n; file >> n;
	event x;

	for (int i = 0; i < n; i++) {
		file >> x.length >> x.deadline;
		x.index = i + 1;
		vect.push_back(x);
	}

	sort(vect.begin(), vect.end(), compare);

	int time, maxDelay;
	time = maxDelay = 0;

	for (int i = 0; i < n; i++) {
		time += vect[i].length;
		cout << "activitatea " << vect[i].index << ": intervalul " << time - vect[i].length << " " << time << " intarziere " << time - vect[i].deadline << endl;
		if (time - vect[i].deadline > maxDelay)
			maxDelay = time - vect[i].deadline;
	}

	cout << "Intarziere planificare " << maxDelay << endl;

	cin.ignore();
	return 0;
}

