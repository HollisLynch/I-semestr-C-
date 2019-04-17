#include <iostream>
#include <fstream>

using namespace std;

int n = 16;
int m = 49;

double **d;



void init()
{
	cin >> n >> m;
	d = new double*[n];
	for (int i = 0; i < n; i++) {
		d[i] = new double[m];
		for (int j = 0; j < m; j++)
		{
			cout << i << " " << j << " ";
			cin >> d[i][j];
		}
	}
}
void write()
{
	ofstream f("maze.txt");
	f << n << endl << m << endl;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			f << d[i][j] << endl;
}
void read()
{
	ifstream f("maze.txt");
	f >> n >> m;
	cout << n << "  " << m << endl;
	d = new double*[n];
	for (int i = 0; i < n; i++) {
		d[i] = new double[m];
		for (int j = 0; j < m; j++)
			f >> d[i][j];
	}
	f.close();
}

int czytanie()
{
	init();
	write();
	read();
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++)
			cout << d[i][j] << "  ";
		cout << endl;
	}

	system("PAUSE");
	return 0;
}