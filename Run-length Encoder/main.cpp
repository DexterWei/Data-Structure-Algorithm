#include <iostream>
#include <vector>
#include <algorithm>
#include "RLV.h"

using namespace std;

int main(void) {
   RLV rlv;

   rlv.push_back(1);
   rlv.push_back(-2);
   rlv.push_back(3);
   cout << rlv << endl;

   rlv.pop_back();
   rlv.pop_back();
   cout << rlv << endl;
   rlv.pop_back();
   rlv.pop_back();
   cout << rlv << endl;

   int arr[5] = {0,1,-2,3,0};
   rlv=RLV(arr+1,arr+4);
   cout << rlv << endl;

   rlv.erase(1);
   rlv.insert(1,2);
   rlv.insert(3,4);
   cout << rlv << endl;

   rlv.clear();
   rlv.push_back(1);
   rlv.push_back(1);
   cout << rlv.size() << endl;
   cout << rlv.size_compressed() << endl;

   rlv.push_back(2);
   rlv.push_back(1);
   cout << rlv.size() << endl;
   cout << rlv.size_compressed() << endl;

   cout << rlv[0] << endl;
   cout << rlv[2] << endl;
   
   rlv.erase(2);
   cout << rlv.size() << endl;
   cout << rlv.size_compressed() << endl;

   return 0;
}


