#include <iostream>
#include <fstream>
#include <limits>
#include <math.h>
#include <vector>
#include <algorithm>

using namespace std;

struct Point{
    int x, y;
};
/// distanta intre 2 pcte
float dist(Point& p1, Point& p2){
    return sqrt((p1.x - p2.x)*(p1.x - p2.x) +(p1.y - p2.y)*(p1.y - p2.y));
}

/// compara Y a 2 pcte
bool compY(Point& a, Point& b){
        if (a.y > b.y)
            return true;
        return false;
}

/// compara X a 2 pcte
bool compX(Point& a, Point& b){
        if (a.x > b.x)
            return true;
        return false;
}

float middlePoints(vector<Point> strip, float d){
    int size = strip.size();
    float min = d;

    /// sort dupa y a punctelor din raza d
    sort(strip.begin(), strip.end(), compY);
    for (int i = 0; i < size; ++i)
        for (int j = i + 1; j < size && (strip[j].y - strip[i].y) < min; ++j)
            if (dist(strip[i], strip[j]) < min)
                min = dist(strip[i], strip[j]);

    return min;
}

float rec(vector<Point> points){
    int n = points.size();

    /// cazul elementar => calculam distanta minima
    if (n <= 3){
        float min = numeric_limits<float>::max();
        for (int i = 0; i < n; ++i)
            for (int j = i + 1; j < n; ++j)
                if (dist(points[i], points[j]) < min)
                    min = dist(points[i], points[j]);
        return min;
    }

    int mid = n / 2;
    Point midPoint = points[mid];
    float minLeft = rec(vector<Point>(points.begin(),points.begin() + mid) );
    float minRight = rec(vector<Point>(points.begin() + mid, points.end()));
    float d = min(minLeft, minRight); /// min dintre minimele celor 2 parti

    vector<Point> strip;
    for (int i = 0; i < n; i++) /// punctele din jurul medianei
    if (abs(points[i].x - midPoint.x) < d)
    strip.push_back(points[i]);

 return min(d, middlePoints(strip, d)); /// minimul dupa verificarea razei medianei
}

int main(){
    ifstream f("puncte.txt");
    int n;
    f >> n;
    vector<Point> points;
    for (int i = 1; i <= n; i++){
        Point pct;
        f >> pct.x >> pct.y;
        points.push_back(pct);
    }
    sort(points.begin(), points.end(), compX);
    cout << rec(points) << endl;

    return 0;
}


