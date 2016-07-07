#include<iostream>
#include<objects.h>
using namespace std;

class Unit
{
    public:
    double value,grad;
}

multplyGate::multplyGate(double v1, double v2)
{
    x1.value=v1;
    x2.value=v2;
}

double multplyGate::forward()
{
    x1.value=v1;x2.value=v2;
    y.value=v1*v2;
    return y.value;
}

double multplyGate::backward()
{
    x1.grad += x2.val*y.grad;
    x2.grad += x1.val*y.grad;
}


addGate::addGate(double v1, double v2)
{
    x1.value=v1;
    x2.value=v2;
}

double addGate::forward()
{
    x1.value=v1;x2.value=v2;
    y.value=v1+v2;
    return y.value;    }

double addGate::backward()
{
    x1.grad += 1*y.grad;
    x2.grad += 1*y.grad;
}
