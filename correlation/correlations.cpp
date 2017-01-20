#include <bits/stdc++.h>

#define read(a) freopen(a, "r", stdin)
#define write(a) freopen(a, "w", stdout)
#define MAX 2000
#define NUM_USR 945
#define NUM_MOV 1685
#define pb push_back
#define LL long long
#define VI std:: vector < int >

using namespace std;

//VI user_id;
//bool visited[MAX];
char str[MAX];

VI Movies[NUM_MOV];// vector containing which users rated this movie
VI Users[NUM_USR];// vector containing which movies this user rated
int rating[NUM_USR][NUM_MOV];// user-movie rating matrix
VI common[NUM_USR][NUM_USR];// common[u][v] is a vector that has the common movies both u and v
							// rated
VI :: iterator it;

void print(VI V){
	int sz = V.size();
	for (int i = 0; i < sz; i++){
		cout << V[i] << " ";
	}
	cout << endl;
	return;
}

void reset(){
	for (int i = 0; i < NUM_MOV; i++){
		Movies[i].clear();
	}
	for (int i = 0; i < NUM_USR; i++){
		Users[i].clear();
	}
	return;
}

VI vector_union(VI &A, VI &B){// finds the union of two vectors A and B
	VI res;
	res.clear();
	//std:: sort(A.begin(), A.end());
	//std:: sort(B.begin(), B.end());
	set_union(A.begin(), A.end(), B.begin(), B.end(), back_inserter(res));
	return res;
}

VI vector_intersection(VI &A, VI &B){// finds the union of two vectors A and B
	VI res;
	res.clear();
	//std:: sort(A.begin(), A.end());
	//std:: sort(B.begin(), B.end());
	std:: set_intersection(A.begin(), A.end(), B.begin(), B.end(), back_inserter(res));
	return res;
}

double dissimiliarity(int u, int v){
	if (u > v){
		swap(u, v);
	}
	VI res = common[u][v];// common movies between u and v
	int sz = res.size();
	if (!sz)	return 1;// if no common movie, totally dissimilar
	int max_diff = 0;
	double sumu = 0.0, sumv = 0.0;
	double sum = 0.0;
	int maxr = 0;
	for (int i = 0; i < sz; i++){
		int m = res[i];
		int diff = rating[u][m]-rating[v][m];
		sumu += rating[u][m];
		sumv += rating[v][m];
		diff = abs(diff);
		max_diff = max(max_diff, diff);
		sum += diff*diff;
		maxr = max(rating[u][m], rating[v][m]);
	}
	double avgu = sumu/sz, avgv = sumv/sz;
	double mean_sqr = (double) sum/(double) sz;
	double rms = sqrt(mean_sqr);
	if (!max_diff)	return 0;// if all common movie ratings are same, totally similar
	double dis = rms/max(avgu, avgv);
	return dis;
}

double similarity(int u, int v){
	return 1.0-dissimiliarity(u, v);
}

double pearson(int u, int v){// computes pearson coefficient between user u and v
	if (u > v){
		swap(u, v);
	}
	VI res = common[u][v];
	int sz = res.size();
	if (!sz)	return 0;
	double sumu = 0.0, sumv = 0, dot = 0;
	double sqr_sumu = 0.0, sqr_sumv = 0.0;
	for (int i = 0; i < sz; i++){
		int m = res[i];
		sumu += rating[u][m];
		sumv += rating[v][m];
		dot += rating[u][m]*rating[v][m];
		sqr_sumu += rating[u][m]*rating[u][m];
		sqr_sumv += rating[v][m]*rating[v][m];
	}
	double numerator = dot-((sumu*sumv)/(double)sz);
	double denou = sqr_sumu-((sumu*sumu)/(double) sz);
	double denov = sqr_sumv-((sumv*sumv)/(double) sz);
	double denominator = sqrt(denou*denov);
	if (denominator < 1e-10)	return 0;
	double sim = numerator/denominator;
	sim += 1.0;
	sim /= 2.0;
	return sim;
}

double cos(int u, int v){// computes cosine correlation coefficient between user u and v
	if (u > v){
		swap(u, v);
	}
	VI res = common[u][v];
	int sz = res.size();
	if (!sz)	return 0;
	double dot = 0, sqr_sumu = 0.0, sqr_sumv = 0.0;
	for (int i = 0; i < sz; i++){
		int m = res[i];
		int r1 = rating[u][m];
		int r2 = rating[v][m];
		dot += r1*r2;
		sqr_sumu += r1*r1;
		sqr_sumv += r2*r2;
	}
	sqr_sumu = sqrt(sqr_sumu);
	sqr_sumv = sqrt(sqr_sumv);
	if (sqr_sumu < 1e-10 || sqr_sumv < 1e-10)	return 0;
	return dot/(sqr_sumu*sqr_sumv);
}

int main(){
	//write("out.txt");
	reset();
	FILE *F;
	F = fopen("u.data", "r");
	int cnt = 0;
	int mxu = 0, mxm = 0;
	while (fgets(str, 10000, F)){
		char *p;
		p = strtok(str, "\t");
		int u = atoi(p);
		p = strtok(0, "\t");
		int m = atoi(p);
		//cout << m << endl;
		p = strtok(0, "\t");
		int r = atoi(p);
		//Data[u] = data(u, m, r);
		//user_id[cnt] = u;
		mxu = max(mxu, u);
		mxm = max(mxm, m);
		cnt++;
		Movies[m].pb(u);
		Users[u].pb(m);
		rating[u][m] = r;
	}
	for (int i = 0; i <= mxm; i++){
		sort(Movies[i].begin(), Movies[i].end());
	}
	for (int i = 1; i <= mxu; i++){
		sort(Users[i].begin(), Users[i].end());
	}
	for (int i = 1; i < mxu; i++){
		for (int j = i+1; j <= mxu; j++){
			common[i][j] = vector_intersection(Users[i], Users[j]);
		}
	}
	cout << pearson(1, 2) << " " << cos(1, 2) << endl;
	
	return 0;
}