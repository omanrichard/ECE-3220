// L10_Ex2_References.cpp
#include <iostream>

using namespace std;

int main(){
    
    int i = 10;
    int &ri = i;	// reference
    int *k = &i;	// pointer
    
    // Notice that there is no need to specify the types when using cout.
    // Using printf(), we needed to specify the type using %d, %c, etc.
    
    cout << "1) i: " << i << ", ri: " << ri << ", *k: " << *k << ", k: " << k << endl;
    
    i = 15;
    cout << "2) i: " << i << ", ri: " << ri << ", *k: " << *k << ", k: " << k << endl;
    
    ri = 10;
    cout << "3) i: " << i << ", ri: " << ri << ", *k: " << *k << ", k: " << k << endl;
    
    int j = ri;
    cout << "4) i: " << i << ", ri: " << ri << ", j: " << j << ", *k: " <<  *k << ", k: " << k << endl;
    
    j = 50;
    cout << "5) i: " << i << ", ri: " << ri << ", j: " << j << ", *k: " <<  *k << ", k: " << k << endl;
    
    i = 20;
    cout << "6) i: " << i << ", ri: " << ri << ", j: " << j << ", *k: " <<  *k << ", k: " << k << endl;
    
    return 0;
}
