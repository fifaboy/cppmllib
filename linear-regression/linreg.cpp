/*
author: Masum Billal
Algorithm: Linear regression (least squares version for 2d points)
*/

#include <bits/stdc++.h>

#define MAX 1000001

using namespace std;

#include "linreg.h"
/*assumes that at least there are two distinct points in the set*/

double denominator(Point P[], int n, double avg_x){
	double sum = 0;
	for (int i = 0; i < n; i++){
		double dx = P[i].x-avg_x;
		dx *= dx;
		sum += dx;
	}
	return sum;
}

double numerator(Point P[], int n, double avg_x, double avg_y){
	double sum = 0;
	for (int i = 0; i < n; i++){
		double dx = P[i].x-avg_x;
		double dy = P[i].y-avg_y;
		sum += (dx*dy);
	}
	return sum;
}

double slope(Point P[], int n, double avg_x, double avg_y){
	return numerator(P, n, avg_x, avg_y)/denominator(P, n, avg_x);
}

pair < double, double > linear_regression(Point P[], int n, double avg_x, double avg_y){
	double m = slope(P, n, avg_x, avg_y);
	double b = avg_y-m*avg_x;
	return pair < double, double > (m, b);
}

Point P[MAX];

int main(){
	int n;
	cin >> n;
	for (int i = 0; i < n; i++){
		cin >> P[i].x >> P[i].y;
	}
	double avg_x = averageX(P, n);
	double avg_y = averageY(P, n);
	pair < double, double> res = linear_regression(P, n, avg_x, avg_y);
	cout << res.first << " " << res.second << endl;
	
	return 0;
}