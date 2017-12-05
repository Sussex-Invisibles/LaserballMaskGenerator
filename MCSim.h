#include "Vector.h"
#include <random>


class MCSim{
    public:
        //Mersenne Twister random number generator 
        std::mt19937_64 g;
        std::uniform_real_distribution<double> dist; 
        MCSim();
        ~MCSim();
        //Random number between 0 and 1
        double randomDouble();
        Vector randomVector(double mag);
        Vector randomDirectionVector(Vector pos);
        double * runMCOldNeck(int numberOfEvents);
        double * runMCNewNeck(int numberOfEvents);

};

