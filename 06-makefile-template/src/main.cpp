#include <cstdio>
#include <iostream>

using namespace std;
int main()
{
    printf("Unused value test project started \n");
	bool testBool = true;
	if (testBool == false) {
        printf("Dead code here \n");   // TEST dead code
	}
	
    return 0;
}
