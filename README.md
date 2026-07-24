*This project has been created as part of the 42 curriculum by slim, jaeclee.*

# push_swap

## 목차

1. [Description](#1-description)
   1. [프로젝트 목표](#11-프로젝트-목표)
   2. [규칙과 허용 연산](#12-규칙과-허용-연산)
   3. [기여 내용](#13-기여-내용)
2. [자료구조와 실행 흐름](#2-자료구조와-실행-흐름)
   1. [원형 배열 스택](#21-원형-배열-스택)
   2. [프로그램 상태 구조체](#22-프로그램-상태-구조체)
   3. [정렬 배열과 임시 연결 리스트](#23-정렬-배열과-임시-연결-리스트)
   4. [연산 버퍼](#24-연산-버퍼)
   5. [main부터 종료까지의 호출 흐름](#25-main부터-종료까지의-호출-흐름)
3. [알고리즘과 복잡도](#3-알고리즘과-복잡도)
   1. [복잡도 기준](#31-복잡도-기준)
   2. [Disorder 측정](#32-disorder-측정)
   3. [소규모 정렬](#33-소규모-정렬)
   4. [Simple 전략 — O(n²)](#34-simple-전략)
   5. [Medium 전략 — O(n√n)](#35-medium-전략)
   6. [Complex 전략 — O(n log n)](#36-complex-전략)
   7. [Adaptive 전략](#37-adaptive-전략)
   8. [공통 연산 계층](#38-공통-연산-계층)
4. [Instructions](#4-instructions)
   1. [컴파일](#41-컴파일)
   2. [실행](#42-실행)
   3. [오류 처리](#43-오류-처리)
5. [Benchmark](#5-benchmark)
   1. [벤치마크 모드](#51-벤치마크-모드)
   2. [성능 기준](#52-성능-기준)
6. [Bonus: checker](#6-bonus-checker)
7. [Resources](#7-resources)
   1. [참고 자료](#71-참고-자료)
   2. [AI 사용 내역](#72-ai-사용-내역)

---

## 1. Description

### 1.1 프로젝트 목표

`push_swap`은 중복되지 않는 정수들을 두 스택 `a`, `b`와 제한된 명령만으로 오름차순 정렬하는 C 프로젝트이다. 입력의 첫 번째 정수가 스택 `a`의 top이며, 초기의 `b`는 비어 있다. 프로그램은 직접 정렬된 숫자를 출력하지 않고, `a`를 정렬하는 Push_swap 명령열을 표준 출력에 한 줄씩 기록한다.

이 구현은 다음 네 전략을 모두 포함한다.

- **Simple**: 원형 삽입 방식, `O(n²)`
- **Medium**: `√n` 규모의 chunk 방식, `O(n√n)`
- **Complex**: 두 pivot을 이용한 재귀적 3-way partition, `O(n log n)`
- **Adaptive**: 입력의 disorder에 따라 위 세 전략 중 하나를 선택

여기서 복잡도는 일반적인 배열 연산 시간이 아니라 **생성되는 Push_swap 명령 수**를 기준으로 한다.

### 1.2 규칙과 허용 연산

| 명령 | 동작 |
|---|---|
| `sa` | `a`의 top 두 원소를 교환한다. |
| `sb` | `b`의 top 두 원소를 교환한다. |
| `ss` | `sa`와 `sb`를 함께 수행한다. |
| `pa` | `b`의 top을 꺼내 `a`의 top에 넣는다. |
| `pb` | `a`의 top을 꺼내 `b`의 top에 넣는다. |
| `ra` | `a`를 위로 한 칸 회전하여 기존 top을 bottom으로 보낸다. |
| `rb` | `b`를 위로 한 칸 회전한다. |
| `rr` | `ra`와 `rb`를 함께 수행한다. |
| `rra` | `a`를 아래로 한 칸 회전하여 기존 bottom을 top으로 올린다. |
| `rrb` | `b`를 아래로 한 칸 회전한다. |
| `rrr` | `rra`와 `rrb`를 함께 수행한다. |

목표 상태는 `a`가 top부터 오름차순이고 `b`가 비어 있는 상태이다. 실행할 수 없는 단일 연산은 아무 동작도 하지 않는다.

### 1.3 기여 내용

- **slim**: 원형 배열 스택, 전체 실행 구조, Simple/Medium/Complex/Adaptive 정렬, 연산 버퍼, benchmark 및 bonus checker 구현
- **jaeclee**: Medium 전략 개선, 입력 파싱과 빌드 구조 보완, 전체 호출 흐름·오류 경로·정렬 동작 검토 및 문서화

두 구성원은 공동 검토를 통해 전체 알고리즘과 코드 흐름을 함께 이해하고 설명할 수 있도록 작업했다.

---

## 2. 자료구조와 실행 흐름

### 2.1 원형 배열 스택

```c
typedef struct s_stack
{
    int *datas;
    int capacity;
    int top_index;
    int bottom_index;
} t_stack;
```

스택은 연결 리스트가 아니라 `capacity + 1`칸의 **원형 배열(circular array)** 로 구현했다. 한 칸을 비워 둠으로써 두 인덱스가 같은 경우를 빈 스택으로 표현한다.

```text
size = (top_index - bottom_index + capacity + 1) % (capacity + 1)
```

논리적인 스택 순서는 `top_index`에서 시작하여 `prev_idx()`를 반복한 방향이다.

```text
stack top  -> datas[top_index]
              datas[prev_idx(top_index)]
              ...
stack bottom
```

#### 생성과 기본 접근

- `init_stack()`은 구조체와 `capacity + 1`개의 정수 배열을 할당한다.
- `push_stack_data()`는 `top_index`를 `next_idx()`로 이동한 뒤 값을 저장한다.
- `pop_stack_data()`는 top 값을 반환한 뒤 `top_index`를 `prev_idx()`로 이동한다.
- `get_stack_size()`, `get_stack_top()`, `is_stack_full()`은 현재 상태를 조회한다.
- `destroy_stack()`은 내부 배열과 구조체를 해제한다.

#### Push_swap 연산 구현

- `swap_stack()`은 top과 그다음 원소의 배열 값을 교환한다.
- `push_stack()`은 출발 스택에서 `pop_stack_data()`를 호출한 뒤 도착 스택에 `push_stack_data()`를 호출한다.
- `rotate_stack()`은 기존 top 값을 원형 배열의 새 bottom 위치로 옮기고 두 인덱스를 함께 감소시킨다.
- `rrotate_stack()`은 기존 bottom 값을 새 top 위치로 옮기고 두 인덱스를 함께 증가시킨다.
- `swap_stacks()`, `rotate_stacks()`, `rrotate_stacks()`는 두 스택에 대한 결합 연산을 담당한다.

따라서 회전할 때 모든 원소를 한 칸씩 복사하지 않으며, 각 스택 명령 자체는 `O(1)`에 처리된다.

### 2.2 프로그램 상태 구조체

`t_push_swap_stat`은 프로그램 전 구간에서 함께 사용되는 상태를 모은다.

| 필드 | 역할 |
|---|---|
| `argc`, `argv`, `i` | 원본 인자와 현재 파싱 위치 |
| `option` | 강제로 선택한 전략. `0`은 Adaptive이다. |
| `bench` | `--bench` 사용 여부 |
| `element_cnt` | 파싱된 전체 정수 개수 |
| `stack_a`, `stack_b` | 실제 정렬에 사용하는 두 스택 |
| `sorted` | 모든 입력값을 오름차순으로 보관한 rank 기준 배열 |
| `op_buffer` | 생성된 명령을 저장하고 축약하는 버퍼 |
| `initial_disorder` | 명령 수행 전 계산한 disorder |
| `selected_strategy` | 실제 실행된 내부 전략 |

`init_push_swap_stat()`은 각 필드를 초기화하고 `init_op_buffer()`를 호출한다. 이 구조체 하나를 파서, 정렬기, 출력기 사이에 전달하므로 전역 변수 없이 상태를 공유한다.

### 2.3 정렬 배열과 임시 연결 리스트

`parse_stack()`은 각 `argv`를 `parse_integers()`에 전달한다. 따라서 아래 두 입력 형식을 모두 처리할 수 있다.

```bash
./push_swap 4 2 1 3
./push_swap "4 2 1 3"
```

세부 호출은 다음과 같다.

```text
parse_stack
├─ parse_integers                 각 문자열에서 정수를 반복 추출
│  ├─ str_to_int                  부호, 숫자 유무, int 범위 검사
│  │  ├─ get_sign
│  │  ├─ get_limit
│  │  └─ parse_digits
│  └─ add_node                    읽은 값을 임시 연결 리스트 앞에 추가
├─ init_stack                     a와 b 할당
└─ list_to_stack                  리스트를 a와 sorted 배열로 변환
```

`add_node()`가 값을 리스트 앞에 넣기 때문에 임시 리스트는 입력의 역순이다. `list_to_stack()`은 리스트 앞에서부터 값을 다시 stack에 push하고 `sorted`는 뒤 인덱스부터 채운다. 두 번의 역전 결과로 `a`의 top부터 원래 입력 순서가 복원된다. 사용한 임시 노드는 변환 즉시 해제한다.

그 후 `merge_sort()`가 `sorted`를 오름차순 정렬한다. `merge_sort_helper()`가 배열을 재귀적으로 나누고 `merge()`가 임시 배열에 병합하며, `copy_array()`가 병합 결과를 되돌려 쓴다. 이 배열은 다음 두 작업의 공통 기준이다.

1. 인접 값 비교를 통한 중복 검사
2. 값의 상대 순위와 pivot/chunk 경계 검색

### 2.4 연산 버퍼

```c
typedef struct s_op_buffer
{
    t_op *arr;
    int idx;
    int capacity;
    int err;
} t_op_buffer;
```

정렬 함수는 명령을 즉시 출력하지 않는다. `OP_SA`, `OP_PB`, `OP_RA`와 같은 `t_op` enum 값을 동적 배열에 저장한다. 초기 용량은 32이며, 공간이 부족하면 `resize()`가 두 배 크기의 배열을 할당한다.

`store_op()`은 새 연산과 버퍼의 마지막 연산을 비교하여 다음과 같이 불필요한 명령을 제거하거나 결합한다.

```text
ra + rra  -> 제거       sa + sa -> 제거
rb + rrb  -> 제거       pa + pb -> 제거
ra + rb   -> rr         rra + rrb -> rrr
sa + sb   -> ss
```

결합 결과가 다시 직전 명령과 축약될 수 있으므로 더 이상 변환되지 않을 때까지 반복한다. 모든 정렬이 끝나면 `print_op_buffer()`가 enum을 실제 명령 문자열로 바꾸어 표준 출력에 기록한다. 이 구조는 명령 수 집계와 `--bench` 출력에도 그대로 사용된다.

### 2.5 main부터 종료까지의 호출 흐름

```text
main
├─ 인자가 없으면 출력 없이 종료
├─ init_push_swap_stat
│  └─ init_op_buffer
├─ parse_flag
├─ parse_stack
│  ├─ parse_integers -> str_to_int -> add_node
│  ├─ init_stack(a), init_stack(b)
│  └─ list_to_stack
├─ merge_sort(sorted)
├─ check_duplicate
├─ sort
│  ├─ small_sort                         n <= 3
│  ├─ compute_disorder                   n > 3
│  └─ simple_sort / medium_sort / complex_sort
├─ print_op_buffer                       stdout
├─ print_bench_info                      --bench일 때 stderr
└─ free_resources
   ├─ free_op_buffer
   ├─ destroy_stack(a), destroy_stack(b)
   └─ free(sorted)
```

#### 1) 상태와 옵션 준비

`init_push_swap_stat()`이 모든 포인터와 옵션을 초기화한다. `parse_flag()`는 숫자보다 앞에 있는 `--simple`, `--medium`, `--complex`, `--adaptive`, `--bench`를 읽는다. 전략 선택자를 둘 이상 지정하거나 `--bench`를 중복 지정하면 실패한다.

#### 2) 입력 생성과 검증

`parse_stack()`이 입력을 두 스택과 `sorted` 배열로 변환하고, `merge_sort()`가 기준 배열을 정렬한다. `check_duplicate()`는 정렬 배열의 인접 원소가 같은지 확인한다. 숫자가 아니거나 `int` 범위를 벗어나거나 중복된 값이 있으면 `Error\n`을 표준 에러에 출력한다.

#### 3) 전략 선택과 정렬

`sort()`는 3개 이하의 입력을 `small_sort()`로 처리한다. 그보다 큰 입력은 `compute_disorder()`로 초기 상태를 측정한 뒤 강제 옵션 또는 Adaptive 기준에 따라 한 전략을 호출한다. 각 전략은 실제 스택을 변경하면서 수행한 명령을 연산 버퍼에 기록한다.

#### 4) 출력과 해제

버퍼 오류가 없으면 `print_op_buffer()`가 명령열만 stdout에 출력한다. `--bench`가 활성화된 경우 `print_bench_info()`가 별도의 통계를 stderr에 출력한다. 마지막에는 성공과 실패 경로 모두 `free_resources()`를 통해 할당 자원을 정리한다.

---

## 3. 알고리즘과 복잡도

### 3.1 복잡도 기준

이 프로젝트에서 `O(n²)`, `O(n√n)`, `O(n log n)`은 C 코드의 비교 횟수가 아니라 **정렬을 위해 생성한 `sa`, `pb`, `ra` 등의 명령 수**에 대한 상한이다.

예를 들어 `binary_search()`나 pivot을 찾기 위한 배열 조회는 C 실행 시간에는 포함되지만 Push_swap 명령을 만들지 않는다. 반대로 원소 하나를 원하는 위치까지 회전시키면 회전 횟수만큼 명령 수가 증가한다.

`n`을 입력 원소 수, `m`을 최종 연산 수라고 할 때 공통 메모리는 두 스택과 `sorted` 배열에 `O(n)`, 연산 버퍼에 `O(m)`을 사용한다.

### 3.2 Disorder 측정

Disorder는 입력이 오름차순에서 얼마나 벗어났는지를 `0`부터 `1` 사이 값으로 나타낸다. stack `a`에서 앞에 있는 값이 뒤의 값보다 큰 모든 inversion을 센다.

```text
disorder = inversion 수 / 전체 쌍의 수
total_pairs = n × (n - 1) / 2
```

- 이미 오름차순이면 `0.0`
- 완전한 내림차순이면 `1.0`
- 일부 순서만 뒤집혀 있으면 그 사이의 값

`compute_disorder()`는 `top_index`부터 `prev_idx()` 방향으로 모든 `(i, j), i < j`를 비교한다. 측정 자체의 C 시간 복잡도는 `O(n²)`, 추가 공간은 `O(1)`이며 Push_swap 명령은 만들지 않는다.

### 3.3 소규모 정렬

이 정렬은 전체 입력이 3개 이하일 때와 Complex 재귀의 종료 조건에서 공통으로 사용된다.

#### `small_sort()` — `a` 쪽 오름차순 구간

- 크기 0 또는 1: 이미 정렬된 상태이다.
- 크기 2: top 두 값이 역순이면 `op_swap()`을 수행한다.
- 크기 3: `three_sort_asc()`를 호출한다.

`three_sort_asc()`는 top, middle, bottom의 상대 순서를 여섯 순열로 구분한다. 이미 정렬된 경우를 제외하고 `swap`과 보조 스택으로의 임시 `push` 조합을 사용해 해당 세 원소를 오름차순으로 만든다.

#### `small_sort_helper()` — `b` 쪽 내림차순 구간

Complex 재귀 중 `b`에 있는 구간은 큰 값부터 `a`로 돌아와야 한다.

- 크기 1: 바로 `a`로 push한다.
- 크기 2: `b`의 두 값을 내림차순으로 맞춘 뒤 두 번 push한다.
- 크기 3: `three_sort_desc()`가 `b`를 확인하며 세 값을 `a`로 옮기고, 마지막에 `three_sort_asc()`로 `a`의 해당 구간을 정리한다.

구간 크기가 최대 3이므로 생성 연산 수와 추가 공간은 모두 `O(1)`이다.

### 3.4 Simple 전략

Simple은 **원형으로 정렬된 `a`에 `b`의 값을 하나씩 삽입**하는 baseline 전략이다.

```text
simple_sort
├─ move_to_b
├─ insert_to_a
│  ├─ get_insert_pos_a
│  │  ├─ get_min_idx
│  │  └─ search_insert_pos
│  ├─ rotate_n
│  └─ op_push (pa)
└─ align_stack_a
   ├─ find_min_idx_stack
   └─ rotate_n
```

#### 1) `move_to_b()`

`a`에 기준 원소 하나만 남을 때까지 `pb`를 수행한다. 이 단계는 최대 `n - 1`개 명령을 만든다.

#### 2) `get_insert_pos_a()`

현재 `a`는 최솟값 경계에서 한 번 끊어진 원형 오름차순 상태를 유지한다.

- `get_min_idx()`가 한 번의 순회로 최솟값, 최댓값, 최솟값 위치를 구한다.
- 삽입값이 현재 범위 밖이면 최솟값 위치가 새 경계가 된다.
- 범위 안이면 `search_insert_pos()`가 `prev_val < val < current_val`을 만족하는 위치를 찾는다.

#### 3) `insert_to_a()`

찾은 위치가 top 쪽에 가까우면 `ra`, bottom 쪽에 가까우면 `rra`를 선택한다. `rotate_n()`이 필요한 횟수만큼 회전한 뒤 `pa`로 값을 삽입한다. 이 과정을 `b`가 빌 때까지 반복한다.

#### 4) `align_stack_a()`

원형 오름차순 상태의 최솟값 위치를 `find_min_idx_stack()`으로 찾고, 더 가까운 회전 방향을 이용해 최솟값을 top에 둔다.

#### 선택 이유와 복잡도

구조가 단순하고 삽입 위치가 명확하여 baseline으로 적합하다. 각 원소를 삽입할 때 `a`를 최대 `O(n)`회 회전하고 이를 `O(n)`개 원소에 반복하므로 생성 연산 수는 `O(n²)`이다. 정렬 로직 자체의 추가 공간은 `O(1)`이며, 전체 프로그램과 연산 버퍼까지 포함하면 `O(n + m) = O(n²)`이다.

### 3.5 Medium 전략

Medium은 정렬된 rank를 약 `√n` 크기의 chunk로 묶는 **range-based chunk 전략**이다.

```text
medium_sort
├─ divide_by_chunks
│  └─ push_pair_to_b
│     ├─ get_chunk_cnt
│     ├─ is_in_chunk
│     │  ├─ get_num_chunks
│     │  └─ binary_search
│     ├─ op_push (pb)
│     └─ op_rotate (ra 또는 rb)
└─ selection_sort_to_b
   ├─ find_max_idx_stack
   ├─ rotate_n (rb 또는 rrb)
   └─ op_push (pa)
```

#### 1) rank와 chunk 구성

`sorted`에서의 인덱스를 값의 rank로 사용한다. `get_num_chunks()`는 약 `√n`개의 chunk가 생기도록 개수를 계산하고, `is_in_chunk()`는 `binary_search()`로 값의 rank를 찾은 뒤 해당 범위에 속하는지 판정한다.

#### 2) `divide_by_chunks()`

중앙의 두 chunk에서 시작하여 바깥쪽 chunk 쌍으로 이동한다.

```text
chunk:  0  1  2  3  4  5
순서:        [2,3] -> [1,4] -> [0,5]
```

`push_pair_to_b()`는 현재 쌍에 속한 원소 수만큼 `a`를 탐색한다.

- 오른쪽의 큰 rank chunk: `pb`로 `b`의 top 쪽에 둔다.
- 왼쪽의 작은 rank chunk: `pb` 후 `rb`를 수행하여 `b`의 bottom 쪽에 둔다.
- 현재 쌍에 속하지 않는 값: `ra`로 넘긴다.

이 배치는 큰 chunk가 top 쪽, 작은 chunk가 bottom 쪽에 모이도록 하여 반환 회전을 제한한다.

#### 3) `selection_sort_to_b()`

`find_max_idx_stack()`으로 `b`의 현재 최댓값 위치를 찾는다. top에 가까우면 `rb`, bottom에 가까우면 `rrb`로 올린 뒤 `pa`한다. 큰 값부터 `a`로 보내므로 최종 `a`는 작은 값이 top에 오는 오름차순이 된다.

#### 선택 이유와 복잡도

모든 값을 개별 삽입하는 Simple보다 이동 범위를 줄이면서, Complex보다 재귀와 partition 관리 비용이 작다. 약 `√n`개의 chunk를 처리하며 각 원소는 소속 chunk를 찾는 동안 최악 `O(√n)` 범위의 회전에 참여한다. 반환 시에도 chunk 내부 탐색과 회전이 원소당 `O(√n)`으로 제한된다. 따라서 생성 연산 수의 상한은 `O(n√n)`이다. 정렬 로직의 추가 공간은 `O(1)`이고 공통 `sorted` 배열은 `O(n)`이다. 연산 버퍼까지 포함한 전체 공간 상한은 `O(n√n)`이다.

### 3.6 Complex 전략

Complex는 두 pivot으로 현재 구간을 세 부분으로 나누고 `a`와 `b` 사이에서 상호 재귀하는 **3-way partition 전략**이다.

```text
complex_sort
└─ complex_sort_helper_a
   ├─ small_sort                         size <= 3
   ├─ partition_asc
   │  └─ find_pivot
   ├─ rewind_stack
   ├─ complex_sort_helper_a
   └─ complex_sort_helper_b
      ├─ small_sort_helper               size <= 3
      ├─ partition_desc
      │  └─ find_pivot
      ├─ complex_sort_helper_a
      ├─ rewind_stack
      └─ complex_sort_helper_a / helper_b
```

#### 1) `find_pivot()`

현재 처리할 구간의 최솟값과 최댓값을 찾고 `binary_search()`로 두 값의 전체 rank를 구한다. 그 rank 구간의 약 `1/3`, `2/3` 지점 값을 두 pivot으로 선택한다. 실제 데이터에서 가져온 pivot이므로 세 partition의 크기가 가능한 한 균형을 이루게 된다.

#### 2) `partition_asc()` — `a` 구간 분할

`a`에서 오름차순으로 완성할 구간을 세 그룹으로 나눈다.

- 높은 그룹: `a`에 남기고 rotate
- 중간 그룹: `b`로 push한 뒤 `b`를 rotate
- 낮은 그룹: `b`로 push

`t_part.cnt`는 높은 그룹 수, 중간 그룹 수, `b`로 이동한 전체 수를 보존하여 뒤의 재귀 크기와 rewind 횟수로 사용한다.

#### 3) `partition_desc()` — `b` 구간 분할

`b`에 있는 구간은 반대 방향으로 나눈다.

- 낮은 그룹: `b`에 남기고 rotate
- 중간 그룹: `a`로 push한 뒤 `a`를 rotate
- 높은 그룹: `a`로 push

이 대칭 구조 덕분에 `complex_sort_helper_a()`와 `complex_sort_helper_b()`가 각자 올바른 스택에 구간을 배치하면서 재귀할 수 있다.

#### 4) `rewind_stack()`

partition 도중 사용한 rotate는 현재 구간 아래에 있던 원소의 상대 위치에 영향을 줄 수 있다. `rewind_stack()`은 기록된 횟수만큼 reverse rotate를 수행해 구간 경계를 복구한다. 두 스택을 동시에 되돌릴 수 있으면 `rrr`를 사용하고, 남은 횟수만 각각 `rra` 또는 `rrb`로 처리한다.

#### 5) 상호 재귀와 종료

`complex_sort_helper_a()`는 `a`의 구간을 오름차순으로 만들고, `complex_sort_helper_b()`는 `b`의 구간을 필요한 순서로 `a`에 반환한다. 각 helper는 세 partition의 크기를 이용해 다시 두 helper를 호출한다. 크기가 3 이하가 되면 `small_sort()` 또는 `small_sort_helper()`가 직접 정렬하여 재귀를 끝낸다.

#### 선택 이유와 복잡도

세 부분으로 균형 있게 나누면 재귀 깊이는 `O(log n)`이다. 각 깊이에서 모든 원소가 상수 횟수의 push/rotate/reverse rotate에 참여하므로 레벨당 `O(n)`, 전체 생성 연산 수는 `O(n log n)`이다. 재귀 호출 스택은 `O(log n)`, 공통 배열은 `O(n)`이며, 연산 버퍼를 포함한 전체 공간 상한은 `O(n log n)`이다.

### 3.7 Adaptive 전략

별도 정렬기를 하나 더 구현하는 대신, 명령을 수행하기 전에 측정한 disorder에 따라 내부 전략을 선택한다.

| Disorder 범위 | 선택 전략 | 명령 복잡도 |
|---|---|---|
| `disorder < 0.2` | Simple | `O(n²)` |
| `0.2 <= disorder < 0.5` | Medium | `O(n√n)` |
| `disorder >= 0.5` | Complex | `O(n log n)` |

이 경계는 과제에서 정의한 low/medium/high disorder 구간을 그대로 반영한다.

- **Low disorder**: 단순한 삽입 위치 계산과 회전만 사용하는 Simple로 제어 구조의 부담을 줄인다.
- **Medium disorder**: 값의 rank를 chunk 단위로 모아 개별 삽입보다 이동 범위를 줄인다.
- **High disorder**: 초기 순서에 덜 의존하는 균형 partition을 사용해 연산 수 증가를 `O(n log n)`으로 제한한다.

`--adaptive`가 기본 동작이며, selector가 없을 때도 같은 방식으로 선택한다. `--simple`, `--medium`, `--complex`가 지정되면 disorder와 관계없이 해당 전략을 실행한다.

Adaptive의 내부 공간 상한은 선택된 전략을 따른다. 따라서 low/medium/high 구간에서 연산 버퍼까지 포함한 상한은 각각 `O(n²)`, `O(n√n)`, `O(n log n)`이다.

### 3.8 공통 연산 계층

모든 전략은 저수준 스택 함수를 직접 호출하는 대신 `op_push()`, `op_swap()`, `op_rotate()`, `op_rrotate()`를 사용한다.

```text
정렬 함수
└─ op_* wrapper
   ├─ 대상 포인터로 pa/pb, sa/sb, ra/rb, rra/rrb 판정
   ├─ push_stack / swap_stack / rotate_stack / rrotate_stack
   └─ store_op
```

이 계층은 **스택 상태 변경과 명령 기록이 항상 함께 일어나도록** 보장한다. `rotate_n()`은 양수면 rotate, 음수면 reverse rotate를 반복하고, `find_min_idx_stack()`과 `find_max_idx_stack()`은 top 기준 위치를 반환한다. `binary_search()`는 `sorted` 배열에서 값의 rank를 찾는다.

---

## 4. Instructions

### 4.1 컴파일

필요 환경은 C 컴파일러 `cc`와 `make`이다. 기본 빌드는 `-Wall -Wextra -Werror` 플래그를 사용한다.

```bash
make            # push_swap 생성
make bonus      # checker 생성
make clean      # object와 dependency 파일 삭제
make fclean     # object, dependency, 실행 파일 삭제
make re         # 전체 재빌드
```

프로젝트의 `Makefile`이 먼저 `libft/Makefile`을 호출하여 `libft.a`를 만든 뒤 각 실행 파일을 링크한다.

### 4.2 실행

기본 형식에서 selector와 `--bench`는 숫자 인자보다 앞에 둔다.

```bash
./push_swap [--simple|--medium|--complex|--adaptive] [--bench] <integers>
```

#### Adaptive 기본 실행

```bash
./push_swap 4 67 3 87 23
./push_swap --adaptive 4 67 3 87 23
```

#### 특정 전략 강제 실행

```bash
./push_swap --simple 5 4 3 2 1
./push_swap --medium 5 4 3 2 1
./push_swap --complex 5 4 3 2 1
```

#### 공식 checker로 결과 확인

```bash
ARG="4 67 3 87 23"
./push_swap --complex $ARG | ./checker_linux $ARG
# OK
```

#### 명령 수 확인

```bash
ARG="4 67 3 87 23"
./push_swap $ARG | wc -l
```

인자가 없으면 아무것도 출력하지 않고 종료한다.

### 4.3 오류 처리

다음 입력은 `Error\n`을 stderr에 출력한다.

- 정수가 아닌 인자
- `int` 범위를 벗어난 값
- 중복된 정수
- 비어 있거나 공백만 있는 숫자 인자
- 잘못 사용하거나 중복 사용한 옵션

```bash
./push_swap --adaptive 0 one 2 3
# Error

./push_swap --simple 3 2 3
# Error
```

---

## 5. Benchmark

### 5.1 벤치마크 모드

`--bench`를 사용하면 정렬 명령은 기존과 같이 stdout으로 보내고, 통계만 stderr에 출력한다.

```bash
./push_swap --bench --medium 5 1 4 2 3 > operations.txt 2> benchmark.txt
cat benchmark.txt
```

출력 항목은 다음과 같다.

- 초기 disorder 백분율(소수점 둘째 자리)
- 선택된 전략과 이론적 복잡도
- 최종 명령 수
- `sa`, `sb`, `ss`, `pa`, `pb`, `ra`, `rb`, `rr`, `rra`, `rrb`, `rrr`별 횟수

checker로 명령을 검증하면서 benchmark를 별도 보관할 수도 있다.

```bash
ARG="4 67 3 87 23"
./push_swap --bench $ARG 2> benchmark.txt | ./checker_linux $ARG
```

### 5.2 성능 기준

| 입력 크기 | 통과 | 우수 | 최우수 |
|---:|---:|---:|---:|
| 무작위 100개 | 2,000 미만 | 1,500 미만 | 700 미만 |
| 무작위 500개 | 12,000 미만 | 8,000 미만 | 5,500 미만 |

명령 수는 연산 버퍼의 최종 출력 명령을 기준으로 하며 제공된 checker로 정렬 결과를 함께 검증한다.

---

## 6. Bonus: checker

`checker`는 숫자 인자로 초기 stack `a`를 만든 뒤 stdin에서 명령을 읽어 직접 실행한다.

```text
checker main
├─ init_push_swap_stat
├─ parse_stack -> merge_sort -> check_duplicate
├─ run_instructions
│  ├─ get_next_line(0)
│  └─ execute_instruction
│     └─ swap/push/rotate/reverse rotate 함수
├─ is_sorted(a) && size(b) == 0
│  ├─ 참: OK
│  └─ 거짓: KO
└─ free_resources
```

`execute_instruction()`은 줄바꿈을 포함한 문자열을 11개 허용 명령과 정확히 비교한다. 알 수 없거나 형식이 잘못된 명령이면 `Error`를 출력한다. 모든 명령 실행 후 `is_sorted()`가 `a`를 top부터 검사하며, `a`가 오름차순이고 `b`가 비어 있을 때만 `OK`, 그 외에는 `KO`를 출력한다.

```bash
make bonus
ARG="3 2 1 0"
./push_swap $ARG | ./checker $ARG
# OK
```

---

## 7. Resources

### 7.1 참고 자료

- [`push_swap.pdf`](./push_swap.pdf) — 프로젝트 규칙, 전략별 복잡도, disorder, benchmark 및 checker 요구사항
- [Big-O notation](https://en.wikipedia.org/wiki/Big_O_notation) — 알고리즘 상한과 성장률
- [Inversion (discrete mathematics)](https://en.wikipedia.org/wiki/Inversion_(discrete_mathematics)) — disorder 계산에 사용한 inversion 정의
- [Circular buffer](https://en.wikipedia.org/wiki/Circular_buffer) — 원형 배열 스택의 인덱스 순환 방식
- [Merge sort](https://en.wikipedia.org/wiki/Merge_sort) — rank 기준 배열 생성에 사용한 병합 정렬

### 7.2 AI 사용 내역

AI는 다음 보조 작업에 사용하였다.

- Complex 전략에서 횟수 최적화에 대한 아이디어 도출
- 소스 파일별 호출 관계, 자료구조 및 메모리 해제 흐름 정리
- Simple/Medium/Complex/Adaptive 전략 설명과 Push_swap 연산 기준 복잡도 서술 검토
- 실행 예시와 README 초안 작성 및 문장 교정
- N의 증가에 따른 명령어 횟수 증가율 스크립트 작성