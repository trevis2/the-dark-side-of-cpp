#include <cstdio>
#include <iostream>

using namespace std;
int main(int argc, char** argv)
{
    printf("Unused value test project started \n");

	int var1;
	
	int var2 = 0;
	var2 = 1;
	
	int var3;
	var3 = 4;
	
	bool testBool = true;
	if (testBool == false) {
		printf("Dead code here \n");
	}
	
    return 0;
}
