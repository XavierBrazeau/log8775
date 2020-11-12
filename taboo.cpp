#include <list>
#include <ctime>
#include <cstdlib>
#include <iostream>

#ifndef COMMON
#define COMMON
#include "./common.cpp"
#endif

using namespace std;

Box rot[] = {{1,1,1},{2,2,2}, {3,3,3}, {4,4,4}, {5,5,5}};
list<Box> candidates;
list<Box> solution;
list<Box> solutionsStar;
list<Box> taboo;

int totalHeight = 0;

int generateRandomNumber(int min, int max){
    return rand()%(max-min + 1) + min;
}

void initializeTabooSearch(){
    // Initializes all candidates
    candidates = list<Box>(begin(rot), end(rot));

    int randomIndex = generateRandomNumber(0, candidates.size() - 1);

    list<Box>::iterator it = candidates.begin(); 

    advance(it, randomIndex);

    Box temp = *it;
    totalHeight = it->d;

    candidates.erase(it);

    solution.push_front(temp);

}

// STEP 1
list<Box>::iterator findCandidate(){
    list<Box>::iterator candidateIt;

    int maxHeight = 0;
    list<Box>::iterator candidateFound;

    for (candidateIt = candidates.begin(); candidateIt != candidates.end(); ++candidateIt){

        list<Box>::reverse_iterator solutionIt;
        for( solutionIt = solution.rbegin(); solutionIt != solution.rend(); solutionIt++){
            int candidateWidth = candidateIt->w;
            int candidateDepth = candidateIt->d;
            
            int solutionWidth = solutionIt->w;
            int solutionDepth = solutionIt->d;

            cout << "Candidate width : " << candidateWidth << endl;
            cout << "Candidate depth : " << candidateDepth << endl;

            cout << "Solution width : " << solutionWidth << endl;
            cout << "Solution depth : " << solutionDepth << endl;

            if(candidateWidth < solutionWidth && candidateDepth < solutionDepth){


                int tempHeight = totalHeight;
                tempHeight += candidateIt->h;


                list<Box>::reverse_iterator newSolutionIt = solutionIt;
                
                for(newSolutionIt; newSolutionIt != solution.rbegin(); --newSolutionIt){
                    int newSolutionWidth = newSolutionIt->w;
                    int newSolutionDepth = newSolutionIt->d;
                    
                    if(newSolutionWidth >= candidateWidth || newSolutionDepth >= candidateDepth){
                        tempHeight -= newSolutionIt->h;
                    }
                }

                // solutionIt = solution.rend();

                if(tempHeight > maxHeight){
                    maxHeight = tempHeight;
                    candidateFound = candidateIt;
                }
                break;
            }
        }
    }

    return candidateFound;
}


int main(int argc, char *argv[])
{   

    initializeTabooSearch();

    cout << "CANDIDATES : " << endl;

    list<Box>::iterator it;
    for (it = candidates.begin(); it != candidates.end(); ++it){
        cout << " Height : " << it->h << " Width : " << it->w << " Depth : " << it->d << endl;
    }

    cout << "SOLUTION : " << endl;

    list<Box>::iterator newIt;
    for (newIt = solution.begin(); newIt != solution.end(); ++newIt){
        cout << " Height : " << newIt->h << " Width : " << newIt->w << " Depth : " << newIt->d << endl;
    }

    cout << "TOTAL HEIGHT : " << totalHeight << endl;

    list<Box>::iterator iter = findCandidate();

    cout << "CANDIDATE : " << " Height : " << iter->h << " Width : " << iter->w << " Depth : " << iter->d << endl;

    return 0;
}

