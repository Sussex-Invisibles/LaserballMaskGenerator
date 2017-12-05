#include <math.h>
#include "Vector.h"
#include <stdio.h>

Vector::Vector(double xIn, double yIn){
    x = xIn;
    y = yIn;
};

Vector::~Vector(){};

double Vector::getMag(){
    return sqrt((x*x)+(y*y));
};

void Vector::normalize(){
    double mag = getMag();
    x /= mag;
    y /= mag;

};

Vector Vector::operator+(Vector a){
    double newX = x+a.x;
    double newY = y+a.y;
    return Vector(newX,newY);
};

Vector Vector::operator-(Vector b){
    return (*this)+(b*-1.0);
};

Vector Vector::operator*(double d){
    return Vector(x*d,y*d);
};

double Vector::dotProduct(Vector a){
    return (x*a.x)+(y*a.y);
};
//Giving magnitude of cross product in 3rd direction
double Vector::crossProduct(Vector a){
    return x*a.y-y*a.x;
};

//Seeing if two lines intersect defined as a->b and c->d
//Explanation here http://stackoverflow.com/questions/563198/how-do-you-detect-where-two-line-segments-intersect
bool Vector::doLinesIntersect(Vector a,Vector b, Vector c, Vector d){
    double t = 1000;
    double u = 1000;
    Vector diffAB = b-a;
    Vector diffCD = d-c;
    Vector startDifference = c-a;
    double denom = diffAB.crossProduct(diffCD);
    if(denom == 0 ){
        return false;
    }
    //Getting intersection points
    else{
        t = startDifference.crossProduct(diffCD)/denom;
        u = startDifference.crossProduct(diffAB)/denom;
    }

    if(t>=0 && t<=1 && u>=0 && u<=1){
        return true;
    }

    else{
        return false;
    }
};

