#include <iostream>
#include <thread>

void printNumbers(int N);

int main() {
    int N;

    std::cout << "Enter the value of N: ";
    std::cin >> N;

    std::thread numThread(printNumbers, N);

    numThread.join();

    return 0;
}

void printNumbers(int N) {
    for (int i = 1; i <= N; ++i) {
        std::cout << i << " ";
    }
    std::cout << std::endl;
}
