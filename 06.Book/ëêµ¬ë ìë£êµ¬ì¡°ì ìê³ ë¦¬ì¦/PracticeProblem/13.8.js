/**
 * 양수 배열이 주어졌을 때, 세 수의 가장 큰 곱을 반환하는 함수를 작성하라, 중첩 루프 3개를 쓰는 방식은 O(N^3) 시간이 걸리므로 비효율적이다.
 * 정렬을 사용하여 O(N log N)의 속도로 계산하도록 함수를 구현하자(더 빠르게 구현할 수 있으나 우선은 정렬을 사용해 코드를 더 빠르게 만드는 데 중점을 두자.
 */

function quickSort(arr) {
    if (arr.length <= 1) {
        return arr;
    }

    const pivot = arr[arr.length - 1];
    const left = [];
    const right = [];

    for (let i = 0; i < arr.length - 1; i++) {
        if (arr[i] < pivot) {
            left.push(arr[i]);
        } else {
            right.push(arr[i]);
        }
    }
    return [...quickSort(left), pivot, ...quickSort(right)];
}

function highestProductOf3(arr) {
    // 배열의 길이가 3보다 작으면 곱을 계산할 수 없음으로 예외 처리
    if (arr.length < 3) {
        throw new Error("배열의 최소 길이는 3 이상이어야 합니다.");
    }

    // 배열을 오름차순으로 정렬
    const sortedArray = quickSort(arr);

    // 가장 큰 세 수의 곱을 계산
    return sortedArray[sortedArray.length - 1] * sortedArray[sortedArray.length - 2] * sortedArray[sortedArray.length - 3];
}

// 테스트
console.log(highestProductOf3([1, 10, 2, 6, 5, 3])); // 10 * 6 * 5 = 300
console.log(highestProductOf3([4, 7, 2, 8, 1]));    // 8 * 7 * 4 = 224
console.log(highestProductOf3([5, 1, 3]));          // 5 * 3 * 1 = 15