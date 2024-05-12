#include <iostream>
#include <chrono>
#include <random>
#include <vector>
#include <iomanip> // 추가: 출력 폭을 조정하기 위해 필요

using namespace std;
using Clock = chrono::high_resolution_clock;

const int MAX_SIZE = 10000000;
int arr[MAX_SIZE];
vector<int> sizes = {1, 10, 100, 1000, 2000, 50000, 100000};

void generateAscending(int n) {
    for (int i = 0; i < n; ++i) {
        arr[i] = i + 1;
    }
}

void generateDescending(int n) {
    for (int i = 0; i < n; ++i) {
        arr[i] = n - i;
    }
}

void generateRandom(int n) {
    static mt19937 gen(Clock::now().time_since_epoch().count());
    uniform_int_distribution<> dis(1, n);
    for (int i = 0; i < n; ++i) {
        arr[i] = dis(gen);
    }
}

void insertionSort(int n) {
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

void merge(int left, int mid, int right) {
    int subOne = mid - left + 1;
    int subTwo = right - mid;
    vector<int> leftArray(arr + left, arr + mid + 1);
    vector<int> rightArray(arr + mid + 1, arr + right + 1);

    int i = 0, j = 0, k = left;

    while (i < subOne && j < subTwo) {
        arr[k++] = leftArray[i] <= rightArray[j] ? leftArray[i++] : rightArray[j++];
    }

    while (i < subOne) {
        arr[k++] = leftArray[i++];
    }
    while (j < subTwo) {
        arr[k++] = rightArray[j++];
    }
}

void mergeSort(int begin, int end) {
    if (begin < end) {
        int mid = begin + (end - begin) / 2;
        mergeSort(begin, mid);
        mergeSort(mid + 1, end);
        merge(begin, mid, end);
    }
}


void __mergesort(int size)
{
    mergeSort(0, size-1);
}

void measureSortTime(const string& sortName, int size, void(*sortFunction)(int)) {
    auto start = Clock::now();
    sortFunction(size);
    auto end = Clock::now();
    cout << left << setw(30) << sortName + " for size " + to_string(size) + ":" << right << setw(15)
         << chrono::duration_cast<chrono::nanoseconds>(end - start).count() << "ns" << endl;
}

void sortData(const string& description, void (*generate)(int), void(*sortFunction)(int), const string& sortName) {
    cout << sortName << " " << description << endl;
    for (int size : sizes) {
        generate(size);
        measureSortTime(sortName, size, sortFunction);
    }
}

int main() {
    sortData("오름차순 데이터로", generateAscending, insertionSort, "InsertionSort");
    sortData("오름차순 데이터로", generateAscending, __mergesort, "MergeSort");
    sortData("내림차순 데이터로", generateDescending, insertionSort, "InsertionSort");
    sortData("내림차순 데이터로", generateDescending, __mergesort, "MergeSort");
    sortData("무작위 데이터로", generateRandom, insertionSort, "InsertionSort");
    sortData("무작위 데이터로", generateRandom, __mergesort, "MergeSort");
    
    return 0;
}
