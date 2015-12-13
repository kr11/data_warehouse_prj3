#include <iostream>
#include <fstream>
#include "head.h"
#include "bi_kmeans.h"
#include "dbscan.h"
#include "evaluation.h"

using namespace std;

void clustering(int data_size, const int para_k[], const double para_eps[], const int para_minPts[])
{
	int i;
	char file_name[20];
	ifstream inFile;
	Point *data = new Point[data_size];

	sprintf(file_name, "dataset%d.dat", (data_size == SIZE2) + 1);
	inFile.open(file_name, ios::in);
	if (inFile.bad())
	{
		cout<<"The file "<<file_name<<"does not exist!"<<endl;
		return;
	}
	for (i = 0; i < data_size; ++i)
	{
		inFile>>data[i].x>>data[i].y;
	}
	inFile.close();
	bi_kmeans_clustering(data, data_size, para_k);
	dbscan(data, data_size, para_eps, para_minPts);

	delete [] data;
}

void main(int argc, char *argv[])
{
	if (argc == 2)
	{
		int flag = atoi(argv[1]);
		
		if (flag & 1)
		{
			clustering(SIZE1, para1_k, para1_eps, para1_minPts);
		}
		if (flag & 2)
		{
			clustering(SIZE2, para2_k, para2_eps, para2_minPts);
		}
	}
	evaluate();
}