#include <iostream>
#include <cmath>
#include <cstdlib>
#include <vector>
#include <fstream>
using namespace std;

void convolution_matrix_mult(float **a,int c1,float *q, int c2,float **final_ans);
void max_pooling(int r,float **a, float **b);
void relu(int r,float **a);
vector<float> softmax(vector<float> v);

