#include <stdio.h>
#include<iostream>
#include<stdio.h>
#include<algorithm>
#include<string>
#include<vector>
extern "C"{
#include "avl.h"
}
using namespace std;

void postorder_string_avl (const struct avl_node *node){
	if (node == NULL)
		return ;
	printf("%s ",(char*)node->avl_data);

	if(node->avl_link[0]!=NULL || node->avl_link[1]!= NULL){
		putchar('(');
		postorder_string_avl(node->avl_link[0]);
		putchar(',');
		putchar(' ');
		postorder_string_avl(node->avl_link[1]) ;
		putchar(')') ;
	}}
int string_compare(const void *pa , const void *pb , void *param)
{
	string a((const char*)pa) ;
	string b((const char*)pb) ;
	int sizea=a.size();
	int sizeb=b.size();

	bool bigger=lexicographical_compare(a.data(),a.data()+sizea,b.data(),b.data()+sizeb);
	bool smaller=lexicographical_compare(b.data(),b.data()+sizeb,a.data(),a.data()+sizea);	
	if ( bigger==1&&smaller==1 ) return 0;
	else if ( bigger==1) return +1;
	else return -1 ;
}

int get_height(struct avl_table *tree){
	struct avl_traverser trav;
	int height;
	int max_height=0;
	avl_t_init(&trav,tree);
	while(avl_t_next(&trav)!=NULL){
		height=(int)trav.avl_height;
		if(height>max_height){
			max_height=height;
		}
		}
	return max_height;
	}

int main ( ){
	vector<string> names;
	names.push_back("C");
	names.push_back("Java");
	names.push_back("C++");
	names.push_back("Objective-C");
	names.push_back("C#");
	names.push_back("PHP");
	names.push_back("Visual Basic");
	names.push_back("Python");
	names.push_back("Perl");
	names.push_back("Ruby");
	names.push_back("JavaScript");
	names.push_back("Lisp");
	names.push_back("Pascal");
	names.push_back("Haskell");
	names.push_back("Scala");
	names.push_back("Fortran");
	names.push_back("Prolog");
	names.push_back("Assembly");
	names.push_back("Verilog");
	names.push_back("Erlang");
	names.push_back("MATLAB");
	names.push_back("Bash");
	names.push_back("SmallTalk");
	names.push_back("Caml");
	names.push_back("Scheme");
	names.push_back("Go");
	names.push_back("Ada");
	names.push_back("Cobol");
	names.push_back("Awk");
	names.push_back("Tcl/Tk");
	names.push_back("Delphi");
	names.push_back("Limbo");
	int num_name=names.size();
	
	struct avl_table *tree;
	tree = avl_create(string_compare,NULL,NULL) ;
	int i ;
	for ( i =0; i <num_name; i++){
		char* element = &names[i][0];
		void **p = avl_probe(tree,element) ;
	}
	postorder_string_avl( tree->avl_root ) ;
	puts(" ") ;

	int height=get_height(tree);
	cout<<endl<<"AVL height: "<<height<<endl;
	return 0 ;

}
