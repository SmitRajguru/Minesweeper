#include<iostream.h>
#include<distance.h>

double d(int x1,int y1, int x2, int y2)
{
	return max(abs(x1-x2),abs(y1-y2));
}
