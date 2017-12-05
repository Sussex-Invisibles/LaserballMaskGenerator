#define PI 3.14159265359
#include <stdio.h>
#include "MCSim.h"

int main(){
    MCSim simmer = MCSim();
    double * data1;
    double * data2;
    FILE * outputNew = fopen("DataNew.txt","w");
    FILE * outputOld = fopen("DataOld.txt","w");
    data1 = simmer.runMCNewNeck(1000000000);
    for(int i=0; i<1000; i++){
        fprintf(outputNew,"%f %f\n",(((double) i)/(1000/PI)),data1[i]);
    };
    fclose(outputNew);
    data2 = simmer.runMCOldNeck(1000000000);
    for(int i=0; i<1000; i++){
        fprintf(outputOld,"%f %f\n",(((double) i)/(1000/PI)),data2[i]);
    };
    fclose(outputOld);
    delete data1;
    delete data2;


    return 0;
};
