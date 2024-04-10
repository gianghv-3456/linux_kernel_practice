
#include <math.h>

double chuViTamGiac(double a, double b, double c){
	return a+b+c;
}

double dienTichTamGiac(double a, double b, double c){
	double p =(a+b+c)/2;
	return sqrt( p * (p-a) * (p-b) * (p-c));

}
