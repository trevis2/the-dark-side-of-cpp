#include "SampleClass.h"
#include <cmath>
#include <cstdlib>
#include <time.h>

SampleClass::SampleClass()
{
    srand(static_cast<unsigned int>(time(nullptr)));
    double valDouble = 2.01 * rand();
    double step = 2.01 * rand()/ valDouble;
    if (/*step == 0.0 ||*/ step < 0) {
        return;
    }
    int stepOrder = static_cast<int>(round(std::log10(static_cast<double>(step) * 1.0000001))); //UNDETECTED_ISSUE: log10 can have invalid input value 0
    printf("Step order %d\n", stepOrder);
    commonMethod(); // UNDETECTED_ISSUE: This Condition should raise an error since a virtual method has been invoked from constructor
}

SampleClass::~SampleClass()
{

}

void SampleClass::deadCodeDueToInvalidCheck() {
    int valueToCheck = rand();
    if (valueToCheck == 2) {
        printf("Do stuff\n");
    } else {
        if (valueToCheck != 2) {  // UNDETECTED_ISSUE: This condition should be detected always true and tool should suggest to delete it
             printf("Do other stuff\n");
        }
    }
}

// UNDETECTED_ISSUE: this method definition can be improved replacing std::string with const std::string &paramValue in order to avoid a new object creation if
// param value was not changed during method execution

void SampleClass::paramWithNoConstRef (std::string paramValue) {
    printf("%s \n", paramValue.c_str());
}

void SampleClass::commonMethod()
{
    printf("Do stuff\n");
}
