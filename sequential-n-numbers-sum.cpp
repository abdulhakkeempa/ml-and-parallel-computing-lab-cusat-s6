#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

int sumArray(int *random_array, int N);

int main() {
    int N;
    cout << "N : ";
    cin >> N;

    int randomArray[N];

    srand(static_cast<unsigned int>(time(nullptr)));

    for (int i = 0; i < N; i++) {
        randomArray[i] = rand() % 100;
    }

    // Measure execution time
    clock_t start = clock();

    int sum = sumArray(randomArray, N);

    clock_t end = clock();
    double elapsedTime = static_cast<double>(end - start) / CLOCKS_PER_SEC;

    cout << "Sum: " << sum << endl;
    cout << "Execution Time: " << elapsedTime << " seconds" << endl;

    return 0;
}

int sumArray(int *random_array, int N) {
    int sum = 0;

    for (int i = 0; i < N; i++) {
        cout << random_array[i] << ", ";
        sum = sum + random_array[i];
    }

    return sum;
}
