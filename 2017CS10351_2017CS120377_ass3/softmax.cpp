#include <iostream>
#include <cmath>
#include <cstdlib>
#include <vector>
#include <fstream>
using namespace std;

vector<float> softmax(vector<float> v){
    unsigned int i=0;
    float count=0.0;
    vector<float> v2;
    while(i<v.size()){
        count=count+exp(v[i]);
        i++;
    }
    i=0;
    while(i<v.size()){
        v2.push_back((float)(exp(v[i])/count));
        i++;
    }
    
    return v2;
}
