#include <iostream>
#include <vector>

using namespace std;

// 2D Peak Finder 문제: 주어진 2D 배열에서 "피크"를 찾는 문제입니다.
// 피크란 해당 위치의 값이 상하좌우보다 크거나 같은 지점을 말합니다.

// 2D 배열에서 최대값의 위치를 찾는 함수
int findMaxIndex(vector<vector<int>>& matrix, int col) {
    int max_index = 0;
    int max_val = matrix[0][col];

    // 주어진 열에서 최대값을 찾습니다.
    for (int i = 1; i < matrix.size(); ++i) {
        if (matrix[i][col] > max_val) {
            max_val = matrix[i][col];
            max_index = i;
        }
    }
    return max_index; // 최대값의 위치를 반환합니다.
}

// 2D Peak Finder 재귀 함수
int findPeak(vector<vector<int>>& matrix, int left, int right) {
    int mid = left + (right - left) / 2; // 중간 열 인덱스

    // 최대값 위치 찾기
    int max_index = findMaxIndex(matrix, mid);

    // 기저 사례: 피크를 찾았습니다.
    if ((mid == 0 || matrix[max_index][mid] >= matrix[max_index][mid - 1]) &&
        (mid == matrix[0].size() - 1 || matrix[max_index][mid] >= matrix[max_index][mid + 1])) {
        return matrix[max_index][mid]; // 피크의 값 반환
    }
    // 피크가 왼쪽에 있는 경우
    else if (mid > 0 && matrix[max_index][mid - 1] > matrix[max_index][mid]) {
        return findPeak(matrix, left, mid - 1); // 왼쪽 부분 배열에서 재귀 호출
    }
    // 피크가 오른쪽에 있는 경우
    else {
        return findPeak(matrix, mid + 1, right); // 오른쪽 부분 배열에서 재귀 호출
    }
}

// 2D Peak Finder 함수
int find2DPeak(vector<vector<int>>& matrix) {
    int left = 0;
    int right = matrix[0].size() - 1;
    return findPeak(matrix, left, right); // 피크를 찾는 재귀 함수 호출
}

int main() {
    vector<vector<int>> matrix = {
        {1, 3, 4, 5, 6},
        {2, 5, 3, 9, 8},
        {7, 8, 9, 10, 11},
        {12, 15, 14, 16, 13},
        {17, 20, 19, 18, 21}
    };

    int peak = find2DPeak(matrix);
    cout << "Peak: " << peak << endl;

    return 0;
}
