#include <iostream>
#include <thread>
#include <vector>
#include <numeric> 
#include <ctime>

const int arraySize = 1000;
const int numThreads = 10;
const int chunkSize = arraySize / numThreads;

void processChunk(const int* array, int startIdx, int endIdx, int& partialSum) {
    partialSum = std::accumulate(array + startIdx, array + endIdx, 0);
}

int main() {
    int myArray[arraySize];

    srand(static_cast<unsigned int>(time(nullptr)));

    for (int i = 0; i < arraySize; i++) {
        myArray[i] = rand() % 1000;
    }
    
    // Measure execution time
    clock_t start = clock();

    
    std::vector<std::thread> threads;
    std::vector<int> partialSums(numThreads, 0);

    for (int i = 0; i < numThreads; ++i) {
        int startIdx = i * chunkSize;
        int endIdx = (i == numThreads - 1) ? arraySize : (i + 1) * chunkSize;

        threads.emplace_back(processChunk, myArray, startIdx, endIdx, std::ref(partialSums[i]));
    }

    for (auto& thread : threads) {
        thread.join();
    }

    int totalSum = std::accumulate(partialSums.begin(), partialSums.end(), 0);

    clock_t end = clock();
    double elapsedTime = static_cast<double>(end - start) / CLOCKS_PER_SEC;
    std::cout<<"Elapsed Time: "<<elapsedTime<<std::endl;
    
    std::cout << "Total Sum: " << totalSum << std::endl;

    return 0;
}
