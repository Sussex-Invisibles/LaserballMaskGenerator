#define PI 3.14159265359

#include "Vector.h"
#include "MCSim.h"
#include <random>
#include <stdlib.h>
#include <math.h>

MCSim::MCSim(){
    g.seed(50345794); 
    dist = std::uniform_real_distribution<double>(0.0, 1.0);
};

MCSim::~MCSim(){};

double MCSim::randomDouble(){
    return dist(g);
};

Vector MCSim::randomVector(double magnitude){
    double x = randomDouble()-randomDouble();
    double y = randomDouble()-randomDouble();
    double z = randomDouble()-randomDouble();
    if(x*x+y*y+z*z>1){
        return randomVector(magnitude);
    }
    Vector output = Vector(x,y);
    output.normalize();
    output = output*magnitude;
    return output;
};

Vector MCSim::randomDirectionVector(Vector position){
    //Generating cosine distributed angle
    double xMin = -PI/2.0;
    double xMax = PI/2.0;
    double a = 0.5 * ( xMin + xMax );
    double b = ( xMax - xMin ) /PI;
    double angle = a + b*asin(randomDouble()-randomDouble());
    //Emmited direction set with surface normal as y axis
    Vector emmited = Vector(sin(angle),cos(angle));
    //Performing rotation on emmited so it points in correct direction
    Vector normPos = position;
    normPos.normalize();
    double posAngle = atan2(normPos.y,normPos.x);
    posAngle = 2.5*PI-posAngle;
    if(posAngle>=2*PI){
        posAngle -= 2*PI;
    };
    //printf("Position Vector Angle to Y axis = %f\n",posAngle);
    //Need to rotate by negative of this angle to get back to original position
    double x = emmited.x*cos(-posAngle)-emmited.y*sin(-posAngle);
    double y = emmited.x*sin(-posAngle)+emmited.y*cos(-posAngle);
    emmited.x = x;
    emmited.y = y;
    return emmited;


};


double * MCSim::runMCOldNeck(int numberOfEvents){
    //Y vector for cos(theta)
    Vector unitY = Vector(0.0,1.0);
    //Creating the neck geometry as a set of linesA
    /* 
     *
     * Left Top       Right Top
     * |                 |
     * insideA           insideB      
     * |                 |
     * bottomA ------ bottomB
     */
    Vector insideA = Vector(-30,60.5);
    Vector insideB = Vector(30,60.5);
    Vector bottomA = Vector(-30,54.5);
    Vector bottomB = Vector(30,54.5);
    Vector leftTop = Vector(-30,250);
    Vector rightTop = Vector(30,250);
    //Creating the bins to store the various angles to the vertical 180 1 degree bins
    double * MCBins = new double[1000];
    double cosTheta;
    for(int i=0; i<numberOfEvents; i++ ){
        //Need to choose random position on the laserball surface 
        Vector position = randomVector(54.5);
        //Choosing random direction for photon to be emmitted in discarding if photon re enters laserball
        Vector direction = randomDirectionVector(position);
        //printf("Direction (%f,%f) Position(%f,%f)\n",direction.x,direction.y,position.x,position.y);
        //Checking if travelling in this direction causes the photon to re enter laserball if it does re doing run
        cosTheta = direction.dotProduct(unitY);
        //Now turning direction into a long vector to check whether it crosses neck
        direction = direction*300;
        //End points of line segments are (position,position+direction) direction now represents the end point of the line
        direction = direction+position;
        //Checking whether the ray crosses the neck
        bool leftCross = unitY.doLinesIntersect(position,direction,leftTop,bottomA);
        bool bottomCross = unitY.doLinesIntersect(position,direction,bottomB,bottomA);
        bool rightCross = unitY.doLinesIntersect(position,direction,rightTop,bottomB);
        bool insideCross = unitY.doLinesIntersect(position,direction,insideA,insideB);
        //If crosses any of the neck sides not adding to the array
        if(leftCross || rightCross  || bottomCross || insideCross){
            continue;
        }
        int binNum = (int) (1000/PI*(acos(cosTheta)));
        MCBins[binNum]++;
    }
    return MCBins;

};

double *  MCSim::runMCNewNeck(int numberOfEvents){
    //Y vector for cos(theta)
    Vector unitY = Vector(0.0,1.0);
    //Creating the neck geometry as a set of linesA
    /* 
     *
     * Left Top                                Right Top
     *    |                                        |
     *    |                                        |              
     * BottomG                                  bottomH
              \                                 /
               \                               /
                \                             / 
          bottomE--bottomC          bottomD--BottomF
                     |                    |
     *               |                    | 
     *                bottomA ------ bottomB
     */
    Vector bottomA = Vector(-9.5,54.5);
    Vector bottomB = Vector(9.5,54.5);
    Vector bottomC = Vector(-9.5,65);
    Vector bottomD = Vector(9.5,65);
    Vector bottomE = Vector(-14.5,65);
    Vector bottomF = Vector(14.5,65);
    Vector bottomG = Vector(-22.7,129.5);
    Vector bottomH = Vector(22.7,129.5);
    Vector leftTop = Vector(-22.7,250);
    Vector rightTop = Vector(22.7,250);
    //Creating the bins to store the various angles to the vertical 180 1 degree bins
    double * MCBins = new double[1000];
    double cosTheta;
    for(int i=0; i<numberOfEvents; i++ ){
        //Need to choose random position on the laserball surface 
        Vector position = randomVector(54.5);
        //Choosing random direction for photon to be emmitted in discarding if photon re enters laserball
        Vector direction = randomDirectionVector(position);
        //printf("Direction (%f,%f) Position(%f,%f)\n",direction.x,direction.y,position.x,position.y);
        //Getting angle between z axis of laserball and direction emitted
        cosTheta = direction.y;
        //Now turning direction into a long vector to check whether it crosses neck
        direction = direction*300;
        //End points of line segments are (position,position+direction) direction now represents the end point of the line
        //printf("Direction before x %f y %f Position before x %f y %f\n",direction.x,direction.y,position.x,position.y);
        direction = direction+position;
        //printf("Direction after x %f y %f Position before x %f y %f\n",direction.x,direction.y,position.x,position.y);
        //Checking whether the ray crosses the neck
        bool aToC = unitY.doLinesIntersect(position,direction,bottomC,bottomA);
        bool bToD = unitY.doLinesIntersect(position,direction,bottomB,bottomD);
        bool eToC = unitY.doLinesIntersect(position,direction,bottomE,bottomC);
        bool dToF = unitY.doLinesIntersect(position,direction,bottomD,bottomF);
        bool EToG = unitY.doLinesIntersect(position,direction,bottomE,bottomG);
        bool FToH = unitY.doLinesIntersect(position,direction,bottomF,bottomH);
        bool GToLeftTop = unitY.doLinesIntersect(position,direction,bottomG,leftTop);
        bool HToRightTop = unitY.doLinesIntersect(position,direction,bottomH,leftTop);
        bool aTob = unitY.doLinesIntersect(position,direction,bottomB,bottomA);
        //If crosses any of the neck sides not adding to the array
        if(aToC || bToD || eToC || dToF || EToG || FToH || GToLeftTop || HToRightTop || aTob  ){
            continue;
        }
        int binNum = (int) (1000/PI*(acos(cosTheta)));
        MCBins[binNum]++;
    }
    return MCBins;

};
