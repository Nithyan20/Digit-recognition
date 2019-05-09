#include "core.hpp"
#include "highgui.hpp"
#include "imgcodecs.hpp"
#include<iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <cstdlib>
#include <conio.h>
#include <cstdio>
#include <math.h>

using namespace cv;
using namespace std;
double **x;
int readdatax()
{
    int i,j;
    double* a = new double[5000];
    long int p=0;
    x= new double *[10];
    for(i=0;i<10;i++)
    x[i]= new double[450];

    FILE *fp;
    fp = fopen("theta.csv","r");
    char buffer[1024] ;
    char *record,*line;

    while(p<4010)
    {
        line=fgets(buffer,sizeof(buffer),fp);
		record = strtok(line,",");
		while(record != NULL)
			{
            a[p++] = atof(record) ;
            record = strtok(NULL,",");
			}

	}
	p=0;
	for(i=0;i<10;i++)
    for(j=0;j<=400;j++)
    x[i][j]=a[p++];
    delete [] a;

    fclose(fp);
    return 0;

}

double sigmoid(double z)
{
    double g;
    g = 1.0/(1.0 + exp(-z));
    return g;
}


int main()
 {
    double pixval[500];int k=0;
    Mat image1, image2;
    image1 = imread("3.jpg");
    if (!image1.data) {
        cout << "could not find image1" << endl;
    }
    for(int j=0;j<image1.rows;j++)
  {
  for (int i=0;i<image1.cols;i++)
  {
   pixval[k++] = (int)image1.at<uchar>(i,j);
  }
  }
  for(int i=0;i<k;i++)
   {
    pixval[i]=pixval[i]/255.0;
    cout<<pixval[i];
   }
     readdatax();

    double sum[10];
 for(int i=0;i<10;i++)
    sum[i]=0;
 for(int i=0;i<10;i++)
    {
    for (int k = 0; k <=400; k++)
    sum[i] = sum[i] + x[i][k]*pixval[k];
    }
 for(int i=0;i<10;i++)
 {
     sum[i]=sigmoid(sum[i]);
     cout<<sum[i]<<endl;
 }

   return 0;
}
