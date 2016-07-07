class Unit
{
    double value,grad;
}

class addGate
{
    public:
    Unit x1,x2,y;
    addGate(double, double);
    double forward();
    double backward();
}

class multiplyGate
{
    public:
    Unit x1,x2,y;
    multiplyGate(double, double);
    double forward();
    double backward();
}
