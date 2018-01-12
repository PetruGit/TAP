#include <iostream>

using namespace std;

struct element {
    int val;
    float p;
};

void Swap(element &a, element &b) {
    element temp = a;
    a = b;
    b = temp;
}

int Split(element elements[], int left, int right) {
    element e = elements[right], aux;
    int i = left, j;
    for(j = left; j <= right - 1; j++) {
        if(elements[j].val <= e.val) {
            Swap(elements[j], elements[i]);
            i++;
        }
    }
    Swap(elements[j], elements[i]);
    return i;
}

void print(element elements[], int len) {
    for(int i = 1; i <= len; i++) {
        cout << elements[i].val << " ";
    }
    cout<<endl<<endl;
}

void med(element *elements, int left, int right, int m) {
    if(m >= 1 && m <= right - left + 1) {
        int pos = Split(elements, left, right), i;
        if(pos == right) {
            pos = Split(elements, left, right - 1);
        }
        /// calculam ponderile Stanga si Dreapta
        float leftSum = 0, rightSum = 0;
        for(i = left; i <= right; i++) {
            if(i < pos) {
                leftSum += elements[i].p;
            }
            if(i > pos) {
                rightSum += elements[i].p;
            }
        }

        /// am gasit mediana ponderata
        if(leftSum < 0.5 && rightSum <= 0.5) {
            cout << "Mediana este: " << elements[pos].val <<" de pondere "<< elements[pos].p<< endl;
            return;
        }
        else if(leftSum >= 0.5) { /// mediana e la stanga
            elements[pos].p += rightSum;
            med(elements, left, pos, m);
        }
        else {                    /// mediana e la dreapta
            elements[pos].p += leftSum;
            med(elements, pos, right, m - pos + left - 1);
        }
        return;
    }
    return;
}

int main()
{
    int len, mid;
    cout<<"Numarul de elemente = "; cin >> len;

    element *elements = new element[len+1];
    for(int i = 1; i <= len; i++)
        cin >> elements[i].val >> elements[i].p;

    mid = len / 2;
    med(elements, 1, len, mid);

    return 0;
}
