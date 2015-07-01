#include<iostream>
#include<fstream>
#include<stdio.h>
#include<stdlib.h>
#include<vector>
#include<string.h>
using namespace std;

class tree_node{
	public:
		bool is_leaf; //is_leaf=1 if true
		int feature;
		double threshold;
		int decision; // either 1 or -1
		tree_node* left;
		tree_node* right;
};

tree_node* build_tree(double** data,int theta,int fea,int num_epl,int* example){
	tree_node* self=new tree_node;
	vector<double> label;
	for(int i=0;i<num_epl;i++){
		label.push_back(data[example[i]][0]);
	}
	int n=0,p=0;
	for(int i=0;i<num_epl;i++){
		if(label[i]==1)
			p++;
		else
			n++;
			
	}
	if(n==0||p==0){
		self->is_leaf=true;
		self->decision=label[0];
	}
	else if(num_epl<=theta){
		self->is_leaf=true;
		if(n>=p)
			self->decision=-1;
		else
			self->decision=1;
	}
	else{		
		self->is_leaf=false;
		vector<double> feature;
		int best_feature=0;//hold the best feature for this decision node
		double best_conf=1.0; //hold the best confusion
		double threshold=0.0; //hold the threshold
		for(int j=0;j<fea;j++){
			feature.clear();
			for(int i=0;i<num_epl;i++){
				feature.push_back(data[example[i]][j+1]);
			}
			{	double fea_max=feature[0];
				double th;
				for(int i=0;i<feature.size();i++){
					int r_positive=0;
					int r_negative=0;
					int l_positive=0;
					int l_negative=0;
					th=feature[i];
					if(th>=fea_max) fea_max=th;
					if(i==num_epl-1) {
						feature.push_back(fea_max+0.1);//
					}
					for(int k=0;k<num_epl;k++){
						if(feature[k]<th){	//set to left if less than(<) threshold
							if(label[k]==1)
								l_positive++;
							else
								l_negative++;
						}
						else{
							if(label[k]==1)
								r_positive++;
							else
								r_negative++;
						}}
					int r=r_positive+r_negative;
					int l=l_positive+l_negative;
					double cr=1.0-(double(r_positive)/double(r))*(double(r_positive)/double(r))-\
						  (double(r_negative)/double(r))*(double(r_negative)/double(r));
					double cl=1.0-(double(l_positive)/double(l))*(double(l_positive)/double(l))-\
						  (double(l_negative)/double(l))*(double(l_negative)/double(l));
					double confuse=(double(r)/double(num_epl))*cr+(double(l)/double(num_epl))*cl;
					if(confuse<best_conf){
						best_conf=confuse;
						best_feature=j;
						threshold=th;
					}
				}
			}
		}
		self->feature=best_feature;
		self->threshold=threshold;
		vector<int> left;
		vector<int> right;
		feature.clear();
		for(int i=0;i<num_epl;i++){
			feature.push_back(data[example[i]][best_feature+1]);
		}
		for(int k=0;k<num_epl;k++){
			if(feature[k]<threshold){	//set to left if less than(<) threshold
				left.push_back(example[k]);
			}
			else{
				right.push_back(example[k]);
			}
		}
		int ll=left.size();
		int lr=right.size();
		int L[ll];
		int R[lr];
		for(int i=0;i<ll;i++) {
			L[i]=left[i];
		}
		for(int i=0;i<lr;i++) {
			R[i]=right[i];
		}
		self->left=build_tree(data,theta,fea,ll,L);
		self->right=build_tree(data,theta,fea,lr,R);
	}
	return self;
}
ofstream dir;

void write_tree(tree_node* father){
	if(father->is_leaf==true){
		dir<<"return "<<father->decision<<";\n";
	}
	else{
		dir<<"if(attr["<<father->feature<<"]<"<<father->threshold<<"){\n";
		write_tree(father->left);
		dir<<"}"<<endl;
		dir<<"else {"<<endl;
		write_tree(father->right);
		dir<<"}"<<endl;
	}
}


int main(int argc,char** argv){
	int n,m;
	int theta=atoi(argv[2]);
	double **train_data;
	FILE* data=fopen(argv[1],"r");
	fscanf(data,"%d %d",&n,&m);
	train_data=(double**)malloc(n*sizeof(double*));
	for(int i=0;i<n;i++)
		train_data[i]=(double*)malloc((m+1)*sizeof(double));
	for(int i= 0; i < n; ++i) {
		for(int j=0;j<=m;j++){
			fscanf(data,"%lf",&train_data[i][j]);
		}		
	}
	int example[n];
	for(int i=0;i<n;i++){
		example[i]=i;
	}
	tree_node* root=build_tree(train_data,theta,m,n,example);
	dir.open ("tree_pred.h", std::ofstream::out | std::ofstream::app);
	dir<<"#include<iostream>\n";
	dir<<"int tree_predict(double* attr){"<<endl;
	write_tree(root);
	dir<<"}";
	dir.close();
	return 0;
}
