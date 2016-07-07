#include<iostream.h>
#include<distance.h>
#include<math.h>
double d(int x1,int y1, int x2, int y2)
{
	return max(abs(x1-x2),abs(y1-y2));
}
double gaussian(double a,double d)
{
	return exp(-1*pow((d/a),2));
}
double inverse(double a,double d)
{
	return (1/pow(d,a));
}
double step(double a,double d)
{
	if(d<a)
		return 1;
	else
		return 0;
}
