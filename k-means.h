#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
#include <numeric>
#include <string>
#include <stdlib.h>
#include <time.h>
#include <fstream>
using namespace std;

double sum(const vector<double> &);//calculate the distance sum between last center points and center points this turn
double get_distance(int* , double*, int );//calculate the distance between two points
double get_distance(double* , double*, int );//overwrite last function
double update_center(double* , vector<int*> &, const int );//update centers of each cluster after each turn
void display(vector<int*>&, int );//dispaly the result to screen
void output_data(ofstream & ,vector<int*>&, int );//put the rusult to files accessible to other apps
void k_means(const vector<int*> &, int , const int );//k-means method
