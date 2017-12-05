#ifndef VECTOR_H
#define VECTOR_H
class Vector{
    public:
        double x,y;
        Vector(double inX, double inY);
        ~Vector();
        double getMag();
        void normalize();
        Vector operator+(Vector);
        Vector operator-(Vector);
        Vector operator*(double);
        double dotProduct(Vector);
        //Method to do the cross product giving the magnitude of the crossed vector
        double crossProduct(Vector);
        //Checking if two line segments cross 
        bool doLinesIntersect(Vector,Vector,Vector,Vector);
};
#endif
