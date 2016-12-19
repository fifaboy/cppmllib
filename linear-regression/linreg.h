struct Point {
	double x, y;
	Point(){}
	
	Point(double a, double b){
		x = a, y = b;
	}
	
	bool operator < (Point P) const {
		return ((x < P.x) || (x == P.x && y < P.y));
	}
	
	Point operator - (Point P) const {
		return Point(x-P.x, y-P.y);
	}
	
	Point operator + (Point P) const {
		return Point(x+P.x, y+P.y);
	}
	
	double operator * (Point P) const {
		return (x*P.y-y*P.x);
	}
	
	double operator ^ (Point P) const {
		return (x*P.x+y*P.y);
	}
};

double averageX(Point P[], int n){
	if (n <= 0)	return 0;
	double sum = 0.0;
	for (int i = 0; i < n; i++){
		sum += P[i].x;
	}
	return sum/n;
}

double averageY(Point P[], int n){
	if (n <= 0)	return 0;
	double sum = 0.0;
	for (int i = 0; i < n; i++){
		sum += P[i].y;
	}
	return sum/n;
}


double average(double ar[], int n){
	if (n <= 0)	return 0;
	double sum = 0.0;
	for(int i = 0; i < n; i++){
		sum += ar[i];
	}
	return sum/n;
}