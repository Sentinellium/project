#ifndef LINEAR_SPLINE_H
#define LINEAR_SPLINE_H

#include <iostream>
#include <fstream>

using namespace std;

class linear_spline
{
protected:
    int n;
    float *yi; //f(x)
    float *xi; //x
    float *hi; //x[i+1]-x[i]
    float *ai; //a coefficient of polynomial
    float *bi; //b coefficient of polynomial
public:
    linear_spline(int c){
        n = c;
        yi  =  new float[n]; //f(x)
        xi = new float[n]; //x
        hi = new float[n]; //x[i+1]-x[i]
        ai = new float[n]; //a coefficient of polynomial
        bi = new float[n]; //b coefficient of polynomial

        ifstream fin("C:\\Users\\Sentinel\\Documents\\project_spline\\input.txt");
        int m, k;
        {
            k = 0;
            while (fin >> m)
            {
                if(k<n){
                    xi[k]=m;
                }
                else{
                    yi[k-n]=m;
                }
                k++;
            }
        }
        fin.close();
        cin.get();

        /*                         // MANUAL INPUT
        for(size_t i(0); i<n; i++){
            cout <<"Enter x"<<i<<" = ";
            cin >>xi[i];
            cout <<"Enter y"<<i<<" = ";
            cin >>yi[i];
            cout <<endl;

        }
        */

        //determination cycle for hi,ai,bi
        for(size_t i(0); i < n-1; i++){
            hi[i] = xi[i+1] - xi[i];
            ai[i] = ((yi[i]/hi[i]) - xi[i]*(yi[i+1]/hi[i]));
            bi[i] = (yi[i+1]/hi[i]) - (yi[i]/hi[i]);
        }

        //determination cycle for ai,bi
        for(size_t i(0); i<n; i++){
            ai[i] = ((yi[i]/hi[i])*xi[i+1]-xi[i]*(yi[i+1]/hi[i]));
            bi[i] = (yi[i+1]/hi[i])-(yi[i]/hi[i]);
        }

        //program output
        for(size_t i(0); i<n-1 ; i++){
            cout <<"F(x) = "<<ai[i]<<"+"<<bi[i]<<"*x"<<endl;
            };
        }

    ~linear_spline(){
        delete []ai;
        delete []bi;
        delete []hi;
        delete []xi;
        delete []yi;
    }

    //finding the x value of the interpolated spline
    void value(float x){
        for(size_t i(0); i < n; i++){

            if(x>=xi[i])
            {
                float j=ai[i]+bi[i]*x;
                cout <<j<<endl;
                break;
            }
        }

    }

};

#endif // LINEAR_SPLINE_H
