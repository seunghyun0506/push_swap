# 명령어 생성·버퍼 최적화 연결 관계 및 오류 분석

> 분석 대상: 현재 디렉터리의 소스 코드
>
> 원본 소스는 수정하지 않았습니다. 이 문서는 명령 enum 생성부터 실제 스택 연산, `store_op()` 최적화, 출력 및 checker 재실행까지 연결되는 함수를 추적하고 관련 오류를 정리합니다.

---

## 1. 전체 명령 처리 흐름

```text
정렬 알고리즘
  │
  ├─ op = OP_XXX
  ├─ stack 함수로 실제 A/B 변경
  └─ store_op(stat->op_buffer, op)
          │
          ├─ OP_NONE이면 무시
          ├─ 이전 명령과 상쇄
          ├─ 이전 명령과 rr/rrr/ss로 병합
          └─ 최종 t_op를 buffer->arr에 저장
                  │
                  ├─ print_op_buffer(): stdout 명령 문자열 출력
                  └─ print_bench_info(): 명령별 개수 집계

출력된 명령
  └─ checker의 execute_instruction()
          └─ 동일한 ft_stack 함수를 호출하여 A/B 상태 재현
```

핵심 요구사항은 다음 두 결과가 같아야 한다는 것입니다.

```text
알고리즘이 직접 변경한 실제 스택 상태
=
최적화된 출력 명령을 checker가 처음부터 실행한 상태
```

---

## 2. 명령 enum 정의

- 파일: `ft_stack/include/ft_stack.h:24-38`

```c
typedef enum e_op
{
    OP_NONE,
    OP_SA,
    OP_SB,
    OP_SS,
    OP_PA,
    OP_PB,
    OP_RA,
    OP_RB,
    OP_RR,
    OP_RRA,
    OP_RRB,
    OP_RRR
}   t_op;
```

실제 값과 출력 연결은 다음과 같습니다.

| 값 | enum | 출력 문자열 | 실제 연결 함수 |
|---:|---|---|---|
| 0 | `OP_NONE` | 출력 없음 | 실패/무효 명령 표시 |
| 1 | `OP_SA` | `sa\n` | `swap_stack(A)` |
| 2 | `OP_SB` | `sb\n` | `swap_stack(B)` |
| 3 | `OP_SS` | `ss\n` | `swap_stacks(A, B)` |
| 4 | `OP_PA` | `pa\n` | `push_stack(B, A)` |
| 5 | `OP_PB` | `pb\n` | `push_stack(A, B)` |
| 6 | `OP_RA` | `ra\n` | `rotate_stack(A)` |
| 7 | `OP_RB` | `rb\n` | `rotate_stack(B)` |
| 8 | `OP_RR` | `rr\n` | `rotate_stacks(A, B)` |
| 9 | `OP_RRA` | `rra\n` | `rrotate_stack(A)` |
| 10 | `OP_RRB` | `rrb\n` | `rrotate_stack(B)` |
| 11 | `OP_RRR` | `rrr\n` | `rrotate_stacks(A, B)` |

`OP_XXX`는 전처리기 매크로가 아니라 enum 상수입니다.

---

## 3. 버퍼 생성 연결

### 호출 경로

```text
main()
  └─ init_push_swap_stat()
       └─ init_op_buffer()
```

- `src/main.c:30`: `init_push_swap_stat(&stat, argc, argv)`
- `src/push_swap_stat.c:26`: `stat->op_buffer = init_op_buffer()`
- `src/op_buffer/op_buffer.c:17`: `init_op_buffer()`

초기 상태:

```text
capacity = 32
idx      = 0
arr      = t_op 32개 동적 배열
```

### [오류 1 / 조건부 치명적] 초기 버퍼 할당 실패를 검사하지 않음

`init_op_buffer()`는 할당 실패 시 `NULL`을 반환하지만 `init_push_swap_stat()`과 `main()`은 이를 검사하지 않습니다.

연결 결과:

```text
init_op_buffer() 실패
  → stat->op_buffer == NULL
  → 알고리즘의 실제 스택 연산은 계속 실행
  → store_op(NULL, op)는 모든 명령을 버림
  → print_op_buffer(NULL)는 아무것도 출력하지 않음
  → checker는 정렬 과정을 재현할 수 없음
```

`--bench`가 있으면 `print_bench_info()`가 `stat->op_buffer->idx`를 직접 읽기 때문에 NULL dereference도 발생할 수 있습니다.

---

## 4. 알고리즘별 실제 명령 생성 함수

## 4.1 Simple

- `src/sort/simple/simple_sort.c`
- `src/sort/simple/align.c`

연결되는 명령:

```text
simple_sort()
  ├─ n == 2
  │    └─ swap_stack(A) → OP_SA → store_op()
  ├─ move_to_b()
  │    └─ push_stack(A, B) → OP_PB → store_op()
  ├─ insert_to_a()
  │    ├─ rotate_a_n()
  │    │    ├─ rotate_stack(A)  → OP_RA  → store_op()
  │    │    └─ rrotate_stack(A) → OP_RRA → store_op()
  │    └─ push_stack(B, A) → OP_PA → store_op()
  └─ align_a()
       └─ align_stack_a()
            └─ rotate_to_top()
                 ├─ rotate_stack(A)  → OP_RA
                 └─ rrotate_stack(A) → OP_RRA
```

현재 Simple 호출부에서는 실제 대상 스택과 기록 enum이 일치합니다.

---

## 4.2 Medium

- `src/sort/medium/medium_sort_divide.c`
- `src/sort/medium/medium_sort_return.c`

분할 단계:

```text
divide_by_chunks()
  └─ push_pair_to_b()
       ├─ rotate_a_n()
       │    ├─ rotate_stack(A)  → OP_RA
       │    └─ rrotate_stack(A) → OP_RRA
       ├─ push_stack(A, B) → OP_PB
       └─ 작은 청크인 경우 rotate_stack(B) → OP_RB
```

반환 단계:

```text
return_to_a_by_chunk()
  ├─ small_sort(A, B, A 크기)
  └─ push_max_to_a()
       ├─ rotate_s_n(B)
       │    ├─ rotate_stack(B)  → OP_RB
       │    └─ rrotate_stack(B) → OP_RRB
       └─ push_stack(B, A) → OP_PA
```

현재 Medium 호출부에서도 실제 연산 대상과 enum은 일치합니다.

단, Medium이 크기 3 이하에서 호출하는 공통 `small_sort()`에는 아래 9번의 3원소 알고리즘 오류가 있습니다.

---

## 4.3 Complex

- `src/sort/complex/complex_sort_util.c`

A 분할:

```text
partition_asc()
  ├─ 큰 그룹: op_rot(A, OP_RA, forward)
  ├─ 나머지: op_push(A, B, OP_PB)
  └─ 중간 그룹: op_rot(B, OP_RB, forward)
```

B 분할:

```text
partition_desc()
  ├─ 작은 그룹: op_rot(B, OP_RB, forward)
  ├─ 나머지: op_push(B, A, OP_PA)
  └─ 중간 그룹: op_rot(A, OP_RA, forward)
```

되감기:

```text
rewind_stack()
  ├─ 양쪽 동시: rrotate_stacks(A, B) → OP_RRR → store_op()
  ├─ A 나머지: op_rot(A, OP_RRA, reverse)
  └─ B 나머지: op_rot(B, OP_RRB, reverse)
```

`op_push()`과 `op_rot()`은 전달받은 enum을 검증하지 않고 저장합니다. 현재 호출부에서는 A/B와 enum이 일치하지만, 이후 잘못된 조합으로 호출되면 다음과 같은 불일치가 생길 수 있습니다.

```c
/* 잘못된 호출의 예시 */
op_rot(stat, stack_a, OP_RB, 0);
```

이 경우 실제로는 A가 회전하지만 출력은 `rb`가 되어 checker 상태가 달라집니다. 현재 코드에 이 잘못된 호출은 확인되지 않았습니다.

---

## 5. `OP_NONE` 연결

다음 실제 스택 함수는 연산할 수 없으면 전달받은 `op`를 `OP_NONE`으로 바꿉니다.

- `ft_stack/stack_push.c::push_stack()`
- `ft_stack/stack_swap.c::swap_stack()`
- `ft_stack/stack_swap.c::swap_stacks()`
- `ft_stack/stack_rotate.c::rotate_stack()`
- `ft_stack/stack_rotate.c::rotate_stacks()`
- `ft_stack/stack_rrotate.c::rrotate_stack()`
- `ft_stack/stack_rrotate.c::rrotate_stacks()`

그 다음:

```text
stack 함수 실패
  → op = OP_NONE
  → store_op(buffer, OP_NONE)
  → 저장하지 않음
  → print_op_buffer()에도 나타나지 않음
```

이 연결 덕분에 실행되지 않은 단일 연산이 출력되는 문제는 방지됩니다.

---

## 6. `store_op()` 최적화 연결

- `src/op_buffer/op_buffer.c:90-113`

```text
store_op()
  └─ get_action_type(last_op, current_op, &merged)
       ├─ 0: 변환 없음
       ├─ 1: 상쇄하여 두 명령 제거
       └─ 2: 결합 명령으로 변경 후 이전 명령과 다시 검사
```

## 6.1 상쇄 규칙

```text
ra  + rra → 제거
rra + ra  → 제거
rb  + rrb → 제거
rrb + rb  → 제거
pa  + pb  → 제거
pb  + pa  → 제거
sa  + sa  → 제거
sb  + sb  → 제거
rr  + rrr → 제거
rrr + rr  → 제거
ss  + ss  → 제거
```

이 규칙은 두 명령이 인접하고 둘 다 실제로 실행된 경우 항등 연산이 됩니다.

특히 `pa + pb`, `pb + pa`는 중간 명령이 없을 때 방금 옮긴 top을 즉시 원래 스택으로 돌려놓으므로 안전합니다.

## 6.2 결합 규칙

```text
ra  + rb  → rr
rb  + ra  → rr
rra + rrb → rrr
rrb + rra → rrr
sa  + sb  → ss
sb  + sa  → ss
```

A와 B의 연산은 서로 다른 스택에 작용하고, 두 단일 명령이 버퍼에 저장됐다는 것은 양쪽 연산이 성공했다는 뜻입니다. 회전과 swap은 스택 크기를 변경하지 않으므로 병합 시점에도 양쪽 연산 조건이 유지됩니다.

## 6.3 반복 최적화

예:

```text
ra, rb, rrr
  → rr, rrr
  → 모두 제거
```

`ra + rb`와 `rr`이 같은 상태를 만들고 `rr + rrr`이 항등이므로 이 반복 변환도 정상 메모리 환경에서는 안전합니다.

---

## 7. [검증 결과] 현재 `store_op()` 규칙 자체의 정렬 파괴는 발견되지 않음

프로젝트 소스를 변경하지 않고 `/tmp`에 다음 두 테스트 빌드를 생성해 비교했습니다.

1. 현재 `store_op()` 최적화 사용
2. 상쇄/병합 없이 실행된 enum을 순서대로 저장

검사 범위:

- 크기 2~6의 모든 순열
- `--simple`, `--medium`, `--complex`, `--adaptive`
- 크기 10, 30, 100의 추가 무작위 입력
- 총 4,808개 전략/입력 조합

결과:

```text
최적화 출력과 비최적화 출력의 최종 A/B 상태 차이: 0
store_op 최적화 때문에 정상 정렬이 실패한 사례: 0
```

현재 확인된 일반 입력의 정렬 실패는 `store_op()`가 아니라 9번의 알고리즘 오류 및 8번의 결합 스택 함수 오류와 연결됩니다.

---

## 8. [확정 오류] `ss`, `rr`, `rrr` 실제 스택 함수의 명세 불일치

관련 함수:

- `ft_stack/stack_swap.c:32::swap_stacks()`
- `ft_stack/stack_rotate.c:30::rotate_stacks()`
- `ft_stack/stack_rrotate.c:35::rrotate_stacks()`

현재 공통 조건:

```c
if (get_stack_size(s1) <= 1 || get_stack_size(s2) <= 1)
{
    if (op)
        *op = OP_NONE;
    return (0);
}
```

즉 한쪽만 연산 가능해도 양쪽 모두 실행하지 않습니다.

push_swap의 결합 명령은 각 스택에서 가능한 단일 연산을 함께 수행해야 합니다. 한쪽이 불가능해도 다른 쪽의 가능한 연산은 실행되어야 합니다.

### checker 연결

```text
checker.c::execute_instruction("ss\n")
  → swap_stacks(A, B, NULL)

checker.c::execute_instruction("rr\n")
  → rotate_stacks(A, B, NULL)

checker.c::execute_instruction("rrr\n")
  → rrotate_stacks(A, B, NULL)
```

재현:

```sh
printf 'ss\n' | ./checker 2 1
# 현재 자체 checker: KO

printf 'ss\n' | ./checker_linux 2 1
# 공식 checker: OK
```

`rr`, `rrr`도 같은 구조의 오류가 있습니다.

### `store_op()` 병합과의 관계

성공한 `ra + rb`, `rra + rrb`, `sa + sb`에서 생성된 `rr`, `rrr`, `ss`는 양쪽 단일 연산이 이미 성공한 조건이므로 현재 `store_op()` 병합 자체는 안전합니다.

그러나 Complex의 `rewind_stack()`은 `OP_RRR`을 직접 생성하여 `rrotate_stacks()`를 호출합니다.

```text
complex_sort_helper_a/b()
  → rewind_stack()
       → rrotate_stacks(s1, s2, &op)
       → store_op(buffer, op)
```

이때 되감기 카운터는 양수지만 실제 스택 중 하나의 크기가 1 이하라면 현재 `rrotate_stacks()`는 양쪽 역회전을 모두 생략하고 `OP_NONE`을 저장합니다. 이 문제는 버퍼 병합이 아니라 결합 스택 함수의 동작 오류입니다.

---

## 9. [확정 오류] 잘못 선택된 명령이 정확히 저장되어 정렬 실패

관련 함수:

```text
medium_sort()/complex_sort()
  → small_sort()
       → three_sort_asc()
            → three_sort_asc_dispatch()
                 → op_rotate_s()
                      → rotate_stack()/rrotate_stack()
                      → store_op()
```

- 파일: `src/sort/three_sort.c:80::three_sort_asc_dispatch()`

실패 사례 1:

```text
초기 A: [1, 2, 0]
선택 명령: OP_RA
실제 결과: [2, 0, 1]
출력 명령: ra
checker 결과: [2, 0, 1]
```

실패 사례 2:

```text
초기 A: [2, 0, 1]
선택 명령: OP_RRA
실제 결과: [1, 2, 0]
출력 명령: rra
checker 결과: [1, 2, 0]
```

여기서는 `store_op()`와 `print_op_buffer()`가 실제로 실행된 잘못된 명령을 정확하게 기록·출력합니다. 따라서 정렬 실패 원인은 버퍼가 아니라 `three_sort_asc_dispatch()`의 회전 방향 선택입니다.

이 함수는 다음 경로로 전파됩니다.

```text
Medium
  → n <= 3 또는 마지막 A 구간
  → small_sort()
  → three_sort_asc()

Complex
  → 재귀 구간 size <= 3
  → small_sort()
  → three_sort_asc()
```

---

## 10. [조건부 치명적] 버퍼 resize 실패 시 실제 명령과 출력 명령 불일치

연결 함수:

```text
알고리즘의 stack 연산 성공
  → store_op()
       → buffer가 가득 참
       → resize_op_buffer()
            → malloc 실패
       → 현재 op를 저장하지 않음
```

- `src/op_buffer/op_buffer.c:70::resize_op_buffer()`
- `src/op_buffer/op_buffer.c:110-112::store_op()`

현재 코드:

```c
if (op != OP_NONE && (buffer->idx < buffer->capacity
        || resize_op_buffer(buffer)))
    buffer->arr[buffer->idx++] = op;
```

resize 실패 시 오류를 호출자에게 반환하지 않으므로:

```text
실제 스택: 명령이 이미 실행됨
버퍼: 해당 명령 누락
출력: 해당 명령 없음
checker: 내부 실제 상태와 달라짐
```

일반 메모리 환경에서는 드문 조건이지만 발생하면 정렬 출력의 정확성을 보장할 수 없습니다.

---

## 11. 출력 함수 연결

- `src/main.c:39`: `print_op_buffer(stat.op_buffer)`
- `src/main.c:45-71`: `print_op_buffer()`

```text
buffer->arr[i]
  → names[enum 값]
  → ft_putstr_fd(..., 1)
  → stdout
```

매핑:

```c
names[OP_SA] = "sa\n";
names[OP_SB] = "sb\n";
names[OP_SS] = "ss\n";
names[OP_PA] = "pa\n";
names[OP_PB] = "pb\n";
names[OP_RA] = "ra\n";
names[OP_RB] = "rb\n";
names[OP_RR] = "rr\n";
names[OP_RRA] = "rra\n";
names[OP_RRB] = "rrb\n";
names[OP_RRR] = "rrr\n";
```

유효 범위 검사:

```c
if (buffer->arr[i] >= OP_SA && buffer->arr[i] <= OP_RRR)
```

정상 enum에서는 매핑 오류가 없습니다. 그러나 메모리 손상 등으로 범위 밖 값이 저장되면 해당 명령을 조용히 출력하지 않아 실제 상태와 checker 상태가 달라질 수 있습니다.

또한 `names[13]`과 benchmark의 `counts[13]`은 enum 개수를 하드코딩하고 있습니다. 현재 enum은 0~11이라 즉시 오류는 없지만, 향후 enum 추가 시 배열 크기와 범위 검사를 함께 변경하지 않으면 오류가 생길 수 있습니다.

---

## 12. Benchmark 연결

```text
main()
  → print_op_buffer()
  → print_bench_info()
       → print_counts()
            → counts[buffer->arr[i]]++
```

benchmark는 알고리즘이 처음 실행한 명령 수가 아니라 `store_op()`의 상쇄·병합 이후 최종 출력 명령 수를 집계합니다.

예:

```text
실행: ra, rb
버퍼: rr
benchmark: ra=0, rb=0, rr=1
```

이는 출력 명령 기준 통계이므로 정상입니다.

단, `op_buffer == NULL`일 때 `print_bench_info()`에는 NULL 검사가 없어 crash 위험이 있습니다.

---

## 13. 오류별 함수 연결 요약

| 구분 | 시작 함수 | 연결 함수 | 결과 |
|---|---|---|---|
| 초기 버퍼 할당 실패 | `init_push_swap_stat()` | `init_op_buffer()` → `store_op()` → `print_op_buffer()` | 실제 연산은 수행되지만 명령 전체 누락 |
| 버퍼 확장 실패 | `store_op()` | `resize_op_buffer()` | 현재 실제 명령 하나 이상 누락 |
| 결합 명령 명세 오류 | `checker::execute_instruction()` / `rewind_stack()` | `swap_stacks()`, `rotate_stacks()`, `rrotate_stacks()` | 한쪽만 가능한 연산까지 생략 |
| 3원소 명령 선택 오류 | `small_sort()` | `three_sort_asc()` → `three_sort_asc_dispatch()` → `store_op()` | 잘못된 `ra`/`rra`가 정확히 출력됨 |
| Complex 직접 `rrr` 위험 | `complex_sort_helper_a/b()` | `rewind_stack()` → `rrotate_stacks()` | 결합 함수 조건 때문에 되감기 누락 가능 |
| 범위 밖 enum | 알고리즘/메모리 손상 | `store_op()` → `print_op_buffer()` | 출력 함수가 명령을 조용히 생략 가능 |
| benchmark NULL 접근 | `main()` | `print_bench_info()` | op buffer 초기화 실패 시 crash 가능 |

---

## 14. 최종 판단

1. 정상 메모리 환경에서 현재 `store_op()`의 인접 상쇄 및 병합 규칙이 정렬을 깨는 사례는 확인되지 않았습니다.
2. 현재 일반 입력에서 확인된 Medium/Complex 정렬 실패는 `three_sort_asc_dispatch()`가 잘못된 `ra`/`rra`를 선택하는 오류와 연결됩니다.
3. `ss`, `rr`, `rrr` 관련 명세 오류는 `store_op()`보다 하위 계층인 `swap_stacks()`, `rotate_stacks()`, `rrotate_stacks()`에 있습니다.
4. Complex의 `rewind_stack()`은 `OP_RRR`을 직접 생성하므로 잘못된 결합 역회전 구현의 영향을 받을 수 있습니다.
5. `init_op_buffer()` 또는 `resize_op_buffer()` 실패 시 실제 스택에서 이미 실행한 명령이 출력 버퍼에서 누락되므로, 이 조건에서는 버퍼 계층 때문에 정렬 재현이 깨질 수 있습니다.
