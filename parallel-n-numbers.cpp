#include <iostream>
#include <thread>
#include <vector>
#include <numeric> 
#include <ctime>

void processChunk(const int* array, int startIdx, int endIdx, int& partialSum) {
    partialSum = std::accumulate(array + startIdx, array + endIdx, 0);
}

int main() {
    srand(static_cast<unsigned int>(time(nullptr)));

    std::vector<int> sizes = {100, 500, 1000, 2000, 5000, 10000};

    for (int N : sizes) {
        int* myArray = new int[N];

        for (int i = 0; i < N; i++) {
            myArray[i] = rand() % 1000;
        }

        for (int numThreads = 1; numThreads <= 10; ++numThreads) {
            int chunkSize = N / numThreads;

            clock_t start = clock();

            std::vector<std::thread> threads;
            std::vector<int> partialSums(numThreads, 0);

            for (int i = 0; i < numThreads; ++i) {
                int startIdx = i * chunkSize;
                int endIdx = (i == numThreads - 1) ? N : (i + 1) * chunkSize;

                threads.emplace_back(processChunk, myArray, startIdx, endIdx, std::ref(partialSums[i]));
            }

            for (auto& thread : threads) {
                thread.join();
            }

            int totalSum = std::accumulate(partialSums.begin(), partialSums.end(), 0);

            clock_t end = clock();
            double elapsedTime = static_cast<double>(end - start) / CLOCKS_PER_SEC;
            std::cout << "Array Size: " << N << ", Number of Threads: " << numThreads << ", Elapsed Time: " << elapsedTime << " seconds, Total Sum: " << totalSum << std::endl;
        }

        delete[] myArray;
    }

    return 0;
}
