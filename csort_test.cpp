// sorttest.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <chrono>
#include "csort.h"

void printArray(int* a, int count)
{
    std::cout << a[0];
    for (int i = 1; i < count; i++)
        std::cout << ", " << a[i];
    std::cout << std::endl;
}

void generatearray(int* a, int count) {
    for (int i = 0; i < count; i++) {
        a[i] = rand() % 100;        // # b/w 0 and 99
    }
}

void runsort(void(*f)(int*, int), std::string title, int n) {
    // generate array to sort
    int* a = new int[n];
    generatearray(a, n);

    // time the sort
    auto start = std::chrono::high_resolution_clock::now();
    f(a, n);   // perform sort
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start);

    // ensure sort is correct
    if (!csort::utils::is_sorted(a, n)) {
        std::cout << title << " is unsorted\n";
        printArray(a, n);
    }

    // output
    std::cout << title << " took " << duration.count() << " ns\n";
}

void run(int n) {
    runsort(&csort::sort::bubble, "Bubble", n);
    runsort(&csort::sort::counting, "Counting", n);
    runsort(&csort::sort::insertion, "Insertion", n);
    runsort(&csort::sort::quicksort, "Quicksort", n);
    runsort(&csort::sort::selection, "Selection", n);
}

int main(int argc, char** argv)
{
    // parse input arguments
    if (argc == 2) {        // user provided # of nums to sort
        int count = atoi(argv[1]);
        run(count);
    }
    else if (argc == 1) {
        std::cout << "warning: defaulting to 1000 terms\n";
        run(1000);
    }
    return 0;
}
