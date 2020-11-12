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
    initializeBlocks(2);

    for (int i = 0; i < NUMBER_OF_BLOCKS; i++){

        cout << rot[i].h << "  " << rot[i].w << "   " << rot[i].d << endl;

    }


    printf("The maximum possible height of stack is %d\n", 
         maxStackHeight (NUMBER_OF_BLOCKS) );

    return 0;
}
