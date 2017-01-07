/*
author: Masum Billal
Algorithm: K-means clustering (standard version for 2d points)
*/


#include <bits/stdc++.h>

using namespace std;

#define MAX 10001
#define VP vector < Point >
#define clr(a) memset(a, 0, sizeof(a))
#define read(a) freopen(a, "r", stdin)

struct Point {
	double x, y;
	Point (){}
	// structure for Point
	Point (double a, double b){
		x = a, y = b;
	}
	
	void print(){
		cout << x << " " << y << endl;
	}
} P[MAX];

Point average(VP V){
	int len = V.size();
	if (!len)	return Point(0.0, 0.0);
	double sumx = 0, sumy = 0;
	for (int i = 0; i < len; i++){
		sumx += V[i].x;
		sumy += V[i].y;
	}
	return Point(sumx/len, sumy/len);
}

Point C[MAX];// contains the centroids
bool flag[MAX];

void initialize(int k, int n){
	clr(flag);// check if a random number mod n is already found
	for (int i = 0; i < k; ){
		int r = rand()%n;
		if (!flag[r]){
			flag[r] = true;// this random number found now
			C[i] = P[r];
			i++;
		}
	}
}

void print_centers(int k){
	for (int i = 0; i < k; i++){
		C[i].print();
	}
}

void k_means(int k, int n){
	if (k < 1 || k > n){
		cout << "Fix the number of centers" << endl;
	}
	if (k == n){
		for (int i = 0; i < k; i++){
			C[i] = P[i];
		}
		return;
	}
	initialize(k, n);
}
	
int main(){
	read("input.txt");
	srand((unsigned)time(0));
	int k, n;
	while (cin >> k >> n){
		if (!k || !n)	break;
		for (int i = 0; i < n; i++){
			cin >> P[i].x >> P[i].y;
			//P[i].print();
		}
		initialize(k, n);
		print_centers(k);
	}
	return 0;
}