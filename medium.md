# Medium 정렬 분석

관련 소스:

```text
src/sort/medium/medium_sort.c
src/sort/medium/medium_sort_divide.c
src/sort/medium/medium_sort_return.c
```

Medium 전략은 값 자체가 아니라 `sorted` 배열에서 얻은 rank와 chunk를 사용해 스택을 정렬한다.
전체 흐름은 다음과 같다.

```text
medium_sort
 ├─ 원소가 3개 이하이면 small_sort
 ├─ divide_by_chunks
 │   └─ A에서 대상 chunk를 찾아 B로 이동
 └─ return_to_a_by_chunk
     ├─ A에 남은 작은 부분을 정렬
     └─ B에서 큰 값부터 A로 반환
```

---

## 1. `medium_sort()`

파일: `src/sort/medium/medium_sort.c`

```c
int medium_sort(t_push_swap_stat *stat)
```

### 처리 순서

1. A의 현재 원소 수를 구한다.
2. 원소가 3개 이하이면 `small_sort()`에 맡긴다.
3. 원소가 4개 이상이면 `divide_by_chunks()`를 호출한다.
4. B에 모아 둔 원소를 `return_to_a_by_chunk()`로 반환한다.

현재 함수는 chunk 크기를 직접 계산하지 않는다. chunk 관련 계산은 `get_num_chunks()`와 `is_in_chunk()`에서 수행된다.

---

## 2. rank 계산

파일: `src/sort/medium/medium_sort.c`

### `get_rank()`

```c
int get_rank(int *sorted, int n, int val)
```

`sorted`는 main에서 merge sort된 배열이다.

예를 들어 입력이 다음과 같다면:

```text
A:       40 10 30 20
sorted:  10 20 30 40
```

각 값의 rank는 다음과 같다.

```text
10 → 0
20 → 1
30 → 2
40 → 3
```

`get_rank()`는 sorted 배열을 이진 탐색하므로 한 번의 rank 조회 비용은 `O(log n)`이다.

값을 찾지 못하면 `-1`을 반환한다. 정상적인 push_swap 입력에서는 중복과 범위 오류가 이미 검사되므로 일반적으로 실패하지 않는다는 전제를 갖는다.

---

## 3. chunk 개수 계산

### `get_num_chunks()`

```c
int get_num_chunks(int n)
```

계산 과정:

```text
chunk_size = floor(sqrt(n))
num_chunks = ceil(n / chunk_size)
```

단, `sqrt(n)` 결과가 0이면 chunk size를 1로 보정한다.

예시:

```text
n = 100
floor(sqrt(100)) = 10
num_chunks = ceil(100 / 10) = 10
```

```text
n = 10
floor(sqrt(10)) = 3
num_chunks = ceil(10 / 3) = 4
```

Medium의 chunk 인덱스는 0부터 시작한다.

---

## 4. chunk 판정

### `is_in_chunk()`

```c
int is_in_chunk(t_push_swap_stat *stat, int rank, int chunk_idx)
```

현재 A와 B의 원소 수를 합쳐 전체 크기 `n`을 계산한다.
그 후 chunk 개수와 실제 구간 폭을 계산한다.

```c
chunk_size = ceil(n / num_chunks)
```

일반 chunk의 범위는 다음과 같다.

```text
chunk 0: [0, chunk_size)
chunk 1: [chunk_size, 2 * chunk_size)
chunk 2: [2 * chunk_size, 3 * chunk_size)
...
```

마지막 chunk는 `n >= 6`일 때 다음 제한을 둔다.

```c
limit = n - 3;
```

즉 마지막 chunk에서는 rank가 `n - 3` 이상인 원소를 대상에서 제외한다.
이 원소들은 A에 남겨 `small_sort()`로 처리하려는 의도다.

다만 chunk 수를 계산할 때 사용한 `floor(sqrt(n))`과 실제 범위 폭을 계산할 때 사용하는 `ceil(n / num_chunks)`가 서로 다르다.
따라서 경계 rank가 어느 chunk에 속하는지 입력 크기별로 확인할 필요가 있다.

---

## 5. A에서 B로 분배

파일: `src/sort/medium/medium_sort_divide.c`

### `divide_by_chunks()`

```c
void divide_by_chunks(t_push_swap_stat *stat)
```

B는 처음에 비어 있으므로 A의 전체 크기로 chunk 개수를 계산한다.
그 다음 중앙의 두 chunk에서 시작해 양쪽 끝으로 확장하며 처리한다.

7개 chunk가 있다면 다음 순서다.

```text
(2, 3)
(1, 4)
(0, 5)
(6)
```

코드에서는 각 pair를 `inner_chunk`, `outer_chunk`로 전달한다.

```text
inner chunk = 2, outer chunk = 3
inner chunk = 1, outer chunk = 4
inner chunk = 0, outer chunk = 5
마지막 chunk = 6
```

chunk 개수가 홀수이면 중앙에서 확장한 뒤 마지막 chunk 하나가 남는다.
이 경우 마지막 chunk는 pair가 아니므로 `outer_chunk`를 `-1`로 전달한다.

각 chunk 쌍의 실제 이동은 `push_pair_to_b()`가 담당한다.

---

## 6. 대상 원소의 최적 회전 탐색

### `find_best_rotation_for_pair()`

현재 A에서 두 대상 chunk에 속한 원소를 찾고, top으로 가져오는 회전 수를 계산한다.

`match` 구조체의 의미:

```text
first : top부터 탐색했을 때 처음 발견한 대상 위치
last  : 마지막으로 발견한 대상 위치
cur   : 현재 확인 중인 원형 배열 index
i     : top 기준 논리 위치
size  : 현재 A의 크기
n     : A와 B를 합친 전체 원소 수
```

A를 top부터 순회하면서 rank를 구하고, 해당 rank가 두 chunk 중 하나에 속하는지 확인한다.

예시:

```text
A 논리 순서: [x, a, b, c, d]
              0  1  2  3  4  ← top으로부터의 위치
```

대상 원소가 위치 1과 4에 있다면:

```text
정방향 회전: 1번 → ra
역방향 회전: 1번 → rra
```

코드의 선택 기준은 다음과 같다.

```c
rot = first;
if (first > size - last)
    rot = -(size - last);
```

따라서:

- 정방향 거리가 더 짧거나 같으면 양수 회전
- 역방향 거리가 더 짧으면 음수 회전

양수는 `ra`, 음수는 `rra`를 의미한다.

---

## 7. chunk 원소를 B로 이동

### `push_pair_to_b()`

`find_best_rotation_for_pair()`가 찾은 회전값을 사용해 다음 순서로 동작한다.

```text
1. A에서 대상 원소를 top으로 회전
2. top 값을 확인
3. pb로 A에서 B로 이동
4. inner chunk 원소라면 B를 rb
```

의사 코드:

```text
while 대상 chunk 원소가 A에 남아 있음:
    A를 대상 원소까지 회전
    val = A의 top
    pb
    if val이 outer chunk가 아니고 outer chunk가 존재하면:
        rb
```

### B에서 inner chunk를 회전시키는 이유

inner chunk와 outer chunk를 같은 방식으로 B에 쌓으면 두 그룹의 위치가 섞인다.
inner chunk 원소를 `rb`로 한 번 더 회전시키면 B 안에서 두 그룹을 어느 정도 분리할 수 있다.

개념적으로는 다음과 같다.

```text
outer chunk 원소 → B의 top 쪽
inner chunk 원소 → rb로 뒤쪽으로 이동
```

이후 반환 단계에서 chunk별 최댓값을 찾기 쉬워진다.

### B의 실제 chunk 배치

스택 표기는 항상 `top → bottom` 순서로 작성한다.
`pb`는 새 원소를 B의 top에 넣고, `rb`는 B의 top 원소를 bottom으로 보낸다.

7개 chunk가 있고 각 chunk에서 대표 원소 하나만 이동한다고 가정하면 다음과 같다.

#### 1단계: `(2, 3)`

```text
pb chunk 2: [2]
rb chunk 2: [2]       // 원소가 하나라 위치 변화 없음
pb chunk 3: [3, 2]
```

#### 2단계: `(1, 4)`

```text
pb chunk 1: [1, 3, 2]
rb chunk 1: [3, 2, 1]
pb chunk 4: [4, 3, 2, 1]
```

#### 3단계: `(0, 5)`

```text
pb chunk 0: [0, 4, 3, 2, 1]
rb chunk 0: [4, 3, 2, 1, 0]
pb chunk 5: [5, 4, 3, 2, 1, 0]
```

#### 4단계: 마지막 chunk `6`

마지막 chunk는 pair가 아니므로 `outer_chunk == -1`이고 `rb`를 실행하지 않는다.

```text
pb chunk 6: [6, 5, 4, 3, 2, 1, 0]
```

따라서 최종적인 chunk 배치는 다음과 같다.

```text
B top
  chunk 6
  chunk 5
  chunk 4
  chunk 3
  chunk 2
  chunk 1
  chunk 0
B bottom
```

실제 입력에서는 각 chunk에 여러 값이 있으므로 chunk 내부의 개별 값까지 정렬되는 것은 아니다.
중요한 것은 낮은 번호의 inner chunk가 `rb`에 의해 B의 bottom 쪽으로 이동하고, 높은 번호의 outer chunk가 top 쪽에 남는다는 점이다.

이 배치는 다음 반환 순서와 연결된다.

```text
B에서 chunk 6의 최댓값부터 pa
→ chunk 5의 최댓값
→ chunk 4의 최댓값
→ ...
→ chunk 0의 최댓값
```

`find_max_chunk_idx()`는 B 전체를 순회하므로 chunk가 완벽하게 연속으로 모여 있지 않아도 동작하지만, 위와 같은 배치는 불필요한 B 회전을 줄이는 데 목적이 있다.

---

## 8. A에 남은 원소 처리

파일: `src/sort/medium/medium_sort_return.c`

### `return_to_a_by_chunk()` 시작 부분

전체 원소 수를 저장한 뒤 A에 남아 있는 원소에 대해 `small_sort()`를 호출한다.

```c
small_sort(stat, stat->stack_a, stat->stack_b,
    get_stack_size(stat->stack_a));
```

분배 과정에서 마지막 상위 원소 일부를 A에 남겨 두었기 때문이다.
A에 남은 부분은 먼저 오름차순으로 정렬한다.

그 다음 가장 큰 chunk부터 0번 chunk까지 역순으로 처리한다.

```text
target = num_chunks - 1
while target >= 0:
    target chunk의 원소가 B에 남아 있는 동안:
        target chunk의 최댓값을 찾아 A로 이동
    target--
```

---

## 9. B에서 chunk 최댓값 찾기

### `find_max_chunk_idx()`

B 전체를 순회하면서 다음 조건을 만족하는 원소를 찾는다.

```text
1. 현재 target chunk에 속해야 함
2. 현재까지 찾은 후보보다 값이 커야 함
```

반환값은 값 자체가 아니라 B의 top 기준 위치다.

```text
max_idx = 0
```

이면 현재 top이 최댓값이고,

```text
max_idx = 3
```

이면 top에서 세 번째 위치의 원소가 최댓값이다.

초기 후보가 없는 경우에는 `max_idx == -1`이다.
첫 번째 대상 원소를 무조건 후보로 인정하기 때문에 실제 값이 `INT_MIN`이어도 처리할 수 있다.

---

## 10. B의 최댓값을 top으로 이동

### `push_max_to_a()`

B에서 찾은 최댓값의 위치에 따라 회전 방향을 선택한다.

```c
if (max_idx <= size_b / 2)
    rb를 max_idx번
else
    rrb를 max_idx - size_b번
```

두 번째 경우의 회전값은 음수다.
예를 들어 B 크기가 8이고 최댓값 위치가 6이면:

```text
6번 rb보다 2번 rrb가 짧음
rot = 6 - 8 = -2
```

회전이 끝나면 `pa`로 B의 최댓값을 A top으로 이동한다.

```text
B에서 최댓값 선택
→ 짧은 방향으로 B 회전
→ pa
```

---

## 11. 전체 예시

원소가 10개라고 가정한다.

```text
n = 10
floor(sqrt(10)) = 3
num_chunks = 4
```

`divide_by_chunks()`는 중앙에서 바깥쪽으로 다음 순서로 chunk를 처리한다.

```text
1번 + 2번 chunk
0번 + 3번 chunk
```

각 쌍에 대해:

```text
A에서 대상 원소를 찾음
→ ra 또는 rra
→ pb
→ 필요하면 rb
```

분배가 끝난 뒤:

```text
A: 분배 과정에서 남은 일부 원소
B: chunk별로 분배된 원소
```

이후:

```text
A에 남은 원소를 small_sort
B의 마지막 chunk부터 최댓값을 pa
그 다음 chunk의 최댓값을 pa
...
0번 chunk까지 pa
```

결과적으로 A의 top에서 bottom 방향이 오름차순이 되고 B는 비게 된다.

---

## 12. 연산 기록 흐름

Medium의 모든 실제 연산은 다음 두 단계를 거친다.

```text
stack operation 실행
→ t_op 설정
→ store_op()
```

예:

```c
op = OP_PB;
push_stack(stat->stack_a, stat->stack_b, &op);
store_op(stat->op_buffer, op);
```

`store_op()`는 인접 명령을 다음처럼 최적화할 수 있다.

```text
ra + rb  → rr
rra + rrb → rrr
sa + sb  → ss
```

따라서 Medium 함수가 생성하는 실제 명령 수와 최종 출력 명령 수는 다를 수 있다.

---

## 13. Medium 전략의 핵심 요약

```text
1. rank 배열로 모든 값을 순서 번호로 바꾼다.
2. rank 범위를 여러 chunk로 나눈다.
3. A에서 현재 chunk 원소를 짧은 방향으로 회전한다.
4. pb로 B에 보낸다.
5. inner chunk 원소는 rb로 그룹을 분리한다.
6. A에 남은 원소를 small_sort한다.
7. B에서 큰 chunk부터 최댓값을 찾아 pa한다.
8. A에는 오름차순, B에는 아무 원소도 남지 않게 한다.
```

Medium의 핵심은 단순히 `√n`개씩 push하는 것이 아니라 다음 세 가지를 함께 사용하는 데 있다.

```text
rank 탐색
chunk 범위 판정
최단 회전 방향 선택
```
