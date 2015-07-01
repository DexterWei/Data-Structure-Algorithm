#include<iostream>
#include<string>
#include<vector>
#include<stdlib.h>
#include"poly.h"

using namespace std;


complex complex::operator+(complex b){
	complex c;
	c.Re=Re+b.Re;
	c.Im=Im+b.Im;
	return c;
}

complex complex::operator-(complex b){
	complex c;
	c.Re=Re-b.Re;
	c.Im=Im-b.Im;
	return c;
}


complex complex::operator*(complex b){
	complex c;
	c.Re=Re*b.Re-Im*b.Im;
	c.Im=Re*b.Im+Im*b.Re;
	return c;
}

void complex::show(){
	std::cout.setf (ios :: fixed,  ios :: floatfield);

	std::cout.precision(2);
			if (Re!=0.00){
				
				std::cout<<Re;
				
				if(Im>0.00)
					std::cout<<"+"<<Im<<"i";
				else if(Im<0.00)
			 		std::cout<<Im<<"i";
			}
			else if(Im!=0.00)
				std::cout<<Im<<"i";
			else
				std::cout<<double(0);
}


complex str2complex(string str){
	complex c;
	int end=str.length()-1;
	int pointpos1=str.find(".");
	int pointpos2=str.rfind(".");
	
	string re,im;
	int i;
	if(pointpos1!=pointpos2){
		int reend=pointpos1+2;
		int dif=pointpos2=pointpos1;
		
		
		for(i=0;i<=reend;i++) re=re+str[i];
		for(i=reend+1;i<end;i++) im=im+str[i];

	}
	else if(str[end]=='i'){
		for(i=0;i<end;i++) im=im+str[i];
	}
	else 
		re=re+str;
	
	c.Re=atof(re.data());
	c.Im=atof(im.data());
	return c;	
}



//poly(vector<string> co);
 poly::poly(vector<string> co){
 	degree=co.size()-1;
	//coeff.resize(degree+1);
 	int i;
	for(i=0;i<=degree;i++){
		complex elem=str2complex(co[i]);
		coeff.push_back(elem);
	} 	
 }
 
// poly operator+(poly b);
poly poly::operator+(poly b){
	poly selfa;
	selfa.degree=degree;
	selfa.coeff=coeff;

	poly selfb;
	selfb.degree=b.degree;
	selfb.coeff=b.coeff;

	poly c;
	int upbound;
	if(degree>b.degree){c.degree=degree;upbound=b.degree;}
	else{c.degree=b.degree;upbound=degree;}

	selfa.degree=selfb.degree=c.degree;
	c.coeff.resize(c.degree+1);
	int j,k;
	for(j=0;j<(c.degree-degree);j++){
	selfa.coeff.push_back(str2complex("0.00"));
	}
	
	for(k=0;k<(c.degree-b.degree);k++){
	selfb.coeff.push_back(str2complex("0.00"));
	}

	int i;
	for(i=0;i<(c.degree+1);i++){
		c.coeff[i]=selfa.coeff[i]+selfb.coeff[i];
	}
	return c;
}

// poly operator-(poly b);
 poly poly::operator-(poly b){
	poly selfa;
	selfa.degree=degree;
	selfa.coeff=coeff;

	poly selfb;
	selfb.degree=b.degree;
	selfb.coeff=b.coeff;

	poly c;
	int upbound;
	if(degree>b.degree){c.degree=degree;upbound=b.degree;}
	else{c.degree=b.degree;upbound=degree;}

	selfa.degree=selfb.degree=c.degree;
	c.coeff.resize(c.degree+1);
	int j,k;
	for(j=0;j<(c.degree-degree);j++){
	selfa.coeff.push_back(str2complex("0.00"));
	}
	
	for(k=0;k<(c.degree-b.degree);k++){
	selfb.coeff.push_back(str2complex("0.00"));
	}

	int i;
	for(i=0;i<(c.degree+1);i++){
		c.coeff[i]=selfa.coeff[i]-selfb.coeff[i];
	}
	return c;
}
 
// poly operator*(poly b);
 poly poly::operator*(poly b){
	poly c;
	c.degree=degree+b.degree;
	c.coeff.resize(c.degree+1);
	int i,j,k;
	complex **mult;
		mult=new complex*[degree];
		for(k=0;k<=degree;k++)
		mult[k]=new complex[b.degree];

	for(i=0;i<=degree;i++){
		for(j=0;j<=b.degree;j++){
			mult[i][j]=coeff[i]*b.coeff[j];
			c.coeff[i+j]=c.coeff[i+j]+mult[i][j];
		}
	}
	return c;
 }
 
//poly operator^(int power);
poly poly::operator^(int power){

	poly c;
	c.degree=0;
	c.coeff.push_back(str2complex("1.00"));
	
	poly self;
	self.degree=degree;
	self.coeff=coeff;

	int i;
	for(i=0;i<power;i++){
		c=self * c;
	}
	return c;
}

// poly operator()(poly b);
poly poly::operator()(poly b){
	poly c;
	c.degree=0;
	c.coeff.resize(1);
	c.coeff[0]=str2complex("0.00");

	int i;
	poly coefficient;
	coefficient.degree=0;
	coefficient.coeff.resize(1);

	for(i=0;i<=degree;i++){
		coefficient.degree=0;
	coefficient.coeff.resize(1);
	coefficient.coeff[0]=coeff[i];
	c=c+coefficient*(b^i);
	}
	return c;
}

// complex eval(complex b);		//ecaluation over constant
poly poly::eval(string str){
	poly b;
	b.degree=0;b.coeff.push_back(str2complex(str));
	
	poly c;
	c.degree=0;
	c.coeff.push_back(str2complex("0.00"));
	
	poly self;
	self.degree=degree;
	self.coeff=coeff;


	c=self(b);

	return c;
}

// void show()
void poly::show(){
	int i;

	complex zero(0.00,0.00);

	while((coeff[(coeff.size()-1)].Re==0.00)&&(coeff[(coeff.size()-1)].Im==0.00)){coeff.pop_back();degree--;}

	for(i=0;i<=degree;i++){
	complex s=coeff[i];
	s.show();cout<<' ';
	}
	cout<<'\n';
}