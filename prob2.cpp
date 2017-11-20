#include <iostream>
#include <fstream>
#include <math.h>

using namespace std;
typedef int* vect;
typedef vect* matrice;

void print(matrice mat, int n){
    for(int i=1; i<=n; i++){
        for(int j=1; j<=n; j++)
            cout<<mat[i][j]<<" ";
        cout<<endl;
    }
    cout<<endl;
}

static int nr = 1;

void rec(matrice mat, int i, int j, int n, int x, int y){
    int holeNr = mat[x][y];
    if(n == 2){
        mat[i][j] = mat[i][j+1] = mat[i+1][j] = mat[i+1][j+1] = nr;
        nr++;
        mat[x][y]= holeNr;
        return;
    }

    int sit;
    if(x < i+n/2){
        if(y < j+n/2)
            sit = 1;
        else
            sit = 2;
    }else{
        if(y < j+n/2)
            sit = 3;
        else
            sit = 4;
    }

    switch(sit){
    case 1:
        mat[i+n/2-1][j+n/2] = mat[i+n/2][j+n/2-1] = mat[i+n/2][j+n/2] = nr;
        nr++;
        rec(mat, i, j, n/2 , x, y);
        rec(mat, i, j+n/2, n/2, i+n/2-1, j+n/2);
        rec(mat, i+n/2, j, n/2, i+n/2, j+n/2-1);
        rec(mat, i+n/2, j+n/2, n/2, i+n/2, j+n/2);
        return;
    case 2:
        mat[i+n/2-1][j+n/2-1] = mat[i+n/2][j+n/2-1] = mat[i+n/2][j+n/2] = nr;
        nr++;
        rec(mat, i, j, n/2, i+n/2-1, j+n/2-1);
        rec(mat, i, j+n/2, n/2, x, y);
        rec(mat, i+n/2, j, n/2, i+n/2, j+n/2-1);
        rec(mat, i+n/2, j+n/2, n/2, i+n/2, j+n/2);
        return;
    case 3:
        mat[i+n/2-1][j+n/2-1] = mat[i+n/2-1][j+n/2] = mat[i+n/2][j+n/2] = nr;
        nr++;
        rec(mat, i, j, n/2, i+n/2-1, j+n/2-1);
        rec(mat, i, j+n/2, n/2, i+n/2-1, j+n/2);
        rec(mat, i+n/2, j, n/2, x, y);
        rec(mat, i+n/2, j+n/2, n/2, i+n/2, j+n/2);
        return;
    case 4:
        mat[i+n/2-1][j+n/2-1] = mat[i+n/2-1][j+n/2] = mat[i+n/2][j+n/2-1] = nr;
        nr++;
        rec(mat, i, j, n/2, i+n/2-1, j+n/2-1);
        rec(mat, i, j+n/2, n/2, i+n/2-1, j+n/2);
        rec(mat, i+n/2, j, n/2, i+n/2, j+n/2-1);
        rec(mat, i+n/2, j+n/2, n/2, x, y);
        return;
    }
}

int main()
{
    ifstream f("date.txt");
    int p; f>>p;
    int hole_i, hole_j; f>>hole_i>>hole_j;
    int n= pow(2,p);

    matrice mat = new vect[n+1];
    for(int i=1;i<=n;i++)
        mat[i] = new int[n+1];

    for(int i=1; i<=n; i++)
        for(int j=1; j<=n; j++)
            mat[i][j]=-1;
    mat[hole_i][hole_j]=0;

    rec(mat,1,1,n,hole_i,hole_j);
    print(mat, n);

    return 0;
}
