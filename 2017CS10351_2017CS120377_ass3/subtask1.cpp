#include "function.h"
#include <iostream>
#include <cmath>
#include <cstdlib>
#include <vector>
#include <fstream>
using namespace std;

//function to display 2D matrix
void display(float **s,int size){
    for (int i=0;i<size;i++){
        for(int j=0;j<size;j++){
            cout<<s[i][j]<<" ";
        }
        cout<<endl;
    }
}

int maximum(vector<float> v){
    int a=0;
    float max=v[0];
    for(int i=0;i<9;i++){
        if(v[i+1]>max){
            max=v[i+1];
            a=(i+1);
        }
    }
    return a;
}
int main(int argc,char* argv[]){
        if(argc!=6){
		cout<<"Please enter appropriate information, check readme!"<<endl;
		return 0;
	}
	ofstream outdata;
	string matrix_file;
        matrix_file=argv[1]; //For data.txt
	ifstream infile;
        infile.open(matrix_file);
        if(!infile.is_open()){
            cout<< "Error opening file"<< endl;
            return 0;
        }
        
        string y;
        float **a;
        int r=28;
        a=new float*[r];
        for(int i=0;i<r;i++)
                a[i]=new float[r];
        for(int i=0;i<r;i++){
                for(int j=0;j<r;j++){
                        infile >> y;
                        a[i][j]=stof(y);
                }
        }
        infile.close();
        ifstream infile2;
        matrix_file=argv[2]; //For conv1.txt
        infile2.open(matrix_file);
        if(!infile2.is_open()){
            cout<< "Error opening file"<< endl;
            return 0;
        }
        
        // bias1 for storing the bias values which are to be added after performing 1st convolution of data.txt
        float *bias1;
        bias1=new float[20];
        float **q;
        q=new float*[20];
        for(int i=0;i<20;i++)
                q[i]=new float[25];
        for(int i=0;i<20;i++){
                for(int j=0;j<25;j++){
                        infile2 >> y;
                        q[i][j]=stof(y);
                }
        }
        for(int i=0;i<20;i++){
            infile2 >> y;
            bias1[i]=stof(y);
        }
        infile2.close();
        
        // final_ans is a 3D matrix storing the answer of convolution between data.txt and kernels in conv1.txt
        float ***final_ans;
                final_ans=new float**[20];
                for(int i=0;i<20;i++)
                    final_ans[i]=new float*[24];
                for(int i=0;i<20;i++){
                    for(int j=0;j<24;j++){
                        final_ans[i][j]=new float[24];
                    }
                }
        for(int k=0;k<20;k++)
            convolution_matrix_mult(a,28,q[k],5,final_ans[k]); // Function calling for convolution
        for(int k=0;k<20;k++)
            for(int i=0;i<24;i++)
                for(int j=0;j<24;j++)
                    final_ans[k][i][j]=bias1[k]+final_ans[k][i][j]; // Adding bias values
        
        // b is the output matrix storing result of max_pooling on final_ans 
        float ***b;
        b=new float**[20];
        for(int i=0;i<20;i++)
            b[i]=new float*[12];
        for(int i=0;i<20;i++){
            for(int j=0;j<12;j++){
                b[i][j]=new float[12];
            }
        }
        
        for(int k=0;k<20;k++){
            max_pooling(24,final_ans[k],b[k]);
        }
        
        
        ifstream infile3;
        matrix_file=argv[3]; //For conv2.txt
        infile3.open(matrix_file);
        if(!infile3.is_open()){
            cout<< "Error opening file"<< endl;
            return 0;
        }
        
        float ***q2;
        q2=new float **[50];
        for(int i=0;i<50;i++)
            q2[i]=new float*[20];
        
        for(int i=0;i<50;i++){
            for(int j=0;j<20;j++){
                q2[i][j]=new float[25];
            }
        }
        
        for(int i=0;i<50;i++){
            for(int j=0;j<20;j++){
                for(int k=0;k<25;k++){
                    infile3 >> y;
                    q2[i][j][k]=stof(y);
                }
            }
        }
        
        // bias2 for storing the bias values which are to be added after performing 2nd convolution of data.txt
        float *bias2;
        bias2=new float[50];
        for(int i=0;i<50;i++){
            infile3 >> y;
            bias2[i]=stof(y);
        }
        
        infile3.close();
        
        // final_ans2 is a 3D matrix storing the answer of convolution with kernels in conv2.txt
        float ***final_ans2;
        final_ans2=new float**[50];
        for(int i=0;i<50;i++)
            final_ans2[i]=new float*[8];
        for(int i=0;i<50;i++){
            for(int j=0;j<8;j++){
                final_ans2[i][j]=new float[8];
            }
        }
        
        for(int i=0;i<50;i++)
            for(int j=0;j<8;j++)
                for(int k=0;k<8;k++)
                    final_ans2[i][j][k]=0.0;
        
        float **temp;
        temp=new float*[8];
        for(int l=0;l<8;l++){
            temp[l]=new float[8];
        }
        
        for(int i=0;i<50;i++){
            for(int j=0;j<20;j++){
                convolution_matrix_mult(b[j],12,q2[i][j],5,temp); // Function calling for convolution
                for(int p=0;p<8;p++){
                    for(int q=0;q<8;q++){
                        final_ans2[i][p][q]=temp[p][q]+final_ans2[i][p][q];
                        temp[p][q]=0.0;
                    }
                    
                }
            }
        }
        
        for(int k=0;k<50;k++)
            for(int i=0;i<8;i++)
                for(int j=0;j<8;j++)
                    final_ans2[k][i][j]=bias2[k]+final_ans2[k][i][j]; // Adding bias values
    
        // b2 is the output matrix storing result of max_pooling on final_ans2
        float ***b2;
        b2=new float**[50];
        for(int i=0;i<50;i++)
            b2[i]=new float*[4];
        for(int i=0;i<50;i++){
            for(int j=0;j<4;j++){
                b2[i][j]=new float[4];
            }
        }
        
        for(int k=0;k<50;k++){
            max_pooling(8,final_ans2[k],b2[k]);
        }
        
        ifstream infile4;
        matrix_file=argv[4]; //For fc1.txt
        infile4.open(matrix_file);
        if(!infile4.is_open()){
            cout<< "Error opening file"<< endl;
            return 0;
        }
        
        float ***q3;
        q3=new float**[500];
        for(int i=0;i<500;i++)
            q3[i]=new float*[50];
        for(int i=0;i<500;i++){
            for(int j=0;j<50;j++){
                q3[i][j]=new float[16];
            }
        }
        
        for(int i=0;i<500;i++){
            for(int j=0;j<50;j++){
                for(int k=0;k<16;k++){
                    infile4 >> y;
                    q3[i][j][k]=stof(y);
                }
            }
        }
        
        // bias3 for storing the bias values which are to be added after performing 3rd convolution of data.txt
        float *bias3;
        bias3=new float[500];
        for(int i=0;i<500;i++){
            infile4 >> y;
            bias3[i]=stof(y);
        }
        infile4.close();
        
        // final_ans3 is a 3D matrix storing the answer of convolution with kernels in fc1.txt
        float ***final_ans3;
        final_ans3=new float**[500];
        for(int i=0;i<500;i++)
            final_ans3[i]=new float*[1];
        for(int i=0;i<500;i++){
            for(int j=0;j<1;j++){
                final_ans3[i][j]=new float[1];
            }
        }
        
        for(int i=0;i<500;i++)
            for(int j=0;j<1;j++)
                for(int k=0;k<1;k++)
                    final_ans3[i][j][k]=0.0;
        
        float **temp2;
        temp2=new float*[1];
        for(int l=0;l<1;l++){
            temp2[l]=new float[1];
        }
        for(int i=0;i<500;i++){
            for(int j=0;j<50;j++){
                    convolution_matrix_mult(b2[j],4,q3[i][j],4,temp2); //Function calling for convolution
                    for(int p=0;p<1;p++){
                        for(int q=0;q<1;q++){
                            final_ans3[i][p][q]=temp2[p][q]+final_ans3[i][p][q];
                            temp2[p][q]=0.0;
                        }
                    }
                }
            }
        
        for(int k=0;k<500;k++)
            for(int i=0;i<1;i++)
                for(int j=0;j<1;j++)
                    final_ans3[k][i][j]=bias3[k]+final_ans3[k][i][j]; // Adding bias values
        
       // Performing relu after convolution with fc1.txt
       for(int i=0;i<500;i++)
           relu(1,final_ans3[i]);
       
       
       ifstream infile5;
        matrix_file=argv[5]; //For fc2.txt
        infile5.open(matrix_file);
        if(!infile5.is_open()){
            cout<< "Error opening file"<< endl;
            return 0;
        }
        
        float ***q4;
        q4=new float**[10];
        for(int i=0;i<10;i++)
            q4[i]=new float*[500];
        for(int i=0;i<10;i++){
            for(int j=0;j<500;j++){
                q4[i][j]=new float[1];
            }
        }
        
        for(int i=0;i<10;i++){
            for(int j=0;j<500;j++){
                for(int k=0;k<1;k++){
                    infile5 >> y;
                    q4[i][j][k]=stof(y);
                }
            }
        }
        
        // bias4 for storing the bias values which are to be added after performing 2nd convolution of data.txt
        float *bias4;
        bias4=new float[10];
        for(int i=0;i<10;i++){
            infile5 >> y;
            bias4[i]=stof(y);
        }
        infile5.close();
        
        // final_ans4 is a 3D matrix storing the answer of convolution with kernels in fc2.txt
        float ***final_ans4;
        final_ans4=new float**[10];
        for(int i=0;i<10;i++)
            final_ans4[i]=new float*[1];
        for(int i=0;i<10;i++){
            for(int j=0;j<1;j++){
                final_ans4[i][j]=new float[1];
            }
        }
        
        for(int i=0;i<10;i++)
            for(int j=0;j<1;j++)
                for(int k=0;k<1;k++)
                    final_ans4[i][j][k]=0.0;
        
        float **temp4;
        temp4=new float*[1];
        for(int l=0;l<1;l++){
            temp4[l]=new float[1];
        }
        
        for(int i=0;i<10;i++){
            for(int j=0;j<500;j++){
                    convolution_matrix_mult(final_ans3[j],1,q4[i][j],1,temp4); //Function calling for convolution
                    for(int p=0;p<1;p++){
                        for(int q=0;q<1;q++){
                            final_ans4[i][p][q]=temp4[p][q]+final_ans4[i][p][q];
                            temp4[p][q]=0.0;
                        }
                    }
            }
        }
        
        for(int k=0;k<10;k++)
            for(int i=0;i<1;i++)
                for(int j=0;j<1;j++)
                    final_ans4[k][i][j]=bias4[k]+final_ans4[k][i][j]; // Adding bias values
                
        vector<float> v1;
        
        for (int i = 0; i < 10; ++i) {
            v1.push_back(final_ans4[i][0][0]); // Making vector(v1) having values of final_ans4 
        }
        
        vector<float> prob = softmax(v1); // Performing softmax on v1
        
        // Array is used as temporary variable for storing probabilities
        float array[10];
        for(int i=0;i<10;i++)
            array[i]=prob[i];
        
        int arr[5];
        
        // Extracting top 5 probabilities for final output
        for(int i=0;i<5;i++){
            arr[i]=maximum(prob);
            prob[arr[i]]=-1.0;
        }
        
        outdata.open("top5.txt");
        if(!outdata)
            return 0;
        
        // Writing output to file top5.txt
        for(int i=0;i<5;i++){
            outdata<< "CPU_TOP: "<< float(array[arr[i]]*100.0) << " class "<< arr[i] <<" output " << final_ans4[arr[i]][0][0] << endl;
        }
        outdata.close();
        
   return 0;   
        
}















