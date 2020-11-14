#include <iostream>
#include <time.h>
#include <vector>
#ifndef COMMON
#define COMMON
#include "./common.cpp"
#endif
using namespace std;

vector<Box> solutionGlouton;
int solutionSize = 0;

int compareAire(const void *a, const void * b){
        return ( (*(Box *)b).d * (*(Box *)b).w ) - 
           ( (*(Box *)a).d * (*(Box *)a).w ); 
}

void sort(){
        qsort(rot, (NUMBER_OF_BLOCKS*3) ,sizeof(rot[0]), compareAire);
}

void addSolution(Box block, int indicator){
    if(indicator == 0){
        solutionGlouton.push_back(block);
        solutionSize = solutionSize + 1;
    }
    else if(block.w < solutionGlouton.at(solutionSize-1).w && block.d < solutionGlouton.at(solutionSize-1).d){
        solutionGlouton.push_back(block);
        solutionSize = solutionSize + 1;
    }
}


void CALCULATE(){
    sort();

    for (size_t i = 0; i < (NUMBER_OF_BLOCKS*3); i++)
    {
        srand ( time(NULL) );
        double randomNumber = rand() % (100 - 0 + 1) + 0;
        randomNumber = randomNumber/100;
        //cout << randomNumber << endl;

        double chances = static_cast<double>(rot[i].w)/static_cast<double>(rot[i].d);
        if(randomNumber <= chances){
            addSolution(rot[i], i);
        }
    }
}
    
int heightGlouton(){
    int height = 0;
    solutionGlouton.clear();
    solutionSize = 0;
    CALCULATE();
    for (size_t i = 0; i < solutionGlouton.size(); i++)
    {
        height += solutionGlouton.at(i).h;
    }
    // cout<<"FIN! hauteur:"<< height << endl;
    return(height);
}