#include "k-means.h"
using namespace std;

int main()
{
    int data_num = 400;//data number
	int cluster_num = 5;//cluster number
	int data_demension = 2;//data demension

    cout<<"Please input data number:"<<endl;
    cin>>data_num;
    cout<<data_num<<endl;
    cout<<"Please input data demension:"<<endl;
    cin>>data_demension;
    cout<<data_demension<<endl;
    cout<<"Please input cluster number:"<<endl;
    cin>>cluster_num;
    cout<<cluster_num<<endl;

    vector<int*>data_set(data_num);

    srand((unsigned int) time(0));//generate random points to cluster
    for (int i = 0;i < data_num;i++)
	{
        data_set[i] = new int[data_demension];//generate data to use
		for (int j = 0;j < data_demension;j++)
		{
			*(data_set[i] + j) = rand() % 50;
		}
	}

    k_means(data_set, data_demension, cluster_num);//invoke cluster method
	while (1) {}
	return 0;
}

