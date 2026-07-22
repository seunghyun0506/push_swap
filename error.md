# 프로젝트 분석 중 발견된 오류 및 위험 사항

> 원본 소스는 수정하지 않았습니다. 이 파일은 분석 결과만 기록합니다.
> 테스트용 실행 파일과 스크립트는 프로젝트 밖의 `/tmp`에 만들었습니다.

## 1. [확정 / 치명적] 3개 원소 정렬이 일부 순열에서 실패

- 관련 파일: `src/sort/three_sort.c` (`three_sort_asc_dispatch`)
- 재현:

```sh
./push_swap --medium 1 2 0 | ./checker_linux 1 2 0
# KO

./push_swap --medium 2 0 1 | ./checker_linux 2 0 1
# KO
```

현재 소스를 `/tmp`에 새로 빌드하여 확인한 실제 명령은 각각 `ra`, `rra`이고, 결과는 다음과 같습니다.

- `[1, 2, 0] --ra--> [2, 0, 1]` (정렬되지 않음)
- `[2, 0, 1] --rra--> [1, 2, 0]` (정렬되지 않음)

`three_sort_asc_dispatch()`에서 다음 두 경우의 회전 방향이 뒤바뀐 것으로 보입니다.

- `b < t && t < m`
- `m < b && b < t`

이 공통 소형 정렬은 Medium과 Complex의 재귀 종료 조건에서 모두 사용되므로 상위 알고리즘까지 오염시킵니다.

테스트 결과:

- 크기 2~6의 순열을 전략별로 검사하는 과정에서 Medium 실패 확인
- Complex는 크기 5~6에서 다수 실패
- 예: `--complex 0 1 3 4 2`의 최종 A가 `[0, 1, 4, 2, 3]`

## 2. [확정 / 치명적] Complex 정렬 다수 입력 실패

- 관련 파일: `src/sort/complex/*`, 특히 공통 종료 정렬인 `src/sort/three_sort.c`
- 재현:

```sh
./push_swap --complex 0 1 3 4 2 | ./checker_linux 0 1 3 4 2
# KO
```

크기 2~6의 순열 테스트에서 Complex 실패 사례가 다수 검출되었습니다. 관찰한 실패의 상당수는 마지막 3개 구간이 회전된 상태로 남아 있어 1번의 3원소 정렬 오류가 직접 전파된 형태입니다. 다만 복합 정렬에는 4번의 결합 연산 문제도 영향을 줄 수 있으므로, 3원소 정렬만 고쳤다고 전체 Complex가 반드시 정상이라고 단정할 수는 없습니다.

## 3. [확정 / 치명적] 정수 범위 초과를 거부하지 않고 signed overflow 발생

- 관련 파일: `libft/src/ft_strtoi.c`, `src/push_swap.c`
- 문제: `int`에 숫자를 누적하면서 `INT_MIN~INT_MAX` 범위를 검사하지 않습니다.
- UBSan 확인:

```text
libft/src/ft_strtoi.c:33:18: runtime error: signed integer overflow
```

예를 들어 `2147483648`, `-2147483649`, 매우 긴 숫자가 `Error`로 거부되지 않고 잘못된 int 값으로 수용될 수 있습니다. C의 signed overflow는 undefined behavior입니다.

## 3-1. [확정] 부호만 있는 토큰 `+`, `-`를 숫자 0으로 허용

- 관련 파일: `libft/src/ft_strtoi.c`, `src/push_swap.c::parse_integers`
- `ft_strtoi()`는 부호를 소비한 뒤 숫자가 한 자리 이상 존재하는지 알려주지 않습니다.
- `parse_integers()`의 `str == pos` 검사도 부호가 소비되었기 때문에 실패를 감지하지 못합니다.

재현:

```sh
./push_swap '+'
./push_swap '-'
./push_swap '+ 1'
./push_swap '- 1'
```

현재는 각각 `0`, `0`, `0 1`, `0 1`처럼 받아들여 정상 종료합니다. push_swap의 유효 정수 문법상 부호 뒤에는 적어도 한 자리 숫자가 필요하므로 모두 `Error`여야 합니다.

## 4. [확정 / 치명적] `ss`, `rr`, `rrr`가 한쪽 스택에서만 가능한 경우에도 양쪽 모두 실행하지 않음

- 관련 파일:
  - `ft_stack/stack_swap.c::swap_stacks`
  - `ft_stack/stack_rotate.c::rotate_stacks`
  - `ft_stack/stack_rrotate.c::rrotate_stacks`
- 현재 구현은 **두 스택 모두 원소가 2개 이상일 때만** 결합 연산을 실행합니다.
- push_swap 명세의 결합 연산은 각 단일 연산을 동시에 시도하는 의미이므로, 한쪽이 불가능해도 다른 쪽에서 가능한 연산은 실행되어야 합니다.

재현:

```sh
printf 'ss\n' | ./checker 2 1
# 현재 checker: KO

printf 'ss\n' | ./checker_linux 2 1
# 공식 checker: OK
```

동일하게 `rr`, `rrr`도 재현됩니다. Checker의 판정이 명세와 달라지며, Complex의 `rewind_stack()`에서 결합 역회전을 직접 사용할 때 정렬에도 영향을 줄 수 있습니다.

## 5. [확정] 파싱 오류 및 중복 플래그 경로에서 op buffer 메모리 누수

- 관련 파일: `src/main.c`, `src/push_swap_stat.c`, `src/push_swap.c`
- `init_push_swap_stat()`에서 `op_buffer`를 먼저 할당한 뒤 다음 실패 경로에서 정리하지 않고 즉시 반환합니다.
  - `parse_flag()` 실패
  - `parse_stack()` 실패
- ASan/LeakSanitizer 확인: 2개 allocation, 총 144 bytes 누수(버퍼 구조체 16 bytes + 초기 배열 128 bytes).

## 6. [확정 가능 경로] 스택 할당 일부 실패 시 내부 배열 누수

- 관련 파일: `src/push_swap.c::parse_stack`
- `init_stack()`은 구조체와 `datas` 배열을 각각 할당합니다.
- 이후 세 할당(`stack_a`, `stack_b`, `sorted`) 중 일부가 실패하면 `free(stat->stack_a)` / `free(stat->stack_b)`만 호출합니다.
- 이미 성공한 스택의 `datas`는 `destroy_stack()`을 거치지 않아 누수됩니다.

## 7. [확정 가능 경로] op buffer 할당 실패를 초기화 성공 여부로 검사하지 않음

- 관련 파일: `src/push_swap_stat.c`, `src/main.c`, `src/print_bench.c`
- `init_op_buffer()`가 NULL이어도 파싱/정렬을 계속합니다.
- `store_op()`과 `print_op_buffer()`는 NULL을 방어하지만, `--bench`의 `print_bench_info()`는 `stat->op_buffer->idx`를 직접 역참조하므로 메모리 부족 상황에서 NULL dereference가 발생합니다.
- bench가 없더라도 연산이 저장되지 않아 성공 코드로 아무 출력도 하지 않을 수 있습니다.

## 8. [확정 가능 경로] merge sort 임시 메모리 할당 실패가 성공처럼 처리됨

- 관련 파일: `src/merge_sort.c`, `src/push_swap.c`
- `merge_sort()`의 임시 배열 malloc 실패 시 오류 전달 없이 반환합니다.
- `parse_stack()`은 이를 성공으로 간주합니다.
- 그 결과 `sorted`가 실제로 정렬되지 않아 중복 검사, rank 이진 탐색, 피벗/청크 계산이 모두 잘못될 수 있습니다.

## 9. [동작 결함] 이미 정렬된 입력에서 `--bench` 정보가 출력되지 않음

- 관련 파일: `src/main.c`
- `is_sorted()`가 참이면 `sort()`와 `print_bench_info()` 전에 반환합니다.
- 따라서 `./push_swap --bench 1 2 3`은 disorder, strategy, total_ops 등의 bench 정보를 전혀 출력하지 않습니다.

## 10. [확정] 저장된 `push_swap` 바이너리가 현재 소스와 불일치

- 저장된 바이너리/오브젝트 시각: 2026-07-20
- 주요 현재 소스 시각: 2026-07-21
- `out/print_bench.o`도 존재하지 않습니다.
- 저장된 바이너리는 오류 문자열을 stdout으로 출력하고 빈 문자열 인자를 정상 종료시키는 등 현재 소스를 `/tmp`에 새로 빌드한 결과와 다릅니다.
- 따라서 저장된 `./push_swap`의 실행 결과만으로 현재 소스를 평가하면 안 됩니다.

## 11. [빌드 설정] `compile_commands.json`이 현재 소스 목록과 불일치

- 존재하지 않는 `src/sort/medium/medium_sort_cost.c`를 참조합니다.
- 현재의 `src/sort/simple/simple_sort_cost.c`, `src/print_bench.c`, checker 소스 등이 정확히 반영되지 않았습니다.
- clangd 진단/인덱싱이 실제 Makefile 빌드와 달라질 수 있습니다.

## 12. [빌드 설정] 하위 Makefile의 의존성 및 re 규칙 문제

- `libft/Makefile`: `DEPS = $(OBJ:.o=.d)`에서 실제 변수는 `OBJS`인데 `OBJ`를 사용하므로 헤더 의존성 `.d` 파일이 include되지 않습니다.
- `ft_stack/Makefile`: `re:` 아래의 `fclean all`은 make 타깃 재귀 호출이 아니라 셸에서 `fclean`이라는 실행 파일을 찾는 명령이므로 `make -C ft_stack re`가 정상 동작하지 않습니다.

## 13. [잠재적 UB / 현재 미사용] `ft_abs(INT_MIN)` 오버플로

- 관련 파일: `libft/src/ft_abs.c`
- `INT_MIN`에 `num = -num`을 수행하면 int로 표현할 수 없어 signed overflow입니다.
- 이 파일은 현재 libft Makefile 소스 목록과 헤더 선언에 포함되지 않은 미사용/untracked 파일이므로 현재 push_swap 실행에는 연결되지 않습니다.

## 테스트 참고

- 현재 소스 전체는 `/tmp` 출력 대상으로 `-Wall -Werror -Wextra` 빌드에 성공했습니다.
- bonus checker 소스도 동일 옵션으로 빌드에 성공했습니다.
- 오류 확인을 위해 원본 프로젝트 소스는 변경하지 않았습니다.
