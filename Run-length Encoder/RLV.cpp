#include<iostream>
#include<iterator>
#include<vector>
#include"RLV.h"
#define MAXINT 779
using namespace std;

ostream& operator<<(ostream& out,RLV a){
	
	if(a.size()!=0){
		for(int i=0;i<a.num_elem-1;i++){
			out<<a.runlength[1][i]<<' '<<a.runlength[0][i]<<' ';
		}
		out<<a.runlength[1].back()<<' '<<a.runlength[0].back();
	}
	return out;
}


int RLV::size(){
	return length;	
	}

int RLV::size_compressed(){
	return num_elem;	
}

int RLV::operator[](int pos){
	if(pos<0||pos>length){
		cerr<<"OHOHOH.\n";
		return MAXINT;}
	else{
		int i;
		pair<int,int> location=position(pos);
		i=location.first;
		return runlength[0][i];
	}
}


pair<int,int> RLV::position(int pos){
	int sum=0;
	int i=0;
	while(sum<pos+1){
		sum=sum+runlength[1][i];
		i++;
	}
	pair<int,int> result=make_pair(i-1,pos-sum+runlength[1][i-1]);//first is the index of the corresponding rlv
						//second is the index in that 'run', both  start from 0
	return result;
}

void RLV::insert(int pos, int value){
	if(pos>length||pos<0)
		cerr<<"OHOHOH.\n";
	else if(pos==length)
		push_back(value);/////////
	else{
		pair<int,int> location=position(pos);
		int i=location.first;
		int j=location.second;

		if(value==runlength[0][i])
			runlength[1][i]++;
		else if(j==0){
			if(i>0){
				if(value==runlength[0][i-1])
					runlength[1][i-1]++;
				else{
					runlength[0].insert(runlength[0].begin()+i,1,value);
					runlength[1].insert(runlength[1].begin()+i,1,1);
					num_elem++;
				}
			}
			else{
				runlength[0].insert(runlength[0].begin(),1,value);
				runlength[1].insert(runlength[1].begin(),1,1);
				num_elem++;
			}
		}
		else { int ori_val=runlength[0][i];
			int ori_len=runlength[1][i];
			runlength[0].insert(runlength[0].begin()+i+1,1,ori_val);
			runlength[1].insert(runlength[1].begin()+i+1,1,ori_len-j);
			runlength[1][i]=j;
			runlength[0].insert(runlength[0].begin()+i+1,1,value);
			runlength[1].insert(runlength[1].begin()+i+1,1,1);
			num_elem++;
			num_elem++;
		}
		length++;
	}	
}

void RLV::erase(int pos){
	if(pos>=length||pos<0){
		cerr<<"OHOHOH.\n";
	}
	else{
		pair<int,int> location=position(pos);
		int i=location.first;
		int j=location.second;
		if(runlength[1][i]!=1){
			runlength[1][i]--;
			length--;
		}
		else{//when length for this run is 1
			if(i==0){
				runlength[0].erase(runlength[0].begin());
				runlength[1].erase(runlength[1].begin());
				num_elem--;
			}
			else if(i==(num_elem-1)){
				runlength[0].erase(runlength[0].end()-1);
				runlength[1].erase(runlength[1].end()-1);
				num_elem--;
			}
			else{
				if(runlength[0][i-1]==runlength[0][i+1]){
					runlength[1][i-1]=runlength[1][i-1]+runlength[1][i+1];
					runlength[0].erase(runlength[0].begin()+i);
					runlength[1].erase(runlength[1].begin()+i);
					runlength[0].erase(runlength[0].begin()+i);
					runlength[1].erase(runlength[1].begin()+i);
					num_elem--;
					num_elem--;
				}
				else{
					runlength[0].erase(runlength[0].begin()+i);
					runlength[1].erase(runlength[1].begin()+i);
					num_elem--;
				}

			}
			length--;
		}
	}
}
int RLV::pop_back(){
	if(length==0){
		cerr<<"OHOHOH.\n";
		return MAXINT;
	}
	else{
		int val=runlength[0].back();
			erase(length-1);
		return val;
	}
}


void RLV::push_back(int value){
	if(length==0){
		runlength[0].push_back(value);
		runlength[1].push_back(1);
		num_elem++;
		length++;
	}
	else{
		if(value==runlength[0].back())
			runlength[1].back()++;
		else{
			runlength[0].push_back(value);
			runlength[1].push_back(1);
			num_elem++;
		}
		length++;
	}
}
void RLV::clear(){
	runlength[0].clear();
	runlength[1].clear();
	length=0;
	num_elem=0;
	}

