#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>

// Function to generate a random integer array of size N
std::vector<int> generateRandomArray(int N) {
    std::vector<int> arr;
    for (int i = 0; i < N; ++i) {
        arr.push_back(rand() % 1000);  // Generating random integers between 0 and 999
    }
    return arr;
}

// Function to search for a key in the array sequentially
bool searchSequential(const std::vector<int>& arr, int key) {
    for (int i = 0; i < arr.size(); ++i) {
        if (arr[i] == key) {
            return true;
        }
    }
    return false;
}

int main() {
    // Seed for random number generation
    srand(static_cast<unsigned>(time(0)));

    // Array sizes to test
    std::vector<int> sizes = {100, 500, 1000, 2000, 5000, 10000};

    for (int N : sizes) {
        std::vector<int> randomArray = generateRandomArray(N);

        int key = rand() % 1000;

        clock_t start = clock();

        bool found = searchSequential(randomArray, key);

        clock_t end = clock();
        double elapsedTime = static_cast<double>(end - start) / CLOCKS_PER_SEC;

        std::cout << "Array Size: " << N << ", Execution Time: " << elapsedTime << " seconds, Key Found: " << std::boolalpha << found << std::endl;
    }

    return 0;
}
