#include <cstdlib>
#include <iostream>
#include <string>
#include <iomanip>
#include <thread>
#include <stdint.h>  //To make sure all ints are 4 bytes regardless of platform

using namespace std;

//Extern function for finding the sum of the array

//extern "C" void* findSum(void* args);
extern "C" void findSum(int32_t[], int32_t, int32_t, int32_t*); //Let the compiler know findSum is coming from an external source (an x86 program!)
void printInt(int32_t i) { cout << "Debug int: " << i << endl; }

//Important constants
const int DEFAULT_ARR_SIZE = 100;
const int DEFAULT_THREAD_COUNT = 2;

int main(int argc, char** argv)
{
    int i, threadCount, arrSize;
    int32_t elementsPerThread;
    int32_t* arr;

    if(argc > 3)
    {
        cout << "Error! Too many args!\n Usage = ./sum_prog_par <arr_size> <optional_thread_count>" << endl;
        return 1;
    }
    else if(argc == 1) //If no args, use default values
    {
        threadCount = DEFAULT_THREAD_COUNT;
        arrSize = DEFAULT_ARR_SIZE;
    }
    else if(argc == 2)
    {
        threadCount = DEFAULT_THREAD_COUNT;

        try{ arrSize = stoi(argv[1]); } //Else try to convert arg 1
        catch(...) {
            cout << "Invalid argument! " << argv[1] << " is not an integer for array size." << endl;
            return 1;
        }
    }
    else
    {
        try{ arrSize = stoi(argv[1]); } //Else try to convert arg 1
        catch(...) {
            cout << "Invalid argument! " << argv[1] << " is not an integer for array size." << endl;
            return 1;
        }
        try{ threadCount = stoi(argv[2]); } //Else try to convert arg 2
        catch(...) {
            cout << "Invalid argument! " << argv[2] << " is not an integer." << endl;
            return 1;
        }
    }
    elementsPerThread = arrSize / threadCount;

    //Start by creating the array in serial
    printf("Creating an array of size %i...\n", arrSize);
    cout << "{ 1, 2, ";
    arr = new int32_t[arrSize];
    arr[0] = 1;
    arr[1] = 2;
    for(i = 2; i < arrSize; i++)
    {
        arr[i] = 11*arr[i - 1]/20 + arr[i / 2];
        cout << arr[i] << ", ";
    }
    cout << " }" << endl;

    //Start all of the threads to find the sum
    printf("Starting %i threads...\n", threadCount);
    thread* threads = new thread[threadCount];
    int32_t* sums = new int[threadCount];
    for(i = 0; i < threadCount - 1; i++) //Set up all of the arguments and start the thread
    {
        cout << "Starting thread " << i << " on range [" << i*elementsPerThread << ", " << i*elementsPerThread + elementsPerThread << ")" << endl;
        threads[i] = thread(findSum, arr, i*elementsPerThread, elementsPerThread, &sums[i]);
    }
    cout << "Starting thread " << i << " on range [" << i*elementsPerThread << ", " << arrSize << ")" << endl;
    threads[i] = thread(findSum, arr, i*elementsPerThread, arrSize - i*elementsPerThread, &sums[i]); //Last thread might contain uneven number of elements compare to other ones

    //Join all of the threads with the main process
    for(i = 0; i < threadCount; i++)
    {
        threads[i].join();
        cout << "Thread " << i << " has joined!" << endl;
    }

    //Finally do the sum of all of the thread results in serial
    int sum = 0;
    for(i = 0; i < threadCount; i++)
    {
        cout << "Sum from thread " << i << " is " << sums[i] << endl;
        sum += sums[i];
    }
    
    cout << "The final sum is: " << sum << "\n";

    //Deallocate dynamic memory
    delete[] arr;
    delete[] threads;
    delete[] sums;

    return 0;
}
