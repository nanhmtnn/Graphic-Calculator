#ifndef RANDOM_H
#define RANDOM_H

#include <random>

using namespace std;

int fastrand(int x) 
{ 
    return rand()%x;
} 

#endif //RANDOM_H