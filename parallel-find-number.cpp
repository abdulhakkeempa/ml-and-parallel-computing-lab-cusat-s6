#include <iostream>
#include <vector>
#include <thread>
#include <ctime>
#include <cstdlib>
#include <functional>

void printArray(double array[6][10], int n_row, int n_col){
    for(int a = 0; a < n_row; a++){
        for(int b = 0; b < n_col; b++){
          std::cout << array[a][b] << " ";
        }
        std::cout << std::endl;
      }   
}

std::vector<int> generateRandomArray(int N) {
    std::vector<int> arr;
    for (int i = 0; i < N; ++i) {
        arr.push_back(rand() % 1000);
    }
    return arr;
}

void searchInThread(const std::vector<int>& arr, int start, int end, int key, std::reference_wrapper<int> found) {
    for (int i = start; i <= end; ++i) {
        if (arr[i] == key) {
            found.get() = 1;
            break;
        }
    }
}

int main() {
    srand(static_cast<unsigned>(time(0)));
    std::vector<int> sizes = {100, 500, 1000, 2000, 5000, 10000};

    double size_thread_comparison [6][10];
    int size_thread_comparison_row_idx = 0;


    for (int N : sizes) {
        std::vector<int> randomArray = generateRandomArray(N);
        int key = rand() % 1000;
        std::cout << "Search Key: " << key << std::endl;

        for (int numThreads = 1; numThreads <= 10; ++numThreads) {
            int partitionSize = N / numThreads;
            clock_t start = clock();
            std::vector<std::thread> threads;
            std::vector<int> foundResults(numThreads, 0);

            for (int i = 0; i < numThreads; ++i) {
                int startIdx = i * partitionSize;
                int endIdx = (i == numThreads - 1) ? N - 1 : startIdx + partitionSize - 1;
                threads.emplace_back(searchInThread, std::ref(randomArray), startIdx, endIdx, key, std::ref(foundResults[i]));
            }

            for (auto& thread : threads) {
                thread.join();
            }

            int found = 0;
            for (const auto& result : foundResults) {
                found += result;
            }

            clock_t end = clock();
            double elapsedTime = static_cast<double>(end - start) / CLOCKS_PER_SEC;
            std::cout << "Array Size: " << N << ", Number of Threads: " << numThreads << ", Execution Time: " << elapsedTime << " seconds, Key Found: " << std::boolalpha << (found > 0) << std::endl;
            size_thread_comparison[size_thread_comparison_row_idx][numThreads-1] = elapsedTime;
        }
        size_thread_comparison_row_idx++;
    }

    printArray(size_thread_comparison, 6, 10);


    return 0;
}
