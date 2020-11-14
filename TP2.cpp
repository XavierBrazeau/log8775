// A divide and conquer program in C++ to find the smallest distance from a 
// given set of points. 

#include <iostream>
#include <fstream> 
#include <float.h> 
#include <stdlib.h> 
#include <math.h>
#include <chrono>
#include <mach-o/dyld.h>
#include <vector>
#include <sstream>
#include <array>

#include "./dynamic.cpp"
#include "./taboo.cpp"
#include "./glouton.cpp"

#ifdef WINDOWS
#include <direct.h>
#define GetCurrentDir _getcwd
#else
#include <unistd.h>
#define GetCurrentDir getcwd
#endif

using namespace std; 

// const int INT_MAX = 2147483647;


string getCurrentDirectory(){

   char buff[1024]; //create string buffer to hold path
   GetCurrentDir( buff, FILENAME_MAX );
   string current_working_dir(buff);
   return current_working_dir;
        
}

void initializeBlocks(int fileNumber){
    
    string currentDirectory = getCurrentDirectory() + "/b" + to_string(NUMBER_OF_BLOCKS);
    
    string currentFile = currentDirectory + "_" + to_string(fileNumber) + ".txt";
    
    ifstream file;

    file.open(currentFile);
    if (!file) {
        cerr << "Unable to open file : " << currentFile << endl;
        exit(1);   // call system to stop
    }else {
        int x; 
        int y;
        int z;

        int blockNumber = 0;

        while (file >> x >> y >> z)
	    {

            Box tempBlock = {x , y, z}; 

            rot[blockNumber] = tempBlock;
            
            blockNumber++;
	    }

        file.close();
        return; 
    }


}

int main(int argc, char *argv[])
{   
  

    struct {
        std::string algo = "";
        std::string file_path = "";
        bool print_res = false;
        bool print_time = false;
    } prog_args;

    for (int i=1; i<argc; i++) {
        std::string arg(argv[i]);
        if (arg == "-a") {
            prog_args.algo = argv[i+1]; i++;
        } else if (arg == "-e") {
            prog_args.file_path = argv[i+1]; i++;
        } else if (arg == "-p") {
            prog_args.print_res = true;
        } else if (arg == "-t") {
            prog_args.print_time = true;
        }
    }
    initializeBlocks(2);

    auto start = high_resolution_clock::now(); 

    if(prog_args.algo == "taboo"){
        tabooSearch();
    }else if(prog_args.algo == "vorace"){
        heightGlouton();
    }else if(prog_args.algo == "progdyn"){
        maxStackHeight(NUMBER_OF_BLOCKS);
    }else {
        cout << "choix d'algorithme invalide" << endl;
        exit(1);
    }

    auto stop = high_resolution_clock::now(); 


    auto duration = duration_cast<microseconds>(stop - start);

    if(prog_args.print_time){
        cout << endl << duration.count() <<endl;
    }


    return 0;
}
