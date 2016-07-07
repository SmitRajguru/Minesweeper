class Unit
{
    double value,grad;
}

class addGate
{
    public:
    Unit x1,x2,y;
    addGate();
    addGate(double, double);
    double forward();
    double backward();
}

class multiplyGate
{
    public:
    Unit x1,x2,y;
    multiplyGate();
    multiplyGate(double, double);
    double forward();
    double backward();
}

class distanceGate
{
    public:
    Unit x,a,y;
    distanceGate();
    distanceGate(double);
    double forward();
    double backward();
}
