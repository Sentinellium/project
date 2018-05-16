#include <iostream>

using namespace std;

class linear_spline{
public:
    linear_spline(int n){
        float *yi  =  new float[n]; //f(x)
        float *xi = new float[n]; //x
        float *hi = new float[n]; //x[i+1]-x[i]
        float *ai = new float[n]; //a coefficient of polynomial
        float *bi = new float[n]; //b coefficient of polynomial

        for(int i = 0; i<n; i++){
            cout <<"Enter x"<<i<<" = ";
            cin >>xi[i];
            cout <<"Enter y"<<i<<" = ";
            cin >>yi[i];
            cout <<endl;

        }
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

};

class cubic_spline{
public:
    cubic_spline(int n){
        float *yi  =  new float[n]; //f(x)
        float *xi = new float[n]; //x
        float *hi = new float[n]; //x[i+1]-x[i]
        float *ai = new float[n]; //a coefficient of polynomial
        float *bi = new float[n]; //b coefficient of polynomial
        float *ci = new float[n]; //c coefficient of polynomial
        float *di = new float[n]; //d coefficient of polynomial
        //float *s1i = new float[n]; //f`(x)
        //float *s2i = new float[n]; //f``(x)

        float *coef1i = new float[n]; //1st coefficient of coef1i[i]*bi[i]+coef2i[i]*bi[i+1]+coef3i*bi[i+2] = coef4i
        float *coef2i = new float[n]; //2nd coefficient of coef1i[i]*bi[i]+coef2i[i]*bi[i+1]+coef3i*bi[i+2] = coef4i
        float *coef3i = new float[n]; //3rd coefficient of coef1i[i]*bi[i]+coef2i[i]*bi[i+1]+coef3i*bi[i+2] = coef4i
        float *coef4i = new float[n]; //4th coefficient of coef1i[i]*bi[i]+coef2i[i]*bi[i+1]+coef3i*bi[i+2] = coef4i
        float *fx = new float[n]; //fx[i] = (yi[i+1]-yi[i])/hi[i];
        float *pi = new float[n]; //pi[0] = coef3i[0]/coef2i[0];
        float *qi = new float[n]; //qi[0] = coef4i[0]/coef2i[0];



        for(int i = 0; i<n; i++){
            cout <<"Enter x"<<i<<" = ";
            cin >>xi[i];
            cout <<"Enter y"<<i<<" = ";
            cin >>yi[i];
            cout <<endl;

        }

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
};

void get_linear(int n){
    linear_spline a(n);
}

void get_cubic(int n){
    cubic_spline a(n);
}

int main()
{
    int n,v;
    cout <<"Enter the amount of values:\n";
    cin >>n;
    cout <<"Enter the type of interpolation(1 for linear,2 for cubic):\n";
    cin >>v;
    for(int i = 0;i < n; i++){
        if(v == 1){
            get_linear(n);
        }
        else{
            get_cubic(n);
        }
    }
    return 0;
}
