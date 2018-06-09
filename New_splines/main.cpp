#include <iostream>
#include <vector>
#include <fstream>
#include <linear_spline.h>
#include <cubic_spline.h>

using namespace std;


int main()
{
    int n,v;
    cout <<"Enter the amount of values:\n";
    cin >>n;
    cout <<"Enter the type of interpolation(1 for linear,2 for cubic):\n";
    cin >>v;

    if(v == 1){
        linear_spline a(n);
        }
    else{
        cubic_spline a(n);
        a.value(1);
        }
    return 0;
};
