#include "complex.h"
#include <iostream>
#include <vector>
using namespace std;

void sortByAbsValue(vector<Complex>& v) // bubble sort
{
    int n = v.size();
    
    for(int i = 0; i < n-1; ++i)
    {
        for(int j = 0; j < n-1-i; ++j)
        {
            if(v[j].absoluteValue() > v[j+1].absoluteValue())
                swap(v[j], v[j+1]);
        }
    }
}

int main()
{
    //input number 'N', then 'N' complex numbers by their coefficients 'a' and 'b'
    int n; cin >> n;
    vector<Complex> v;
    for(int i = 0; i < n; ++i)
    {
        int a, b;
        cin >> a >> b;
        v.push_back(Complex(a, b));
    }
    
    sortByAbsValue(v);
    
    for(int i = 0; i < n; ++i){
        cout << v[i].getReal() << " " << v[i].getImaginary() << "\n";
    }
}
