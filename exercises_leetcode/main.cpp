#include <iostream>
#include <vector>
#include <assert.h>
#include "tests.h"
#include "solution.h"

using namespace std;

int main() {
	/*try{ 
		assert(twoSum() && "two sum failed"); 
		assert(twoSum_hash() && "two sum failed");

	}
	catch (const char* msg) {
		cerr << msg << endl;
	}*/
	Solution sol;
	cout << sol.getMaxRepetitions("aahumeaylnlfdxfircvscxggbwkfnqduxwfnfozvsrtkjprepggxrpnrvystmwcysyycqpevikeffmznimkkasvwsrenazkycxf"
		, 1000000, "aac", 10);
	return 0;
}


