#pragma once
#include<fstream>
#include<iostream>
#include<cstdlib>
#include<iomanip>
#include<ctime>

#define maxIterate 100
#define numSearch 1000
#define numCross 82
#define numGoal 2

#define maxTraffic 10
#define minTraffic 1
#define maxDistance 1000
#define minDistance 0

#define STOP 11111111

int GetRandomInt(int max, int min = 0);
double GetPercent();
double GetDelta(double delta);
double GetMaxFromArray(double M[], int len); 
double GetMaxIndexFromArray(double M[], int len);
double EqualQ(double delta,double R,double maxQ,double Q = 0);
bool IfHit(int hip,double** Array,int len);
bool IfHit(int hip, int* Array, int len);

void DisplayMetric(double **M, int len1 = numCross, int len2 = numCross, const char* comment = NULL);

void crash();