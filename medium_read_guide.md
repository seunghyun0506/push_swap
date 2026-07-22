# Medium Sort 코드 읽기 가이드 (Read Guide)

`src/sort/medium` 코드를 효율적으로 분석하고 이해하기 위한 추천 읽기 순서 및 구조 설명 문서입니다.

---

## 1단계: 전체 흐름 파악 (`src/sort/medium/medium_sort.c` 상단)

- **`medium_sort(stat)`**
  - 전체 정렬 알고리즘의 진입점입니다.
  - 요소가 3개 이하이면 `small_sort`로 바로 처리하고, 4개 이상이면 **(1) 분할 단계(`divide_by_chunks`)** $\rightarrow$ **(2) 복귀 단계(`return_to_a_by_chunk`)**의 2단계 구조로 동작합니다.

---

## 2단계: 청크 개념 및 보조 기능 파악 (`src/sort/medium/medium_sort_utils.c`)

분할과 복귀 로직을 읽기 전에 아래 유틸 함수들이 어떤 역할을 하는지 먼저 파악하면 코드를 쉽게 이해할 수 있습니다.

1. **`get_num_chunks(n)`**
   - 전체 개수 $n$의 제곱근($\sqrt{n}$)을 기준으로 청크(그룹) 개수를 계산합니다.
2. **`is_in_chunk(stat, val, chunk_idx)`**
   - 어떤 값(`val`)이 몇 번째 청크 영역(구간)에 속하는지 확인합니다.
3. **`rotate_n(stat, s, rot)`**
   - 회전 수(`rot`)가 양수면 위로(`ra`/`rb`), 음수면 아래로(`rra`/`rrb`) 스택을 회전시키는 범용 함수입니다.

---

## 3단계: A $\rightarrow$ B 분할 알고리즘 분석 (`src/sort/medium/medium_sort.c`)

스택 A의 원소들을 청크 단위로 스택 B로 넘기는 과정입니다.

1. **`divide_by_chunks(stat)`**
   - 중앙 청크 쌍 `(left_chunk, right_chunk)`부터 시작하여 양 바깥쪽 청크 방향으로 이동하며 `push_pair_to_b`를 호출합니다.
2. **`find_best_rot(stat, c1, c2, rot)`**
   - 스택 A를 탐색하여 현재 대상 청크(`c1`, `c2`)에 속하는 원소 중 **가장 적은 회전(최소 비용)**으로 스택 상단에 올릴 수 있는 위치(`rot`)를 찾습니다.
3. **`push_pair_to_b(stat, c1, c2)`**
   - `find_best_rot`으로 찾은 최소 회전수만큼 A스택을 돌린 후 B스택으로 푸시(`pb`)합니다.
   - 이때 두 청크 중 한쪽에 속하는 원소는 `rb`를 수행하여 B스택 안에서도 구간을 구분합니다.

---

## 4단계: B $\rightarrow$ A 정렬 복귀 알고리즘 분석 (`src/sort/medium/medium_sort.c` & `medium_sort_utils.c`)

스택 B에 모인 원소들을 다시 A스택으로 정렬하며 되돌리는 과정입니다.

1. **`return_to_a_by_chunk(stat)`**
   - 가장 큰 청크 번호(마지막 청크)부터 0번 청크까지 역순으로 A스택에 복귀시킵니다.
2. **`find_max_chunk_idx(stat, chunk_idx)`** (`medium_sort_utils.c`)
   - B스택에서 현재 대상 청크에 속하는 원소들 중 **최댓값의 위치(인덱스)**를 찾습니다.
3. **`return_to_a_by_chunk` 내부 루프**
   - 최댓값을 B스택 상단으로 회전(`rotate_n`)시킨 후 A스택으로 푸시(`pa`)합니다.
   - 최댓값부터 순서대로 A스택으로 넘어가므로 A스택에는 최종적으로 오름차순 정렬이 완성됩니다.

---

## 💡 요약 구조도

```
medium_sort
├── 1. divide_by_chunks     (A -> B: 최소 회전 청크 푸시)
└── 2. return_to_a_by_chunk (B -> A: 청크별 최댓값 푸시)
```
