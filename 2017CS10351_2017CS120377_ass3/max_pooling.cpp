#include "function.h"
#include <iostream>
#include <cmath>
#include <cstdlib>
#include <vector>
#include <fstream>
using namespace std;

float max(float a,float b,float c,float d){
    
    if((b<a || b==a) && (c<a || c==a) && (d<a || d==a))
        return a;
    else if((a<b || a==b) && (c<b || c==b) && (d<b || d==b))
            return b;
    else if((b<c || b==c) && (a<c || a==c) && (d<c || d==c))
            return c;
    else return d;
}

void max_pooling(int r,float **a, float **b)
{
	if(r%2==0){
        	int p=0; int q=0;
        	for(int i=0;i<r-1;){
                        q=0;
            		for (int j=0;j<r-1;){
                		b[p][q]=max(a[i][j],a[i+1][j],a[i][j+1],a[i+1][j+1]);
                		j=j+2;
                		q++;
            		} 
            	i=i+2;
            	p++;
        	}
	}
	else{
		float **m;
        	m=new float*[r+1];
        	for(int i=0;i<r+1;i++)
            	m[i]=new float[r+1];
        
        	//column major order input
        	for(int i=0;i<r+1;i++){
            		for(int j=0;j<r+1;j++){
                		if(i<r && j<r){
                    			m[i][j]=a[i][j];
                		}
				else{
                    			m[i][j]=0.0;
                		}
            		}
                }
        	int p=0; int q=0;
        	for(int i=0;i<r;){
                        q=0;
            		for (int j=0;j<r;){
                		b[p][q]=max(m[i][j],m[i+1][j],m[i][j+1],m[i+1][j+1]);
                		j=j+2;
                		q++;
            		} 
            	i=i+2;
            	p++;
        	}
	}
}
