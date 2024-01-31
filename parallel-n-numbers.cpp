#include <iostream>
#include <thread>
#include <vector>
#include <numeric> 

const int arraySize = 1000;
const int numThreads = 10;
const int chunkSize = arraySize / numThreads;

void processChunk(const int* array, int startIdx, int endIdx, int& partialSum) {
    partialSum = std::accumulate(array + startIdx, array + endIdx, 0);
}

int main() {
    int myArray[arraySize];

    for (int i = 0; i < arraySize; ++i) {
        myArray[i] = i;
    }

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

    std::cout << "Total Sum: " << totalSum << std::endl;

    return 0;
}
