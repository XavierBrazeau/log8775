#include <list>
#include <ctime>
#include <cstdlib>
#include <iostream>
#include <fstream> 
#include <chrono>


#ifdef WINDOWS
#include <direct.h>
#define GetCurrentDir _getcwd
#else
#include <unistd.h>
#define GetCurrentDir getcwd
#endif

#ifndef COMMON
#define COMMON
#include "./common.cpp"
#endif

using namespace std;
using namespace std::chrono;

//Box rot[] = {{5, 5, 5}};
list<Box> candidates;
list<Box> solution;
list<Box> solutionsStar;

list<pair<Box, int> > taboo;
list<pair<Box, int> > tempTaboo;

int iterations = 0;

int totalHeight = 0;

void printSolution()
{
    list<Box>::iterator newIt;
    for (newIt = solution.begin(); newIt != solution.end(); ++newIt)
    {
        cout << " Height : " << newIt->h << " Width : " << newIt->w << " Depth : " << newIt->d << endl;
    }
}




int generateRandomNumber(int min, int max)
{
    return rand() % (max - min + 1) + min;
}

void initializeTabooSearch()
{
    // Initializes all candidates
    candidates = list<Box>(begin(rot), end(rot));

    list<Box>::iterator it = candidates.begin();

    advance(it, 2);

    Box temp = *it;
    totalHeight = it->d;

    candidates.erase(it);

    solution.push_front(temp);

    // solution.insert(solution.begin(), (Box){4, 5, 4});
    
    // solution.insert(solution.begin(), (Box){6, 6, 6});
    // solution.insert(solution.begin(), (Box){8,8,8});
}

// STEP 1
list<Box>::iterator findCandidate()
{   
    // cout << "STEP ONE" << endl;
    list<Box>::iterator candidateIt;

    int maxHeight = -10000000;
    list<Box>::iterator candidateFound;

    for (candidateIt = candidates.begin(); candidateIt != candidates.end(); ++candidateIt)
    {
        int candidateWidth = candidateIt->w;
        int candidateDepth = candidateIt->d;

        int biggestBlockWidth = solution.begin()->w;
        int biggestBlockDepth = solution.begin()->d;

        if (candidateWidth > biggestBlockWidth && candidateDepth > biggestBlockDepth)
        {
            int tempHeight = totalHeight + candidateIt->h;
            if (tempHeight > maxHeight)
            {
                maxHeight = tempHeight;
                candidateFound = candidateIt;
            }
        }
        else
        {
            list<Box>::iterator solutionIt;
            for (solutionIt = solution.end(); solutionIt != solution.begin();)
            {   
                
                solutionIt--;
                
                int solutionWidth = solutionIt->w;
                int solutionDepth = solutionIt->d;

                if (candidateWidth < solutionWidth && candidateDepth < solutionDepth)
                {

                    // cout << "YEET" << endl;
                    int tempHeight = totalHeight;

                    tempHeight += candidateIt->h;
                    
                    for (solutionIt++; solutionIt != solution.end(); solutionIt++)
                    {
                        int newSolutionWidth = solutionIt->w;
                        int newSolutionDepth = solutionIt->d;

                        if (newSolutionWidth >= candidateWidth || newSolutionDepth >= candidateDepth)
                        {
                            tempHeight -= solutionIt->h;
                        }
                    }

                    if (tempHeight > maxHeight)
                    {

                        maxHeight = tempHeight;
                        
                        candidateFound = candidateIt;
                    }
                    break;
                }
            }
        }
    }
    return candidateFound;
}

// step 2 and 3
void insertCandidate(list<Box>::iterator candidate)
{
    // cout << "STEP TWO THREE" << endl;
    list<Box>::iterator solutionIt;

    int candidateWidth = candidate->w;
    int candidateDepth = candidate->d;

    int biggestBlockWidth = solution.begin()->w;
    int biggestBlockDepth = solution.begin()->d;

    if (candidateWidth > biggestBlockWidth && candidateDepth > biggestBlockDepth)
    {
        solution.insert(solution.begin(), *candidate);

        candidates.erase(candidate);
    }
    else
    {
        for (solutionIt = solution.end(); solutionIt != solution.begin();)
        {
            solutionIt--;
            int solutionWidth = solutionIt->w;
            int solutionDepth = solutionIt->d;

            if (candidateWidth < solutionWidth && candidateDepth < solutionDepth)
            {
                // cout << "INSERT" << endl;
                solution.insert(next(solutionIt), *candidate);

                candidates.erase(candidate);

                
                advance(solutionIt, 2);

                for (; solutionIt != solution.end(); solutionIt++)
                {
                    // cout << "Infinite loop ?" << endl;

                    //printSolution();
                    int newSolutionWidth = solutionIt->w;
                    int newSolutionDepth = solutionIt->d;

                    // cout << "DEPTH : " << newSolutionDepth << endl;
                    // cout << "WIDTH : " << newSolutionWidth << endl;


                    if (newSolutionWidth >= candidateWidth || newSolutionDepth >= candidateDepth)
                    {

                        pair<Box, int> tempPair (*solutionIt, generateRandomNumber(7, 10));
                        tempTaboo.push_back(tempPair);

                        // cout << "YEET" << endl;

                        solution.erase(solutionIt);
                        
                        





                    }
                }

                
                break;
            }
        }
    }
}

// step 4
void decrementTaboo(){
    // cout << "STEP FOUR" << endl;
    // devrement all elements
    list<pair<Box, int> >::iterator it = taboo.begin();
    for(; it != taboo.end(); it++){
        it->second = it->second - 1;

        if(it->second == 0){
            candidates.push_back(it->first);

            taboo.erase(it);
        }
    }

    // add all elements of tempTaboo
    list<pair<Box, int> >::iterator tempIt = tempTaboo.begin();
    for(; tempIt != tempTaboo.end(); tempIt++){
        taboo.push_back(*tempIt);
        tempTaboo.erase(tempIt);
    }
}

int calculateHeight(list<Box> listToCalculate){
    list<Box>::iterator it = listToCalculate.begin();  

    int height = 0;

    for(; it != listToCalculate.end(); ++it){
        height += it->h;
    }  

    return height;
}

// step 5
void copyS(){

    // cout << "STEP FIVE" << endl;
    int heightS = calculateHeight(solution);
    int heightStar = calculateHeight(solutionsStar);

    // cout << "HEIGHT : " << heightS <<  endl;
    // cout << "Height STAR : " << heightStar << endl;

    if(heightStar < heightS){
        // cout << "YES" << endl;
        solutionsStar = solution;
        iterations = 0;
    }
}

void printTaboo()
{
    list<pair<Box, int> >::iterator it;
    for (it = taboo.begin(); it != taboo.end(); ++it)
    {
        cout << " Height : " << it->first.h << " Width : " << it->first.w << " Depth : " << it->first.d << "TIMER : " << it->second << endl;

    }
}

void tabooSearch(){

    initializeTabooSearch();
    while(iterations != 100){
        // step 1



        totalHeight = calculateHeight(solution);
        list<Box>::iterator iter = findCandidate();

        // step 2 & 3
        insertCandidate(iter);

        //printTaboo();

        // step 4
        decrementTaboo();

        //setp 5

        copyS();

        // cout << iterations << endl;

        iterations++;
    }
}






void printCandidates()
{
    list<Box>::iterator it;
    for (it = candidates.begin(); it != candidates.end(); ++it)
    {
        cout << " Height : " << it->h << " Width : " << it->w << " Depth : " << it->d << endl;
    }
}



void printSolutionStar(){
    list<Box>::iterator newIt;
    for (newIt = solutionsStar.begin(); newIt != solutionsStar.end(); ++newIt)
    {
        cout << " Height : " << newIt->h << " Width : " << newIt->w << " Depth : " << newIt->d << endl;
    }
}

// int main(int argc, char *argv[])
// {

//     // candidates.insert(candidates.begin(), (Box){5, 5, 5});

//     // solution.insert(solution.begin(), (Box){5, 4, 5});
//     // solution.insert(solution.begin(), (Box){6, 6, 6});
//     // solution.insert(solution.begin(), (Box){8, 8, 8});

//     initializeBlocks(8);

//     high_resolution_clock::time_point t1 = high_resolution_clock::now();
//     tabooSearch();

//     high_resolution_clock::time_point t2 = high_resolution_clock::now();
//     duration<double> time_span = duration_cast<duration<double> >(t2 - t1);
    
//     std::cout << "It took me " << time_span.count() << " seconds.";
//     std::cout << std::endl;

//     cout << "HEIGHT  : " << calculateHeight(solutionsStar) << endl;
    


        
    






//     //Box firstCandidate = {}
//     // initializeTabooSearch();

//     // cout << "CANDIDATES : " << endl;

//     // printCandidates();

//     // cout << "SOLUTION : " << endl;

//     // printSolution();

//     // totalHeight = calculateHeight(solution);

//     // cout << "TOTAL HEIGHT : " << totalHeight << endl;

//     // list<Box>::iterator iter = findCandidate();

    

//     // cout << "CANDIDATE : "
//     //      << " Height : " << iter->h << " Width : " << iter->w << " Depth : " << iter->d << endl;

//     // insertCandidate(iter);

//     // cout << "Solution apres insertion : " << endl;

//     // printSolution();

//     // cout << "Candidats apres insertion : " << endl;

//     // printCandidates();

//     // decrementTaboo();

//     // printTaboo();

//     // copyS();

//     // printSolutionStar();

//     return 0;
// }