#include<iostream>
#include <stdio.h>
#include <stdlib.h>
extern "C"{
#include "avl.h"
}
using namespace std;
void postorder_float_avl (const struct avl_node *node){
	if (node == NULL)
		return ;
	printf( "%f ", *( ( float *) node->avl_data ) ) ;
	if(node->avl_link[0]!=NULL || node->avl_link[1]!= NULL){
		putchar('(');
		postorder_float_avl(node->avl_link[0]);
		putchar(',');
		putchar(' ');
		postorder_float_avl(node->avl_link[1]) ;
		putchar(')') ;
	}}

int double_compare(const void *pa , const void *pb , void *param )
{
	double a = *(const double *) pa ;
	double b = *(const double *) pb ;
	if ( a < b ) return -1;
	else if ( a > b ) return +1;
	else return 0 ;
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
	int max_insert=0,min_insert=AVL_MAX_HEIGHT,avg_insert=0;
	int max_remove=0,min_remove=AVL_MAX_HEIGHT,avg_remove=0;
	int times=10000,R=4096,R2=2048;
	
	for(int round=0;round<times;round++){
	//insertion
		double generated[R];
		for(int k=0;k<R;k++){
			generated[k]=(double)((double)(rand()%12800)/(double)12800);
		}
		struct avl_table *tree;
		tree = avl_create(double_compare,NULL,NULL) ;
		for (int i =0; i <R; i++){
			void **p = avl_probe(tree,&generated[i]) ;
		}
		int height=get_height(tree);

		avg_insert=avg_insert+height;
		if(height>max_insert) max_insert=height;
		if(height<min_insert) min_insert=height;
	//removal
		for(int i=0;i<R2;i++){
			avl_delete(tree,&generated[i]);
			}
		int height2=get_height(tree);
		
		avg_remove=avg_remove+height2;
		if(height2>max_remove) max_remove=height2;
		if(height2<min_remove) min_remove=height2;
	}
	double average_insert=(double)((double)avg_insert/(double)times);
	double average_remove=(double)((double)avg_remove/(double)times);
	cout<<"AVL:"<<endl;
	cout<<"max height after insertion: "<<max_insert<<endl;
	cout<<"min height after insertion: "<<min_insert<<endl;
	cout<<"avg height after insertion: "<<average_insert<<endl;
	cout<<"max height after removal: "<<max_remove<<endl;
	cout<<"min height after removal: "<<min_remove<<endl;
	cout<<"avg height after removal: "<<average_remove<<endl;

	return 0 ;

}
