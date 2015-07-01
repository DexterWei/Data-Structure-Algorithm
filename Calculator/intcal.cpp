#include<iostream>
#include<stack>
#include<vector>
#include<stdlib.h>
#include<fstream>
using namespace std;

bool read1out(string instr,string& readout,int& position){
       if (instr[position]=='<'||instr[position]=='>'){ //detect << and >> (two character operators)
	       readout.push_back(instr[position]);
	       position++;
	       if(instr[position]==instr[position-1]){
		      readout.push_back(instr[position]);
		      position++;}
		else cout<<"error";
		return 1;//if char was read return 1
	}
	else if(instr[position]=='+'){	//detect unary plus
		if (position==0)
			readout.push_back('p');

		else if((instr[position-1]<'0'||instr[position-1]>'9')\
			&&instr[position-1]!=')')
			readout.push_back('p');
		else
			readout.push_back('+');
		position++;
		return 1;
	}
	else if(instr[position]=='-'){	//detect unary minus
		if (position==0)
			readout.push_back('n');
		else if	((instr[position-1]<'0'||instr[position-1]>'9')\
			&&instr[position-1]!=')')
			
			readout.push_back('n');
		else
			readout.push_back('-');
//		cout<<"'"<<readout<<"'";
		position++;
		return 1;
	}	
	else if(instr[position]=='~'||instr[position]=='*'||instr[position]=='/'||instr[position]=='%'\
		||instr[position]=='&'||instr[position]=='^'||instr[position]=='|'\
		||instr[position]=='('||instr[position]==')'){
			readout.push_back(instr[position]);
			position++;
			return 1;
		}
	else{ while(instr[position]>='0'&&instr[position]<='9'){
		readout.push_back(instr[position]);
		position++;}
		return 0;//if number was read return 0
		}
	}

int getprio(string optor){
	int proi;
	switch (optor[0]){
	case 'p':
		proi=8;
		break;
	case 'n':
		proi=8;
		break;
	case '~':
		proi=7;
		break;
	case '*':
		proi=6;
		break;
	case '/':
		proi=6;
		break;
	case '%':
		proi=6;
		break;
	case '+':
		proi=5;
		break;
	case '-':
		proi=5;
		break;
	case '<':
		proi=4;
		break;
	case '>':
		proi=4;
		break;
	case '&':
		proi=3;
		break;
	case '^':
		proi=2;
		break;
	case '|':
		proi=1;
		break;
	default:
		proi=-1;
		break;
	}
	return proi;
}


void calculate(string optr,stack<int>& opnd){
	int operand1=0,operand2=0;
	switch (optr[0]){
	case 'p':
		operand2=opnd.top();
		opnd.pop();
		opnd.push(operand2);
		break;
	case 'n':
		operand2=opnd.top();
		opnd.pop();
		opnd.push(0-operand2);
		break;
	case '~':
		operand2=opnd.top();
		opnd.pop();
		opnd.push(~operand2);
		break;
	case '*':
		operand2=opnd.top();
		opnd.pop();
		operand1=opnd.top();
		opnd.pop();
		opnd.push(operand1*operand2);
		break;
	case '/':
		operand2=opnd.top();
		opnd.pop();
		operand1=opnd.top();
		opnd.pop();
		opnd.push(operand1/operand2);
		break;
	case '%':
		operand2=opnd.top();
		opnd.pop();
		operand1=opnd.top();
		opnd.pop();
		opnd.push(operand1%operand2);
		break;
	case '+':
		operand2=opnd.top();
		opnd.pop();
		operand1=opnd.top();
		opnd.pop();
		opnd.push(operand1+operand2);
		break;
	case '-':
		operand2=opnd.top();
		opnd.pop();
		operand1=opnd.top();
		opnd.pop();
		opnd.push(operand1-operand2);
		break;
	case '<':
		operand2=opnd.top();
		opnd.pop();
		operand1=opnd.top();
		opnd.pop();
		opnd.push(operand1<<operand2);
		break;
	case '>':
		operand2=opnd.top();
		opnd.pop();
		operand1=opnd.top();
		opnd.pop();
		opnd.push(operand1>>operand2);
		break;
	case '&':
		operand2=opnd.top();
		opnd.pop();
		operand1=opnd.top();
		opnd.pop();
		opnd.push(operand1&operand2);
		break;
	case '^':
		operand2=opnd.top();
		opnd.pop();
		operand1=opnd.top();
		opnd.pop();
		opnd.push(operand1^operand2);
		break;
	case '|':
		operand2=opnd.top();
		opnd.pop();
		operand1=opnd.top();
		opnd.pop();
		opnd.push(operand1|operand2);
		break;
	default:
		break;
	
	}
//	cout<<"operand1:"<<operand1<<"\toperand2:"<<operand2<<"\toperator:"<<optr<<"\tresult:"<<opnd.top()<<endl;
}



int infix2postfix(string infix,string& postfix){
	int len;
	len=infix.size();
	cout<<"infix expression:\t"<<infix<<endl;
	
	stack<int> opnd;

	stack<string> stk;
	
	int position=0;
	string buffer;
	bool isoperator;
	while(position<len){
		isoperator=read1out(infix,buffer,position);
		cout<<"\tread:\t"<<buffer<<endl;
		if(isoperator==0){
			postfix=postfix+' '+buffer+' ';
			cout<<"\t\toutput\t"<<buffer<<' '<<endl;//display output
			
			opnd.push(atoi(buffer.data()));//CALCULATE STACK PUSH
//			cout<<"push operand: "<<opnd.top()<<endl;//
			}
		else if(buffer[0]=='('){
			stk.push(buffer);
			cout<<"\t\tpush stack\t"<<buffer<<endl;//display push
			}
		else if(buffer[0]==')'){
			while((stk.empty()!=1)&&(stk.top()[0]!='(')){
				cout<<"\t\tpop stack\t"<<stk.top()<<endl;//display pop and output
				postfix=postfix+stk.top();
				calculate(stk.top(),opnd);//CALCULATE STACK OPERATOR
//				cout<<"calculate one step and save: "<<opnd.top()<<endl;//
				stk.pop();
			}
			cout<<"\t\tdiscard left parenthesis"<<endl;//display discard
			stk.pop();
			}
		else {
			if((stk.empty()==1)||(stk.top()[0]=='(')){
				stk.push(buffer);
				cout<<"\t\tpush stack\t"<<buffer<<endl;//display push
			}
			else{ while((stk.empty()!=1)&&(stk.top()[0]!='(')&&getprio(buffer)<=getprio(stk.top())){
				cout<<"\t\tpop stack\t"<<stk.top()<<endl;//display pop and output
				calculate(stk.top(),opnd);//CALCULATE STACK OPERATOR
//				cout<<"calculate one step and save: "<<opnd.top()<<endl;//
				postfix=postfix+stk.top();
					stk.pop();
				}
				stk.push(buffer);
				cout<<"\t\tpush stack\t"<<buffer<<endl;//display push
				}
		}
//		cout<<endl;
		buffer.clear();


	}
	while(stk.empty()!=1){
		cout<<"\t\tpop stack\t"<<stk.top()<<endl;//display output
		calculate(stk.top(),opnd);//CALCULATE STACK OPERATOR
//		cout<<"calculate one step and save: "<<opnd.top()<<endl;//
		postfix=postfix+stk.top();
		stk.pop();
	}
	cout<<"converted postfix expression:\t"<<postfix<<endl;
	
	return opnd.top();
}







//int calpost(string postfix){}


int main(){
//	ifstream expressions("input.txt",ifstream::in);
	string infix;
	string postfix;
	int result;
	//while(!expressions.fail()){
	while(getline(cin,infix)){
		if(infix.empty()!=1)
		{
//		cout<<"read line "<<infix<<endl;
		result=infix2postfix(infix,postfix);
		cout<<"RESULT: "<<result<<endl<<endl<<endl;
		infix.clear();
		postfix.clear();
	}
	}
//	expressions.close();

	return 0;
}
