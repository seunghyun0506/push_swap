# 3원소 오름차순 정렬 오류 분석 및 해결 방법

> 관련 소스: `src/sort/three_sort.c`
>
> 이 문서는 오류의 원인과 해결 방향을 설명하기 위한 문서입니다. 요청된 기존 원칙에 따라 실제 C 소스는 수정하지 않았습니다.

## 1. 오류 요약

현재 `three_sort_asc_dispatch()`는 3개 값으로 만들 수 있는 6개 순열 중 다음 두 경우에 회전 방향을 반대로 선택합니다.

```text
[중간값, 최댓값, 최솟값] → 현재 ra  사용 → 실패
[최댓값, 최솟값, 중간값] → 현재 rra 사용 → 실패
```

실제 값으로 표현하면 다음과 같습니다.

```text
[1, 2, 0] → 현재 ra  → [2, 0, 1] (정렬되지 않음)
[2, 0, 1] → 현재 rra → [1, 2, 0] (정렬되지 않음)
```

두 경우의 올바른 방향은 다음과 같습니다.

```text
[1, 2, 0] → rra → [0, 1, 2]
[2, 0, 1] → ra  → [0, 1, 2]
```

즉 두 조건문에서 호출하는 `ra`와 `rra`가 서로 뒤바뀌어 있습니다.

---

## 2. 코드에서 사용하는 `t`, `m`, `b`의 의미

`three_sort_asc()`와 `three_sort_asc_dispatch()`는 스택 A의 위쪽 3개 값을 다음과 같이 읽습니다.

```c
t = s1->datas[s1->top_index];
m = s1->datas[prev_idx(s1, s1->top_index)];
b = s1->datas[prev_idx(s1, prev_idx(s1, s1->top_index))];
```

각 변수는 다음 위치를 의미합니다.

```text
t = top 원소
m = top 바로 아래 원소
b = 세 번째 원소
```

따라서 스택을 top에서 아래 방향으로 표현하면 다음과 같습니다.

```text
top → t, m, b → bottom 방향
```

3개가 오름차순으로 정렬된 상태는 다음 조건입니다.

```c
t < m && m < b
```

예:

```text
top → 0, 1, 2
```

`three_sort_asc()`는 이미 이 상태이면 아무 연산도 하지 않습니다.

---

## 3. 이 프로젝트에서 `ra`와 `rra`가 이동시키는 방향

3개 원소를 다음처럼 표현하겠습니다.

```text
top → [t, m, b]
```

### `ra`

`ra`는 top 원소를 bottom으로 보냅니다.

```text
[t, m, b] --ra--> [m, b, t]
```

예:

```text
[2, 0, 1] --ra--> [0, 1, 2]
```

### `rra`

`rra`는 bottom 원소를 top으로 가져옵니다.

```text
[t, m, b] --rra--> [b, t, m]
```

예:

```text
[1, 2, 0] --rra--> [0, 1, 2]
```

오류를 이해할 때 가장 중요한 차이는 다음과 같습니다.

```text
ra  : 첫 번째 값을 맨 뒤로
rra : 마지막 값을 맨 앞으로
```

---

## 4. 3개 원소의 모든 경우 분석

서로 다른 3개 값은 총 6가지 순열을 만들 수 있습니다. 최솟값을 `0`, 중간값을 `1`, 최댓값을 `2`라고 놓으면 모든 경우는 다음과 같습니다.

| 입력 `(t, m, b)` | 값의 관계 | 필요한 명령 | 현재 코드 | 결과 |
|---|---|---|---|---|
| `[0, 1, 2]` | `t < m < b` | 없음 | 없음 | 정상 |
| `[0, 2, 1]` | `t < b < m` | `sa`, `ra` | `sa`, `ra` | 정상 |
| `[1, 0, 2]` | `m < t < b` | `sa` | `sa` | 정상 |
| `[1, 2, 0]` | `b < t < m` | `rra` | `ra` | 오류 |
| `[2, 0, 1]` | `m < b < t` | `ra` | `rra` | 오류 |
| `[2, 1, 0]` | `b < m < t` | `sa`, `rra` | `sa`, `rra` | 정상 |

따라서 6가지 중 정확히 2가지 분기의 회전 방향이 잘못되어 있습니다.

---

## 5. 첫 번째 오류 분기: `b < t && t < m`

현재 코드:

```c
else if (b < t && t < m)
    op_rotate_s(stat, s1, OP_RA);
```

관계식:

```text
b < t < m
```

이는 위치별 값이 다음과 같다는 뜻입니다.

```text
t = 중간값
m = 최댓값
b = 최솟값
```

예:

```text
top → [1, 2, 0]
```

최솟값 `0`이 bottom에 있으므로, 최솟값을 top으로 가져와야 합니다. 따라서 필요한 연산은 `rra`입니다.

올바른 흐름:

```text
[1, 2, 0] --rra--> [0, 1, 2]
```

현재 흐름:

```text
[1, 2, 0] --ra--> [2, 0, 1]
```

현재 코드는 top의 중간값 `1`을 bottom으로 보내므로 여전히 회전된 상태가 남습니다.

해결 방향은 이 분기에서 `OP_RA`가 아니라 `OP_RRA`를 선택하는 것입니다.

개념적으로 필요한 변경:

```diff
 else if (b < t && t < m)
-    op_rotate_s(stat, s1, OP_RA);
+    op_rotate_s(stat, s1, OP_RRA);
```

이 diff는 설명용이며 실제 소스에는 적용하지 않았습니다.

---

## 6. 두 번째 오류 분기: `m < b && b < t`

현재 코드:

```c
else if (m < b && b < t)
    op_rotate_s(stat, s1, OP_RRA);
```

관계식:

```text
m < b < t
```

이는 위치별 값이 다음과 같다는 뜻입니다.

```text
t = 최댓값
m = 최솟값
b = 중간값
```

예:

```text
top → [2, 0, 1]
```

최댓값 `2`가 top에 있으므로 이 값을 bottom으로 보내야 합니다. 따라서 필요한 연산은 `ra`입니다.

올바른 흐름:

```text
[2, 0, 1] --ra--> [0, 1, 2]
```

현재 흐름:

```text
[2, 0, 1] --rra--> [1, 2, 0]
```

현재 코드는 bottom의 중간값 `1`을 top으로 가져오기 때문에 여전히 회전된 상태가 남습니다.

해결 방향은 이 분기에서 `OP_RRA`가 아니라 `OP_RA`를 선택하는 것입니다.

개념적으로 필요한 변경:

```diff
 else if (m < b && b < t)
-    op_rotate_s(stat, s1, OP_RRA);
+    op_rotate_s(stat, s1, OP_RA);
```

이 diff는 설명용이며 실제 소스에는 적용하지 않았습니다.

---

## 7. 해결 방법 요약

`three_sort_asc_dispatch()`에서 다음 두 분기의 연산을 서로 교환해야 합니다.

```text
조건                  현재 연산    필요한 연산
b < t && t < m        OP_RA        OP_RRA
m < b && b < t        OP_RRA       OP_RA
```

수정 대상만 모아 표현하면 다음과 같습니다.

```diff
 else if (b < t && t < m)
-    op_rotate_s(stat, s1, OP_RA);
+    op_rotate_s(stat, s1, OP_RRA);
 else if (m < b && b < t)
-    op_rotate_s(stat, s1, OP_RRA);
+    op_rotate_s(stat, s1, OP_RA);
```

단, 사용자 요청에 따라 이 문서 작성 시 실제 `src/sort/three_sort.c`는 수정하지 않았습니다.

---

## 8. 왜 Medium과 Complex에도 영향을 주는가

이 오류는 `three_sort_asc()` 하나에만 국한되지 않습니다.

### Medium

`medium_sort()`는 원소가 3개 이하이면 다음을 호출합니다.

```c
small_sort(stat, stat->stack_a, stat->stack_b, n);
```

`small_sort()`에서 크기가 3이면:

```c
three_sort_asc(stat, s1, s2);
```

를 호출합니다.

따라서 다음 입력은 Medium 전략 자체가 바로 잘못된 3원소 분기를 실행합니다.

```sh
./push_swap --medium 1 2 0
```

현재 출력:

```text
ra
```

적용 결과:

```text
[1, 2, 0] --ra--> [2, 0, 1]
```

그러므로 공식 checker가 `KO`를 출력합니다.

### Complex

Complex는 3분할 재귀를 진행하고 부분 구간 크기가 3 이하가 되면 다음 공통 함수로 종료합니다.

```text
complex_sort_helper_a
  → small_sort
      → three_sort_asc

complex_sort_helper_b
  → small_sort_helper
      → three_sort_desc
      → 내부적으로 three_sort_asc 사용 가능
```

따라서 전체 입력이 5개, 100개, 500개여도 재귀의 마지막 부분 구간이 문제의 순열 형태가 되면 최종 정렬이 실패할 수 있습니다.

확인된 예:

```sh
./push_swap --complex 0 1 3 4 2 | ./checker_linux 0 1 3 4 2
# KO
```

다만 Complex에는 결합 회전 함수의 별도 명세 불일치도 존재하므로, 이 두 분기를 해결한 것만으로 Complex 전체의 모든 입력이 정상이라고 바로 단정해서는 안 됩니다. 수정 후 별도의 전체 검증이 필요합니다.

---

## 9. 해결 후 권장 검증 방법

실제 수정 권한이 주어져 두 분기를 변경하게 된다면 먼저 3개 원소의 6개 순열을 전부 검사해야 합니다.

```sh
./push_swap --medium 0 1 2 | ./checker_linux 0 1 2
./push_swap --medium 0 2 1 | ./checker_linux 0 2 1
./push_swap --medium 1 0 2 | ./checker_linux 1 0 2
./push_swap --medium 1 2 0 | ./checker_linux 1 2 0
./push_swap --medium 2 0 1 | ./checker_linux 2 0 1
./push_swap --medium 2 1 0 | ./checker_linux 2 1 0
```

여섯 결과가 모두 다음이어야 합니다.

```text
OK
```

전략별로도 검사해야 합니다.

```text
--simple
--medium
--complex
--adaptive
```

그 다음에는 크기 4 이상 순열과 무작위 입력을 검사해야 합니다. 특히 Complex는 재귀 종료 과정에서 `three_sort_asc()`를 사용하므로 3원소 직접 테스트만으로 충분하지 않습니다.

검증 항목:

```text
1. 출력 명령이 모두 유효한가
2. 명령 적용 후 A가 오름차순인가
3. 명령 적용 후 B가 비어 있는가
4. 프로그램 종료 코드가 정상인가
5. ASan/UBSan 오류가 없는가
6. 모든 강제 전략과 Adaptive에서 결과가 올바른가
```

---

## 10. 결론

오류의 직접 원인은 `three_sort_asc_dispatch()`가 다음 두 형태를 처리할 때 회전 방향을 반대로 선택하는 것입니다.

```text
[중간값, 최댓값, 최솟값]에는 rra가 필요하지만 ra 사용
[최댓값, 최솟값, 중간값]에는 ra가 필요하지만 rra 사용
```

따라서 해결 핵심은 다음 한 줄 요약과 같습니다.

```text
`b < t < m` 분기와 `m < b < t` 분기의 RA/RRA를 서로 교환한다.
```

이 오류는 Medium의 3원소 입력뿐 아니라 Complex의 재귀 종료에도 전파되므로, 해결 후에는 6개 순열 테스트와 더 큰 입력에 대한 전략별 회귀 테스트가 모두 필요합니다.
