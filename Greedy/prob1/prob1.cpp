// prob1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <cstdio>
#include <vector>
#include <algorithm>
#include <stack>
#include <fstream>
#include <iostream>

using namespace std;

struct interval {
	int stanga, dreapta;
};

vector <interval> v;
stack <interval> st;

bool sortare(interval a, interval b) {
	if (a.stanga < b.stanga)
		return true;
	else if (a.stanga == b.stanga && a.dreapta < b.dreapta) 
		return true;
	return false;
}

void print(stack<interval> st) {
	if (st.empty())
		return;
	interval aux = st.top();
	st.pop();
	print(st);
	cout << aux.stanga << " " << aux.dreapta << endl;
}

int main() {

	ifstream in("intervals.txt");

	int a, b;
	int n;
	interval x;
	
	in >> a >> b >> n;

	for (int i = 0; i < n; i++) {
		in >> x.stanga >> x.dreapta;
		if (x.dreapta < a || x.stanga > b)
			continue;
			v.push_back(x);
	}

	sort(v.begin(), v.end(), sortare);

	if (v.size() == 0 || v[0].stanga > a) {
		cout << "No suitable intervals" << endl;
		return 0;
	}

	interval top;
	st.push(v[0]);

	for (int i = 1; i < n; i++) {
		top = st.top();
		if (v[i].stanga > top.dreapta) {
			cout << "No suitable intervals" << endl;
			return 0;
		}	

		if (v[i].stanga == top.stanga && v[i].dreapta != top.dreapta) {
			st.pop();
			st.push(v[i]);
			continue;
		}
		else if (v[i].dreapta > top.dreapta) {
			st.pop();
			if (st.empty()) {
				if (v[i].stanga <= a)
					st.push(v[i]);
				else {
					st.push(top);
					st.push(v[i]);
				}
					
				
				continue;
			}
			else if (v[i].stanga <= st.top().dreapta) {
				st.push(v[i]);
				continue;
			}
				
			st.push(top);
			st.push(v[i]);
		}
	}

	if (st.top().dreapta < b)
		cout<<"No suitable intervals" << endl;
	else {
		print(st);
	}

	cin.ignore();
	cin.ignore();
	return 0;
}

