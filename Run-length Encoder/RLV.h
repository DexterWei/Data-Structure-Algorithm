#include<iostream>
#include<iterator>
#include<vector>
#define MAXINT 779
using namespace std;

class RLV{
	public:
		vector< vector<int> > runlength;
		int length;
		int num_elem;

		RLV(){
			vector<int> ele;
			vector<int> len;
			runlength.push_back(ele);
			runlength.push_back(len);
			length=0;
			num_elem=0;
			}

		template <class InputIterator>
			RLV(InputIterator first,InputIterator last){
				length=0;
				num_elem=0;
				vector<int> ele;
				vector<int> len;
				runlength.push_back(ele);
				runlength.push_back(len);
				for(InputIterator iter=first;iter!=last;iter++){
					length++;
					if(iter==first){
						num_elem++;
						runlength[0].push_back(*iter);
						runlength[1].push_back(1);
					}
					else if(*iter!=*(iter-1)){
						num_elem++;
						runlength[0].push_back(*iter);
						runlength[1].push_back(1);
					}
					else {
						runlength[1].back()++;
					}


				}	
			}
		pair<int,int> position(int pos);

		void insert(int pos,int value);

		void erase(int pos);

		void push_back(int value);
		
		int pop_back();

		int operator[](int pos);

		int size();
		
		void clear();

		int size_compressed();
};

ostream& operator<<(ostream& out,RLV a);
