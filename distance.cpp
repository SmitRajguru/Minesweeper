#include<iostream.h>
#include<distance.h>
#include<math.h>
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
