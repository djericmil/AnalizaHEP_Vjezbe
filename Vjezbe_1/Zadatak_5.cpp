#include<iostream>  
using namespace std; 

double my_cube(double x)
{
return x*x*x;
}


int main() 
{ 
    int x; 
	cout << "Type a number: ";
	cin >> x;
	cout << my_cube(x);
    return 0; 
}
