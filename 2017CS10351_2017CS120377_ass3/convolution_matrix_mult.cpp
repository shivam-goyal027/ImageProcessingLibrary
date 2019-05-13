#include "function.h"
#include <iostream>
#include <cmath>
#include <cstdlib>
#include <vector>
#include <fstream>
using namespace std;

void convert(float *ans, float **final_ans,int size){
    for(int i=0;i<size*size;i++){
        int l=(i)/size;
        int m=(i)%size;
        final_ans[l][m]=ans[i];
    }
}

void matrix_mult(float **a,float *q,float *ans,int c1,int c2){
    for(int l=0;l<(c1-c2+1)*(c1-c2+1);l++){
        float count=0.0;
        for(int n=0;n<c2*c2;n++){
            count=count+a[l][n]*q[n];
        }
        ans[l]=count;
    }
}

void convolution_matrix_mult(float **a,int c1,float *q, int c2,float **final_ans){
    
    //without padding
    float **c;
    c=new float*[(c1-c2+1)*(c1-c2+1)];
    for(int i=0;i<(c1-c2+1)*(c1-c2+1);i++)
        c[i]=new float[c2*c2];
    int g=0;
    int r=0;
    for(int i=0;i<(c1-c2+1);i++){
        for(int j=0;j<(c1-c2+1);j++){
            r=0;
            for(int w=i;w<i+c2;w++){
                for(int t=j;t<j+c2;t++){
                  c[g][r]=a[w][t];
                  r++;
                }
            }
        g++;
        }
    }

    float *ans;
    ans=new float[(c1-c2+1)*(c1-c2+1)];

    matrix_mult(c,q,ans,c1,c2);
    
    convert(ans,final_ans,c1-c2+1);
}
