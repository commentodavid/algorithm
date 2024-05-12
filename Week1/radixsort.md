
## 기수 정렬 (Radix Sort)
기수 정렬은 숫자나 문자열 같은 데이터를 그 길이나 가능한 값의 범위가 크지 않은 경우 효과적으로 정렬할 수 있습니다. 이 방법은 데이터를 내부적으로 여러 키를 기준으로 여러 단계에 걸쳐 정렬합니다.

### 가장 효율적인 경우
- **데이터의 길이가 동일**하고, **각 자리수별로 범위가 제한적**인 경우 기수 정렬은 매우 빠릅니다.
- 예를 들어, 모든 전화번호는 10자리로 구성되어 있으며, 각 자리수는 0부터 9까지의 숫자입니다. 이런 경우 기수 정렬을 사용하면 효율적으로 정렬할 수 있습니다.

### 제한점
- 기수 정렬은 **자릿수가 많고, 범위가 넓어질수록** 정렬 과정에서 사용하는 **보조 메모리가 많아집니다**.
- 데이터 길이가 일정하지 않거나, 자릿수별 범위가 너무 넓다면 기수 정렬의 효율성이 떨어집니다.

### 복잡도
- 기수 정렬의 시간 복잡도는 \(O(d(n + k))\)이며, 여기서 \(d\)는 자릿수, \(n\)은 리스트의 길이, \(k\)는 자릿수의 범위입니다.

결론적으로, 각 정렬 방법은 특정 유형의 데이터와 환경에서 최적의 성능을 발휘합니다. 사용되는 데이터의 특성과 요구 사항을 고려하여 적절한 정렬 알고리즘을 선택하는 것이 중요합니다.

```cpp
#include <iostream>

// 배열에서 최댓값을 찾는 함수
int getMax(int arr[], int n) {
    int max = arr[0];
    for (int i = 1; i < n; i++) {
        if (arr[i] > max) {
            max = arr[i];
        }
    }
    return max;
}

// LSD 기수 정렬 함수
void radixSort(int arr[], int n) {
    // 최댓값을 찾음
    int maxVal = getMax(arr, n);

    // 각 자리수에 대해 countSort 수행
    for (int exp = 1; maxVal / exp > 0; exp *= 10) {
        int output[n]; // 정렬된 순서대로 저장할 배열
        int count[10] = {0}; // 각 숫자의 빈도를 저장할 배열

        // 각 숫자의 빈도 계산
        for (int i = 0; i < n; i++) {
            count[(arr[i] / exp) % 10]++;
        }

        // 각 숫자의 누적 빈도 계산
        for (int i = 1; i < 10; i++) {
            count[i] += count[i - 1];
        }

        // output 배열에 정렬된 숫자 배치
        for (int i = n - 1; i >= 0; i--) {
            output[count[(arr[i] / exp) % 10] - 1] = arr[i];
            count[(arr[i] / exp) % 10]--;
        }

        // arr 배열 업데이트
        for (int i = 0; i < n; i++) {
            arr[i] = output[i];
        }
        
        // 배열 변화 설명
        std::cout << "// After sorting for digit " << exp << ": ";
        for (int i = 0; i < n; i++) {
            std::cout << arr[i] << " ";
        }
        std::cout << std::endl;
    }
}

int main() {
    int data[] = {170, 45, 75, 90, 802, 24, 2, 66};
    int n = sizeof(data) / sizeof(data[0]);

    // 기수 정렬 호출
    radixSort(data, n);

    // 정렬된 배열 출력
    std::cout << "Sorted array: ";
    for (int i = 0; i < n; i++) {
        std::cout << data[i] << " ";
    }
    std::cout << std::endl;
    return 0;
}

```