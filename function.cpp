#include"function.h"
using namespace std;


int GetRandomInt(int max, int min) {
	return rand() % (max - min + 1) + min;
}

//get random value from 0 and 1
double GetPercent() {
	return 0.01*(rand()%100);
}


double alpha = 0.85;
double beta = 0.001;//beta means how much reward each unit of Jam will reduce

double GetDelta(double delta) {
	if (delta > (1 / beta)) delta = 1 / beta - 1;
	return 1 - beta * delta;
}

double EqualQ(double delta, double R, double maxQ, double Q) {
	return delta * (Q + R + alpha * (maxQ - Q));
}

double GetMaxFromArray(double M[], int len) {
	int max = 0, i = 0;
	for (i = 0; i < len; i++) {
		if (M[i] > max)max = M[i];
	}
	return max;
}

double GetMaxIndexFromArray(double M[], int len) {
	int max = 0, index = 0, i = 0;
	for (i = 0; i < len; i++) {
		if (M[i] > max) {
			max = M[i];
			index = i;
		}
	}
	while (max == 0) {
		index = GetRandomInt(len - 1);
		if (M[index] == 0) return index;
	}
	return index;
}

bool IfHit(int hip, double** Array, int len) {
	for (int i = 0; i < len; i++) {
		if ((int)Array[i][0] == hip) {
			return true;
		}
	}
	return false;
}

bool IfHit(int hip, int* Array, int len) {
	for (int i = 0; i < len; i++) {
		if (Array[i] == hip) {
			return true;
		}
	}
	return false;
}

void DisplayMetric(double** M, int len1,int len2, const char* comment) {
	if (comment == NULL);
	else cout << comment << '\n';
	for (int i = 0; i < len1; i++) {
		for (int j = 0; j < len2; j++) {
			cout << setw(3) << M[i][j] << ' ';
		}
		cout << '\n';
	}
}

void crash() {
	system("pause");
	exit(0);
}