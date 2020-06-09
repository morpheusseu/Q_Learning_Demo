#include"function.h"
using namespace std;

double** Distance;//unit per 100 meters___

double** Traffic;//1 for default(or clear situation) and 10 for most crowded___

double** Goal;//store the Goals and Willingness(Or Reward)___

double** Jam;//Distance*Trffic
double* Reward;//the willingness of Goal cross
double** Q;

const char* filename = "Z://Paths.txt";

int i, j, g_count;
int Q_block;
bool flag;
bool test = false;
bool output = false;
double time_s = time(0);

int order = 0;
int GetNumInOrder(bool ADD = false);

void TraceBack(int** T, int src, int dest) {
	if (output) cout << "\n\n\nTracing Back\n";
	int end = dest;
	bool flag = true;
	if (output) cout << "path end from " << dest;
	while (flag) {
		flag = false;
		for (int it = 0; it < numCross; it++) {
			if (T[it][end] > 0) {
				if (output)cout << " <- " << it;
				flag = true;
				Q[it][end] = EqualQ(GetDelta(Jam[it][end]), Reward[end], GetMaxFromArray(Q[end], numCross));
				/*if (Q[it][end] == 0) {
					cout << "Err : Turn back to 0 : from " << it << " to " << end << '\n';
					system("pause");
				}*/
				T[it][end]--;
				end = it;
				break;
			}
		}
		//cout << "\nend : " << end << " flag : " << flag << '\n';
	}
	if (output)cout << '\n';
}

bool QL_Step_Rand(int start) {
	if (output)cout << "\n\n\nQL_Step_Rand\n\n";
	if (test) system("cls");
	srand(time(0));
	if (IfHit(start, Goal, numGoal)) {
		return true;//hit the goal
	}
	int src = start;
	int counter = 0;
	int next = 0;
	int** Trace = new int* [numCross];
	int Banned[10] = { -1,-1,-1,-1,-1,-1,-1,-1,-1,-1 };
	for (i = 0; i < numCross; i++)Trace[i] = new int[numCross];
	for (i = 0; i < numCross; i++)memset(Trace[i], 0, sizeof(int) * numCross);
	if (output)cout << "QL_Step_Rand : start " << start;
	while ((counter++) <= maxIterate) {
		int last = -1;
		while (true) {
			for (int i = 0; i < 9; i++) {
				Banned[i] = Banned[i + 1];
			}
			if (!IfHit(start, Banned, 10))Banned[9] = start;
			double sum = 0;
			last = -1;
			for (i = 0; i < numCross; i++) {
				if (Trace[i][start] > 0) {
					last = i;
					break;
				}
			}//get last

			for (i = 0; i < numCross; i++) {
				if (Q[start][i] != -1) {
					if (IfHit(i, Banned, 10))sum += 0;
					else sum += pow(0.5, Trace[start][i]);
					//cout <<"sum["<<i<<"] : "<< sum << '\n';
				}
			}
			double prob = GetPercent() * sum;
			//cout <<"prob : "<< prob << '\n';
			sum = 0;
			for (i = 0; i < numCross; i++) {
				if (Q[start][i] != -1) {
					if (IfHit(i, Banned, 10)) {
						if (last == -1) last = i;
						sum += 0;//pow(0.5, 20);
					}
					else {
						last = i;
						sum += pow(0.5, Trace[start][i]);
					}
					if (sum >= prob) {
						next = i;
						break;
					}
					next = last;
				}
			}

			if (Q[start][next] != -1) {
				break;
			}
		}//choosing next step

		if (test) {
			for (i = 0; i < 10; i++)cout << Banned[i] << '\t';
			cout << '\n';
		}

		Trace[start][next]++;
		//Q[start][next] = EqualQ(GetDelta(Jam[start][next]), Reward[next], GetMaxFromArray(Q[start], numCross));
		start = next;
		if (output)cout << " -> " << start;
		if (IfHit(start, Goal, numGoal)) {
			//system("pause");
			TraceBack(Trace, src, start);
			for (i = 0; i < numCross; i++)delete[]Trace[i];
			delete[]Trace;
			return true;//hit the goal
		}
		//system("pause");
	}
	if (output)system("pause");
	for (i = 0; i < numCross; i++)delete[]Trace[i];
	delete[]Trace;
	return false;
}

bool QL_Step_Q(int start) {
	if (output)cout << "\n\n\nQL_Step_Q\n\n";
	if (test) system("cls");
	srand(time(0));
	if (IfHit(start, Goal, numGoal)) {
		return true;//hit the goal
	}
	int src = start;
	int counter = 0;
	int next = 0;
	int** Trace = new int* [numCross];
	int Banned[10] = { -1,-1,-1,-1,-1,-1,-1,-1,-1,-1 };
	for (i = 0; i < numCross; i++)Trace[i] = new int[numCross];
	for (i = 0; i < numCross; i++)memset(Trace[i], 0, sizeof(int) * numCross);
	if (output)cout << "QL_Step_Q : start " << start;
	while ((counter++) <= maxIterate) {
		int last = -1;
		while (true) {
			for (int i = 0; i < 9; i++) {
				Banned[i] = Banned[i + 1];
			}
			if (!IfHit(start, Banned, 10))Banned[9] = start;
			double sum = 0;
			last = -1;
			for (i = 0; i < numCross; i++) {
				if (Trace[i][start] > 0) {
					last = i;
					break;
				}
			}//get last

			for (i = 0; i < numCross; i++) {
				if (Q[start][i] != -1) {
					if (IfHit(i, Banned, 10))sum += pow(0.5, 20) * pow(1.2, Q[start][i]);
					else sum += pow(0.5, Trace[start][i]) * pow(1.2, Q[start][i]);
					//cout <<"sum["<<i<<"] : "<< sum << '\n';
				}
			}
			double prob = GetPercent() * sum;
			//cout <<"prob : "<< prob << '\n';
			sum = 0;
			for (i = 0; i < numCross; i++) {
				if (Q[start][i] != -1) {
					if (IfHit(i, Banned, 10)) {
						if (last == -1) last = i;
						sum += pow(0.5, 20) * pow(1.2, Q[start][i]);
					}
					else {
						last = i;
						sum += pow(0.5, Trace[start][i]) * pow(1.2, Q[start][i]);
					}
					if (sum >= prob) {
						next = i;
						break;
					}
					next = last;
				}
			}

			if (Q[start][next] != -1) {
				break;
			}
		}//choosing next step

		if (test) {
			for (i = 0; i < 10; i++)cout << Banned[i] << '\t';
			cout << '\n';
		}

		Trace[start][next]++;
		//Q[start][next] = EqualQ(GetDelta(Jam[start][next]), Reward[next], GetMaxFromArray(Q[start], numCross));
		start = next;
		if (output)cout << " -> " << start;
		if (IfHit(start, Goal, numGoal)) {
			//system("pause");
			TraceBack(Trace, src, start);
			for (i = 0; i < numCross; i++)delete[]Trace[i];
			delete[]Trace;
			return true;//hit the goal
		}
		//system("pause");
	}
	if (output)system("pause");
	for (i = 0; i < numCross; i++)delete[]Trace[i];
	delete[]Trace;
	return false;
}
bool QL_Step(int start, int epsilon = 0);
bool QL_Search(int start);
void UpdateQTable(int loop = 1);
void Initialize(fstream& infile);
void Finish();

int main() {
	srand(time(0));
	fstream infile;
	infile.open(filename, ios::in);
	if (!infile.is_open()) {
		cout << "Err : can't open file __ " << filename;
		system("pause");
		exit(0);
	}
	Initialize(infile);
	//Initialization Stage Finished ........

	flag = true;
	g_count = 0;
	int white_block = 0;
	int zero_block = 0;
	for (i = 0; i < numGoal; i++) {
		int goal = 0;
		for (j = 0; j < numCross; j++) {
			goal = (int)Goal[i][0];
			if (goal == STOP)break;
			if (Q[goal][j] != -1 && !IfHit(j, Goal, numGoal)) {
				zero_block++;
			}
		}
	}
	int max_loop = 10;
	while (flag) {
		g_count++;
		int icount = 0;
		while (icount < numSearch) {
			if (!QL_Step(GetNumInOrder(), 40));//when the parameter has a value of 40, it means 40% percnet using Q_learning searching, 60% percent using random searching
			else {
				icount++;
				GetNumInOrder(true);
				int p = 0;
				int down = 10;
				if (icount % (numSearch / 100) == 0) {
					system("cls");
					for (int iq = 0; iq < numCross; iq++)for (int jq = 0; jq < numCross; jq++) {
						if (Q[iq][jq] == 0) {
							flag = true;
							p++;
							if ((down--) > 0 && icount % (numSearch / 100) == 0) cout << iq << '/' << jq << '\n';
						}
					}
					white_block = p;
					if (icount % (numSearch / 100) == 0) {
						cout << "Loop " << g_count << " : " << icount / (numSearch / 100) << " % Processing ...\nwith white_block : " << white_block << " / " << Q_block << " with zero_block : "<<zero_block<<"\n";
						cout << "using " << time(0) - time_s << " sec\n";
					}
				}
			}
		}
		cout << "Finish a loop\n";
		icount = 0;
		for (int iq = 0; iq < numCross; iq++)for (int jq = 0; jq < numCross; jq++) {
			if (Q[iq][jq] == 0) {
				icount++;
			}
		}
		white_block = icount;
		if (white_block <= zero_block) {
			flag = false;
			//max_loop = g_count + 2;
		}
		if (g_count >= max_loop) break;
	}
	//UpdateQTable(100);
	system("cls");
	//DisplayMetric(Q, numCross, numCross, "Q_table");
	for(i=0;i<numCross;i++)
		QL_Search(i+1);
	cout << "using " << time(0) - time_s << " sec totally\n";
	system("pause");
	Finish();
}





int GetNumInOrder(bool ADD) {
	if (ADD) order++;
	order = order % numCross;
	return order;
}
bool QL_Step(int start, int epsilon) {//epsilon sit between 0 and 100 , if s < epsilon using Q_table searching paths(0 for fully randomly adventure)
	srand(time(0));
	if (GetRandomInt(100) < epsilon) {
		return QL_Step_Q(start);
	}
	else {
		return QL_Step_Rand(start);
	}
}
bool QL_Search(int start) {
	start--;
	if (IfHit(start, Goal, numGoal)) {
		return false;//hit the goal
	}
	int counter = 0;
	int next = 0;
	cout << "path from " << start + 1;
	cout << " : " << start + 1;
	while ((counter++) <= maxIterate) {
		next = GetMaxIndexFromArray(Q[start], numCross);
		cout << " -> " << next + 1;
		start = next;
		if (IfHit(start, Goal, numGoal)) {
			cout << "\n\n";
			return true;//hit the goal
		}
	}
	cout << "\n\n";
	return false;
}
void UpdateQTable(int loop) {
	while (loop > 0) {
		for (int iq = 0; iq < numCross; iq++) {
			for (int jq = 0; jq < numCross; jq++) {
				if (Q[iq][jq] != -1)Q[iq][jq] = EqualQ(GetDelta(Jam[iq][jq]), Reward[jq], GetMaxFromArray(Q[jq], numCross), Q[iq][jq]);
			}
		}
		loop--;
	}
}
void Initialize(fstream& infile) {
	Distance = new double* [numCross];
	Traffic = new double* [numCross];
	Jam = new double* [numCross];
	Q = new double* [numCross];
	Goal = new double* [numCross];
	Reward = new double[numCross];
	for (i = 0; i < numCross; i++) {
		Distance[i] = new double[numCross];
		Traffic[i] = new double[numCross];
		Jam[i] = new double[numCross];
		Q[i] = new double[numCross];
		Goal[i] = new double[numGoal];
	}

	for (i = 0; i < numCross; i++) {
		Reward[i] = 0;
		for (j = 0; j < numCross; j++) {
			Distance[i][j] = 0;
			Traffic[i][j] = 1;
			Jam[i][j] = 0;
			Q[i][j] = -1;
		}
	}

	string a;
	int start, end;
	double distance, traffic;
	infile >> a >> a >> a >> a;//withdraw the table index
	Q_block = 0;
	while (true) {
		infile >> start;
		if (start == STOP) break;
		infile >> end >> distance >> traffic;
		start--, end--;
		//CHECK for diatance and trffic's overflow
		if (distance >= minDistance && distance <= maxDistance);
		else if (distance > maxDistance)distance = maxDistance;
		else distance = minDistance;
		if (traffic >= minTraffic && traffic <= maxTraffic);
		else if (traffic > maxTraffic) traffic = maxTraffic;
		else traffic = minTraffic;

		Distance[start][end] = Distance[end][start] = distance;
		Traffic[start][end] = Traffic[end][start] = traffic;
		Jam[start][end] = Jam[start][end] = distance * traffic;
		Q[start][end] = Q[end][start] = 0;
		Q_block += 2;
	}
	for (i = 0; i < numGoal; i++) {
		infile >> Goal[i][0];
		if (Goal[i][0] == STOP)break;
		infile >> Goal[i][1];
		if (j == 1 && Goal[i][j] <= 0) Goal[i][j] = 1;
		Reward[(int)Goal[i][0]] = Goal[i][1];
	}

	/*for (i = 0; i < numCross; i++) {
		for (j = 0; j < numCross; j++) {
			cout << Jam[i][j] << ' ';
		}
		cout << '\n';
	}*/
	/*
	*/
	for (i = 0; i < numGoal; i++) {
		if (Goal[i][0] == STOP)break;
		cout << Goal[i][0] << '/' << Goal[i][1] << '\n';
	}
}
void Finish() {
	for (i = 0; i < numCross; i++) {
		delete Distance[i];
		delete Traffic[i];
		delete Jam[i];
		delete Q[i];
		delete Goal[i];
	}
	delete Distance;
	delete Traffic;
	delete Jam;
	delete Q;
	delete Goal;
	delete Reward;
}
