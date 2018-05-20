#include "spline.h"
#include <iostream>
#include <fstream>

using namespace std;


class linear_spline{
public:
    int n;
    float *yi; //f(x)
    float *xi; //x
    float *hi; //x[i+1]-x[i]
    float *ai; //a coefficient of polynomial
    float *bi; //b coefficient of polynomial

    linear_spline(int c){

        ifstream fin("C:\\Users\\Sentinel\\Documents\\project_spline\\input.txt");
        int m, k;
        int A[1000];
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
            }
            for (int i = 0; i < k; i++)
            {
                cout << A[i] << " ";
            }
        }
        fin.close();
        cin.get();


        n = c;
        yi  =  new float[n]; //f(x)
        xi = new float[n]; //x
        hi = new float[n]; //x[i+1]-x[i]
        ai = new float[n]; //a coefficient of polynomial
        bi = new float[n]; //b coefficient of polynomial

        /*                         // MANUAL INPUT
        for(int i = 0; i<n; i++){
            cout <<"Enter x"<<i<<" = ";
            cin >>xi[i];
            cout <<"Enter y"<<i<<" = ";
            cin >>yi[i];
            cout <<endl;

        }
        */

        for(int i = 0; i < n-1; i++){
            hi[i] = xi[i+1] - xi[i];
            ai[i] = ((yi[i]/hi[i])-xi[i]*(yi[i+1]/hi[i]));
            bi[i] = (yi[i+1]/hi[i])-(yi[i]/hi[i]);
        }
        for(int i = 0; i<n; i++){
            ai[i] = ((yi[i]/hi[i])*xi[i+1]-xi[i]*(yi[i+1]/hi[i]));
            bi[i] = (yi[i+1]/hi[i])-(yi[i]/hi[i]);
        }
        for(int i = 0; i<n-1 ; i++){
            cout <<"F(x) = "<<ai[i]<<"+"<<bi[i]<<"*x"<<endl;
            };
        }
    void value(int x){
        for(int i = 0; i < n; i++){
            if(x>=xi[i]){
                int j=ai[i]+bi[i]*x;
                cout <<j;
                break;
            }
        }

    }

};

class cubic_spline{
public:
    int n;
    float *yi; //f(x)
    float *xi; //x
    float *hi; //x[i+1]-x[i]
    float *ai; //a coefficient of polynomial
    float *bi; //b coefficient of polynomial
    float *ci; //c coefficient of polynomial
    float *di; //d coefficient of polynomial
    //float *s1i; //f`(x)
    //float *s2i; //f``(x)

    float *coef1i; //1st coefficient of coef1i[i]*bi[i]+coef2i[i]*bi[i+1]+coef3i*bi[i+2] = coef4i
    float *coef2i; //2nd coefficient of coef1i[i]*bi[i]+coef2i[i]*bi[i+1]+coef3i*bi[i+2] = coef4i
    float *coef3i; //3rd coefficient of coef1i[i]*bi[i]+coef2i[i]*bi[i+1]+coef3i*bi[i+2] = coef4i
    float *coef4i; //4th coefficient of coef1i[i]*bi[i]+coef2i[i]*bi[i+1]+coef3i*bi[i+2] = coef4i
    float *fx; //fx[i] = (yi[i+1]-yi[i])/hi[i];
    float *pi; //pi[0] = coef3i[0]/coef2i[0];
    float *qi; //qi[0] = coef4i[0]/coef2i[0];

    cubic_spline(int c){
        n = c;
        yi  =  new float[n]; //f(x)
        xi = new float[n]; //x
        hi = new float[n]; //x[i+1]-x[i]
        ai = new float[n]; //a coefficient of polynomial
        bi = new float[n]; //b coefficient of polynomial
        ci = new float[n]; //c coefficient of polynomial
        di = new float[n]; //d coefficient of polynomial
        //s1i = new float[n]; //f`(x)
        //s2i = new float[n]; //f``(x)

        coef1i = new float[n]; //1st coefficient of coef1i[i]*bi[i]+coef2i[i]*bi[i+1]+coef3i*bi[i+2] = coef4i
        coef2i = new float[n]; //2nd coefficient of coef1i[i]*bi[i]+coef2i[i]*bi[i+1]+coef3i*bi[i+2] = coef4i
        coef3i = new float[n]; //3rd coefficient of coef1i[i]*bi[i]+coef2i[i]*bi[i+1]+coef3i*bi[i+2] = coef4i
        coef4i = new float[n]; //4th coefficient of coef1i[i]*bi[i]+coef2i[i]*bi[i+1]+coef3i*bi[i+2] = coef4i
        fx = new float[n]; //fx[i] = (yi[i+1]-yi[i])/hi[i];
        pi = new float[n]; //pi[0] = coef3i[0]/coef2i[0];
        qi = new float[n]; //qi[0] = coef4i[0]/coef2i[0];

        ifstream fin ("C:\\Users\\Sentinel\\Documents\\project_spline\\input.txt");
        int m, k;
        int A[1000];
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
            }
            for (int i = 0; i < k; i++)
            {
                cout << A[i] << " ";
            }
        }
        fin.close();
        cin.get();

        /*                         // MANUAL INPUT
        for(int i = 0; i<n; i++){
            cout <<"Enter x"<<i<<" = ";
            cin >>xi[i];
            cout <<"Enter y"<<i<<" = ";
            cin >>yi[i];
            cout <<endl;

        }
        */

        for(int i = 0; i<n; i++){
            ai[i] = yi[i];
        }
        for(int i = 0; i<n-1; i++){
            hi[i] = xi[i+1]-xi[i];
            fx[i] = (yi[i+1]-yi[i])/hi[i];

        }
        for(int i = 0; i<n-1 ; i++){
            coef1i[i] = 1/hi[i];
            coef2i[i] = 2*(1/hi[i]+1/hi[i]);
            coef3i[i] = 1/hi[i];
            coef4i[i] = 3*(fx[i+1]/hi[i+1]+fx[i]/hi[i]);
        }
        coef1i[0] = 0;
        coef3i[n-1] = 0;
        pi[0] = coef3i[0]/coef2i[0];
        qi[0] = coef4i[0]/coef2i[0];
        for(int i = 1; i<n-1 ; i++){
            pi[i] = coef3i[i]/((-1)*coef2i[i]-pi[i-1]*coef1i[i]);
            qi[i] = (coef1i[i]*qi[i-1]-coef4i[i])/((-1)*coef2i[i]-coef1i[i]*pi[i-1]);
            }
        bi[n-1] = qi[n-1];
        for(int i = n-2;i>=0;i--){
            bi[i] = pi[i]*bi[i+1]+qi[i];
        }
        for(int i = 0;i<n;i++){
            ci[i] = (3*fx[i]-bi[i+1]-2*bi[i])/hi[i];
            di[i] = (bi[i]+bi[i+1]-2*fx[i])/(hi[i]*hi[i]);

        }
        for(int i = 0; i<n-1 ; i++){
            cout <<"F(x) = "<<ai[i]<<"+"<<bi[i]<<"(x-"<<xi[i]<<")+"<<ci[i]<<"(x-"<<xi[i]<<")^2+"<<di[i]<<"(x-"<<xi[i]<<")^3; "<<xi[i]<<"< x < "<<xi[i+1]<<endl;
            };


    }
    void value(int x){
        for(int i = 0; i < n; i++){
            if(x>=xi[i]){
                int j=ai[i]+bi[i]*(x-xi[i])+ci[i]*(x-xi[i])*(x-xi[i])+di[i]*(x-xi[i])*(x-xi[i])*(x-xi[i]);
                cout <<j;
                break;
            }
        }

    }
};
