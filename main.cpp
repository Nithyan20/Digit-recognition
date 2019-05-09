#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <cstdlib>
#include <conio.h>
#include <cstdio>
#include <math.h>

using namespace std;
int layersize=400;const int num_labels = 10;int lambda=0.1;int num_iters=500;
double **x;double y[2000],m=1000,n=400;double ybin[10][2000];double **tempx; double hyp[2000][num_labels];
double initial_theta[450][num_labels];double cost[num_labels]; double grad[450][num_labels];int i,j,k;double alpha=0.01;

int readdatax()
{
    double* a = new double[500000];
    long int p=0;
    x= new double *[2000];
    for(i=0;i<2000;i++)
    x[i]= new double[450];

    FILE *fp;
    fp = fopen("dataxt2.csv","r");
    char buffer[1024] ;
    char *record,*line;

    while(p<(m*n))
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
	for(i=0;i<m;i++)
    for(j=0;j<n;j++)
    x[i][j]=a[p++];


    delete [] a;

    fclose(fp);
    return 0;

}

int readdatay()
{
    FILE *fp;
    fp = fopen("datayt.csv","r");
    char buffer[1024] ;
    char *record,*line;
    int l=0;
    double maty[2000];
    while((line=fgets(buffer,sizeof(buffer),fp))!=NULL)
    {
		record = strtok(line,",");
		while(record != NULL)
			{
            maty[l++] = atof(record) ;
            record = strtok(NULL,",");
			}

	}
    fclose(fp);
    int k=0;
    for(i=0;i<m;i++)
    {
        y[i]=maty[k];
        k++;
    }
    return 0;
}

int assigntheta()
{
    for(i=0;i<=n;i++)
    for(j=0;j<num_labels;j++)
        initial_theta[i][j]=0;
    return 0;
}

int featurexo()
{
    for(i=0;i<m;i++)
    for(j=n-1;j>0;j--)
    {
        x[i][j+1]=x[i][j];
    }
    for(i=0;i<m;i++)
    x[i][0]=1;

    return 0;
}

int outbin()
{
    for(i=0;i<num_labels;i++)
    {
        for(j=0;j<m;j++)
        if(y[j]==i)
        ybin[i][j]=1;
        else
        ybin[i][j]=0;
    }
   return 0;

}

double sigmoid(double z)
{
    double g;
    g = 1.0/(1.0 + exp(-z));
    return g;
}



int costfunc()
{
    double sum=0;double hy[2000][num_labels];double temp1[2000][num_labels];
    for(i=0;i<m;i++)
    {
        for(j=0;j<num_labels;j++)
        {
          for (k = 0; k <=n; k++)
          sum = sum + x[i][k]*initial_theta[k][j];

          hy[i][j]=sum;
        sum=0;
        }
    }

    for(i=0;i<m;i++)
    for(j=0;j<num_labels;j++)
    {
        hyp[i][j]= sigmoid(hy[i][j]);
    }

    for(i=0;i<m;i++)
    for(j=0;j<num_labels;j++)
    temp1[i][j]=hyp[i][j]-ybin[j][i];

    tempx= new double *[450];
    for(i=0;i<450;i++)
    tempx[i]= new double[2000];

    for(i=0;i<m;i++)
    for(j=0;j<=n;j++)
    tempx[j][i]=x[i][j];

    sum=0;
    for(i=0;i<=n;i++)
    {
        for(j=0;j<num_labels;j++)
        {
            for(k=0;k<m;k++)
            sum+= tempx[i][k]*temp1[k][j];

            grad[i][j]=sum;
            sum=0;
        }
    }

    for(i=0;i<=n;i++)
    {
        for(j=0;j<num_labels;j++)
        {
            if(i==0)
            {
                grad[i][j]=grad[i][j]/m;
            }
            else
            {
                grad[i][j]=(grad[i][j]/m)+(lambda/m)*initial_theta[i][j];
            }
        }
    }



for(i=0;i<=n;i++)
for(j=0;j<num_labels;j++)
initial_theta[i][j]-=alpha*grad[i][j];

for(i=0;i<450;i++)
    delete []tempx[i];
    delete []tempx;

return 0;
}
int writetheta()
{
    ofstream g("theta.csv");

        for(int i=0;i<=n;i++)
        {
            for(int j=0;j<num_labels;j++)
            g<<initial_theta[i][j]<<",";
            g<<endl;
        }
        g.close();
    return 0;
}



int main()
{
    readdatax();
    readdatay();
    assigntheta();
    featurexo();
    outbin();
   for(int b=0;b<500;b++)
   {
       costfunc();
    }
    for(i=0;i<=n;i++)
    for(j=0;j<num_labels;j++)
        cout<<initial_theta[i][j];

    writetheta();

    for(i=0;i<2000;i++)
        delete []x[i];
    delete []x;
    return 0;
}
