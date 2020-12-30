#include <iostream>
#include <vector>
#include <assert.h>
#include "tests.h"

using namespace std;

int main() {
	try{ 
		assert(twoSum() && "two sum failed"); 
		assert(twoSum_hash() && "two sum failed");

	}
	catch (const char* msg) {
		cerr << msg << endl;
	}
	
	return 0;
}