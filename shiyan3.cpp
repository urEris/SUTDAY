#include <iostream>
using namespace std;

void swap(int n,int m);

int main()
{
int a,b;
int &c=a;
int &d=b;
cout<< "input a" <<endl;
cin >> a;
cout<< "input b" <<endl;
cin >> b;
swap(a,b);
cout << c <<endl;
cout << d <<endl;
return 0;
}

void swap(int n,int m)
{
    int temp;
    temp=n;
    n=m;
    m=temp;
}