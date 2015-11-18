#include "k-means.h"
using namespace std;

double sum(const vector<double> &distances)
{
    double sum=0;
    for (unsigned int i = 0;i<distances.size();i++)
    {
        sum += distances[i];
    }
    return sum;
}

double get_distance(int* point1, double*point2, int data_demension = 2)
{
    double distance=0;
    double temp=0;
    for (int i = 0;i<data_demension;i++)
    {
        temp += pow(((double)*(point1 + i)) - *(point2 + i), 2.0);
        //cout<<temp<<endl;
    }
    distance = sqrt(temp);
    return distance;
}

double get_distance(double* point1, double*point2, int data_demension = 2)
{
    double distance=0;
    double temp=0;
    for (int i = 0;i<data_demension;i++)
    {
        temp += pow(*(point1 + i) - *(point2 + i), 2.0);
    }
    distance = sqrt(temp);
    return distance;
}

double update_center(double* center, vector<int*> &cluster, const int data_demension = 2)//update centers of each cluster after each turn
{
    double temp=0;
    double* last_point;
    last_point =new double[data_demension];
    double* temp_ptr = last_point;
    for (int i = 0;i<data_demension;i++)
    {
        for (unsigned int j = 0;j<cluster.size();j++)
        {
            temp += (double)*(cluster[j] + i);
        }
        *(temp_ptr + i) = *(center + i);
        temp = temp / (double)cluster.size();
        *(center + i) = temp;
    }
    return get_distance(temp_ptr, center);
}

void display(vector<int*>&cluster, int data_demension = 2)
{
    for (unsigned int i = 0; i<cluster.size();i++)
    {
        for (int j = 0; j<data_demension;j++)
        {
            cout << *(cluster[i] + j) << " ";
        }
        cout << endl;
    }
}

void output_data(ofstream &outfile ,vector<int*>&cluster, int data_demension = 2)
{
    for( unsigned int i = 0;i < cluster.size();i++)
    {
        for (int j = 0; j < data_demension;j++)
        {
            outfile << *(cluster[i] + j) << ' ';
        }
        outfile << endl;
    }
    outfile.close();
}

void k_means(const vector<int*> &data_set, int data_demension = 2, const int cluster_num = 2)
{
    double offset = 10;
    vector<double>::iterator iter;//tempt pointer
    vector<int*> *clusters;
    clusters=new vector<int*> [cluster_num];//initiate containers to hold clusters
    vector<double*>  centers(cluster_num);//initiate container to hold center points
    vector<double> temp_distance(cluster_num); //put the distances between the point and the center points
    vector<double> distances(cluster_num);//distances of each center points and each last center points
    string *filename;
    filename = new string[cluster_num];
    ofstream *stream;
    stream = new ofstream[cluster_num];
    char c_num[10];
    string s_num;
    for (int i = 0;i < cluster_num;i++)//generate files to store the result
    {
        sprintf(c_num, "%d", i+1);//When compile on Qt,use this function,when compile on the VS, use the next function
        //sprintf_c(c_num, "%d", i+1);
        s_num = c_num;
        filename[i] = "cluster_data" + s_num+".txt";
        stream[i].open(filename[i]);//output the result to file
    }

    for (int i = 0;i<cluster_num;i++)
    {
        centers[i] = new double[data_demension];
        for (int j = 0;j<data_demension;j++)
        {
            *(centers[i] + j) = (double)*(data_set[i] + j);//put cluster number data points to container
        }
    }
    while (offset>0.01)
    {
        for (int i = 0;i<cluster_num;i++)
        {
            clusters[i].clear();//clear the clusters in order to renew the clusters
        }
        for (unsigned int i = 0;i<data_set.size();i++)//calculate each point belong which cluster
        {
           // temp_distance.clear();
            for (int j = 0;j<cluster_num;j++)
            {
                temp_distance[j] = get_distance(data_set[i], centers[j],data_demension);//calculate the distance between the point and center points
            }
            iter = min_element(temp_distance.begin(), temp_distance.end()); //exact the smallest distance
            //cout << *iter << endl;
            for (int j = 0; j<cluster_num;j++)
            {
                if (*iter == temp_distance[j])
                {
                    clusters[j].push_back(data_set[i]);//put the point to the cluster which its distance is smallest
                    break;
                }
            }
        }
        for (int i = 0;i<cluster_num;i++)
        {
            distances[i] = update_center(centers[i], clusters[i],data_demension);//update the center points and the distances between centers and last centers
        }
        offset = sum(distances);
    }

    for (int i = 0;i<cluster_num;i++)
    {
        cout << "The No." << i + 1 << " cluster of data points" << endl;//print the result
        display(clusters[i],data_demension);
    }

    for (int j = 0;j < cluster_num;j++)
    {
        output_data(stream[j],clusters[j], data_demension);
    }
}



