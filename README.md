# Threading
***Shoutout to Professor Samuel Black for creating this project. I thought learning about how threading works and a approach to parallelism is very fascinating to me!***

Overview:
Threading is one approach to parallelism. This project is about running code in parallel and observing the result. This project will also have linking across languages.
Both the g++ compiler and the yasm assembler generate object files from their respective source code. This means that we can take compiled C++ code and assembled x86 code
and put them together to make a single program. Linking involves resolving the addresses of functions from across or inside files.
The task of this project is to find the sum of an array of integers.

Each program takes optional command line arguments to customize parameters. 
The sequential version takes one argument, the number of elements for the array to contain. 
The parallel version takes two arguments: the number of elements for the array and the number of threads to execute with. 
If any parameters are left out, default values will be filled in.

Below are examples of how to run each program:
./sum_prog_seq 10 (Runs sequential version with 10 elements in the array)
./sum_prog_seq (Runs sequential version with default of 100 elements in the array)
./sum_prog_par (Runs parallel version with 100 elements and 2 threads, the default)
./sum_prog_par 400 (Runs parallel version with 400 elements in the array with 2 threads)
./sum_prog_par 100 5 (Runs parallel version on 100 elements in the array with 5 threads)

I have included my *writeup.txt* file to show the key results of each parallel version being ran 5 times.

Parallel programming should ideally speed up a program. From a theoretical approach, running our problem on arrays of the same size with n threads
should speed up the program by a factor of n. For example, having two threads should theoretically make the program twice as fast, while five threads should
make the program five times faster. However, in reality this is likely not the case and the results are probably much more tame. 

The speedup factor for a parallel program is defined as the proportion of how
much faster it ran compared to the sequential version:
            SpeedupFactor = Tseq/Tpar(n)
            
where T_seq is the time it took the program to run sequentially and Tpar(n) is the time it took for the program to run in parallel on n threads.

I have added a "sampleOutputThreading" to show the sum of the array from both threads
