#include "function.h"
#include <iostream>
#include <cmath>
#include <cstdlib>
#include <vector>
#include <fstream>
using namespace std;


float maxo(float a,float b){
    if(a>b) return a;
    else return b;
}

void relu(int r,float **a)
{
	 for(int i=0;i<r;i++){
         	for(int j=0;j<r;j++){
            		a[j][i]=maxo(0.0,a[j][i]);
		}
	}
}
