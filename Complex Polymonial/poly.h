#include<iostream>
#include<stdlib.h>
#include<iomanip>
#include<vector>
#include<string>

using namespace std;

// define class complex number
class complex{
	
	public:
		double Re, Im;
		
		complex() {Re=Im=0.00;}
	
		complex(double a, double b){Re=a;Im=b;}
		
		complex operator+(complex b);
			
		complex operator-(complex b);
			
		complex operator*(complex b);
			
		void show();
};



//define class polynomial

class poly{
	
public:
 int degree;
 vector<complex> coeff;

 poly(){degree=0;}
 
 poly(vector<string> co);
 
 poly operator+(poly b);
 
 poly operator-(poly b);
 
 poly operator*(poly b);
 
 poly operator^(int power);
 
 poly operator()(poly b);
 
 poly eval(string str);		//evaluation over constant
 
 void show();
};


