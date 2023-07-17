//This version finds the sum of all of the values sequentially - no threads involved

#include <cstdlib>
#include <iostream>
#include <string>
#include <stdint.h>  //To make sure all ints are 4 bytes regardless of platform

using namespace std;

//Important constants
const int DEFAULT_ARR_SIZE = 100;

int main(int argc, char** argv)
{
    int i, arrSize;
    int32_t* arr;

    if(argc > 2)
    {
        printf("Error! Too many args!\n Usage = ./sum_prog_par <arr_size>\n");
        return 1;
    }
    else if(argc == 1) //If no args, use default value
        arrSize = DEFAULT_ARR_SIZE;
    else 
    {
        try{ arrSize = stoi(argv[1]); } //Else try to convert arg 1
        catch(...) {
            cout << "Invalid argument! " << argv[1] << " is not an integer for array size." << endl;
            return 1;
        }
    }

    //Start by creating the array in serial
    printf("Creating an array of size %i...\n", arrSize);
    printf("{ 1, 2, ");
    arr = new int32_t[arrSize];
    arr[0] = 1;
    arr[1] = 2;
    for(i = 2; i < arrSize; i++)
    {
        arr[i] = 11*arr[i - 1]/20 + arr[i / 2];
        printf("%i, ", arr[i]);
    }
    printf(" }\n");

    //Finally do the sum of all of the thread results in serial
    int sum = 0;
    for(i = 0; i < arrSize; i++)
        sum += arr[i];
    
    printf("The final sum is: %i\n", sum);

    delete[] arr;

    return 0;
}
