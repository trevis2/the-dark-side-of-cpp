#ifndef SAMPLE_CLASS_H
#define SAMPLE_CLASS_H
#include <iostream>

class BaseSampleClass {
    public:
        BaseSampleClass() {}
        virtual ~BaseSampleClass() = default;
        virtual void sampleMethod() {}
        virtual void commonMethod() = 0;
};

class SampleClass : public BaseSampleClass {
    public:
    SampleClass();
    ~SampleClass() override;
    void deadCodeDueToInvalidCheck();
    void paramWithNoConstRef(std::string paramValue);
    void commonMethod() override;
};

#endif //SAMPLE_CLASS_H
