# Push Swap 프로젝트 대화 메모리

## 1. 이 문서의 목적

이 문서는 `/home/jaeclee/push_swap_01` 프로젝트에 관해 지금까지 사용자와 AI가 나눈 분석 및 설명의 맥락을 다른 세션에서도 이어가기 위한 인계 문서이다.

새 세션의 AI는 답변하기 전에 이 문서를 읽고 다음을 이해해야 한다.

- 사용자는 단순한 요약보다 코드의 호출 흐름, 포인터, 메모리 변화, 자료구조 상태를 머릿속으로 그릴 수 있는 상세한 설명을 원한다.
- 설명할 때 함수 이름과 파일 경로를 명확히 제시한다.
- 가능하면 임의 입력을 정하고 각 변수, 포인터, 리스트, 스택이 단계별로 어떻게 변하는지 도식화한다.
- 오류를 발견하면 임의로 소스를 수정하지 말고 사용자에게 알린다.
- 발견한 오류는 프로젝트 루트의 `error.md`에도 기록한다.
- 사용자가 명시적으로 수정 요청을 하기 전까지 원본 소스 수정은 금지한다.

> 주의: 일반적으로 새 AI 세션이 이 파일을 자동으로 읽는다고 보장할 수 없다. 새 세션을 시작할 때 사용자 또는 세션 초기 지침에서 `MEMORY.md`와 `error.md`를 먼저 읽으라고 요청하는 것이 가장 확실하다.

---

## 2. 프로젝트 위치와 성격

프로젝트 루트:

```text
/home/jaeclee/push_swap_01
```

42 `push_swap` 프로젝트이며 기본 기능 외에 다음 확장 요소가 있다.

- 원형 배열 기반 스택 라이브러리
- 여러 `argv` 문자열 안의 정수 파싱
- Simple / Medium / Complex 정렬 전략
- disorder 기반 Adaptive 전략
- 연산 명령 최적화 버퍼
- benchmark 출력
- bonus checker
- 자체 libft와 get_next_line

주요 디렉터리:

```text
include/                 공용 헤더
src/                     push_swap 본체
src/sort/simple/         Simple 알고리즘
src/sort/medium/         Medium 알고리즘
src/sort/complex/        Complex 알고리즘
src/op_buffer/           명령 버퍼
src/checker/             bonus checker
ft_stack/                원형 배열 스택 라이브러리
libft/                   자체 libft 및 GNL
```

---

## 3. 사용자가 최초 요청한 분석 범위

사용자는 프로젝트를 하나도 빠짐없이 상세히 분석해 달라고 요청했다. 특히 다음 구분을 원했다.

1. 파서
2. 스택
3. Simple 알고리즘
4. Medium 알고리즘
5. Complex 알고리즘
6. disorder
7. benchmark
8. op buffer
9. checker
10. libft, GNL, merge sort, Makefile 및 기타 프로젝트 영역
11. `main.c`에서 인자를 받은 뒤 프로그램이 반환할 때까지의 전체 흐름

오류가 있으면 직접 수정하지 말고 알린 다음 `error.md`에 기록해 달라는 조건이 있었다.

이 조건에 따라 프로젝트 루트에 다음 파일이 만들어져 있다.

```text
error.md
```

원본 소스는 수정하지 않았고, 오류 기록 문서만 생성·갱신했다.

---

## 4. 전체 실행 흐름 요약

`src/main.c` 기준 흐름:

```text
main
 ├─ argc <= 1이면 0 반환
 ├─ init_push_swap_stat
 │   └─ op buffer 초기화
 ├─ parse_flag
 ├─ parse_stack
 │   ├─ parse_integers
 │   │   ├─ ft_strtoi
 │   │   └─ add_node
 │   ├─ stack_a / stack_b / sorted 할당
 │   ├─ list_to_stack
 │   └─ merge_sort(sorted)
 ├─ check_duplicate
 ├─ is_sorted
 ├─ sort
 │   ├─ compute_disorder
 │   └─ Simple / Medium / Complex 선택
 ├─ print_op_buffer (stdout)
 ├─ print_bench_info (활성 시 stderr)
 ├─ free_resources
 └─ 0 반환
```

`t_push_swap_stat`은 인자, 파싱 인덱스, 옵션, 두 스택, 정렬 배열, 명령 버퍼, disorder와 선택 전략을 하나로 묶어 전달한다.

Adaptive 선택 기준:

```text
disorder < 0.2 → Simple
disorder < 0.5 → Medium
그 외          → Complex
```

---

## 5. op buffer에 관한 기존 대화

사용자는 상태 초기화에서 “`t_op` 32개를 저장하도록 할당한다”는 표현을 자세히 질문했다.

관련 구조:

```c
typedef struct s_op_buffer
{
    t_op *arr;
    int  idx;
    int  capacity;
} t_op_buffer;
```

초기화:

```c
buffer->arr = malloc(sizeof(t_op) * 32);
buffer->idx = 0;
buffer->capacity = 32;
```

의미:

- 문자열 `"sa\n"`, `"pb\n"`를 저장하는 것이 아니다.
- `OP_SA`, `OP_PB`, `OP_RA` 같은 enum 값 하나가 명령 하나를 나타낸다.
- `arr[0]`부터 `arr[31]`까지 총 32개의 명령 값을 저장할 수 있다.
- `idx`는 현재 저장된 명령 수이자 다음 저장 위치다.
- 32개를 초과하면 `32 → 64 → 128 → ...` 형태로 두 배 확장한다.
- 32는 명세상 고정된 값이 아니라 개발자가 선택한 임의의 초기 용량이다.
- 32를 택한 이유는 작은 메모리 사용량과 재할당 횟수 사이의 일반적인 절충으로 해석할 수 있지만 코드에는 선택 근거가 명시돼 있지 않다.
- 일반적인 4바이트 enum 환경에서는 배열이 약 128바이트이고, 64비트 환경의 관리 구조체 약 16바이트를 더하면 초기 할당은 총 약 144바이트다.

버퍼는 명령을 바로 출력하지 않고 저장하여 다음 최적화를 수행한다.

```text
ra + rra  → 제거
sa + sa   → 제거
pa + pb   → 제거
ra + rb   → rr
rra + rrb → rrr
sa + sb   → ss
```

정렬 알고리즘은 실제 스택을 먼저 변경하고, 수행한 연산을 버퍼에 기록한다. 정렬 완료 후 enum을 명령 문자열로 변환해 stdout으로 출력한다.

---

## 6. parse_stack → parse_integers → add_node에 관한 기존 대화

사용자는 이 호출 흐름과 포인터 관계를 머릿속으로 그리기 어렵다고 했다. 다음 예시로 상세 설명했다.

```sh
./push_swap "8 3" "7" "1 6"
```

인자:

```text
argv[0] = "./push_swap"
argv[1] = "8 3"
argv[2] = "7"
argv[3] = "1 6"
```

### 6.1 각 함수의 역할

```text
parse_stack
  → argv를 하나씩 선택하고 전체 정수 개수를 누적

parse_integers
  → argv 하나의 문자열 안에서 공백으로 구분된 정수를 반복해서 읽음

ft_strtoi
  → 현재 위치부터 정수를 읽고, 읽기가 끝난 주소를 pos로 반환

add_node
  → int 저장 공간과 t_list 노드를 각각 할당하고 리스트 맨 앞에 삽입
```

### 6.2 개수 변수 구분

- `parse_stack()`의 `cnt`: 모든 argv에서 읽은 정수의 총개수
- `parse_stack()`의 `tmp`: 현재 argv에서 읽은 정수 개수
- `parse_integers()`의 `cnt`: 현재 문자열 하나에서 읽은 정수 개수

예제에서는:

```text
"8 3" → tmp 2, 전체 cnt 2
"7"   → tmp 1, 전체 cnt 3
"1 6" → tmp 2, 전체 cnt 5
```

### 6.3 `&list`와 이중 포인터

`parse_stack()`은 다음과 같이 호출한다.

```c
parse_integers(&list, stat->argv[stat->i]);
```

- `list`: 첫 노드의 주소
- `&list`: 첫 노드의 주소를 보관하는 변수 자체의 주소
- `t_list **lst`: 호출자 쪽 `list` 값을 직접 변경하기 위해 필요

`add_node()` 안의 `ft_lstadd_front(lst, tmp)`는 개념적으로 다음을 수행한다.

```c
tmp->next = *lst;
*lst = tmp;
```

따라서 호출자 `parse_stack()`의 `list`가 새 노드를 가리키게 된다.

### 6.4 add_node의 두 번 할당

```c
tmp_int = malloc(sizeof(int));
*tmp_int = num;
tmp = ft_lstnew(tmp_int);
ft_lstadd_front(lst, tmp);
```

메모리 관계:

```text
t_list 노드                     별도 int 데이터
+------------------+           +-----+
| content ----------+--------->| num |
| next ------------ |           +-----+
+------------------+
```

노드 안에 int가 직접 들어가는 것이 아니라 `content`가 별도 할당된 int를 가리킨다.

### 6.5 리스트 순서 변화

`ft_lstadd_front()`를 사용하므로 입력 전체의 역순 리스트가 만들어진다.

```text
입력: 8 3 7 1 6

8 추가:       8
3 추가:       3 → 8
7 추가:       7 → 3 → 8
1 추가:       1 → 7 → 3 → 8
6 추가:       6 → 1 → 7 → 3 → 8
```

하지만 `list_to_stack()`이 리스트의 앞에서부터 스택에 push하므로 한 번 더 뒤집힌다.

```text
push 순서: 6, 1, 7, 3, 8
최종 A:    top → 8, 3, 7, 1, 6 → bottom
```

따라서 원래 입력 순서가 복원된다.

`sorted` 배열도 뒤 인덱스부터 채워 원본 순서가 되며, 이후 merge sort로 정렬된다.

```text
list:       6 1 7 3 8
sorted 전:  8 3 7 1 6
sorted 후:  1 3 6 7 8
```

### 6.6 pos를 이용한 토큰 검증

```c
num = ft_strtoi(str, &pos);
```

예: `"8 3"`

```text
8 3\0
↑ ↑
str
  pos (8을 읽고 난 뒤 공백)
```

검사:

```c
if (str == pos || (*pos != '\0' && !ft_isspace(*pos)))
```

- `str == pos`: 숫자를 전혀 읽지 못함
- 숫자 뒤 문자가 문자열 끝도 공백도 아님: `12abc` 같은 잘못된 토큰

오류가 나면 `ft_lstclear(lst, free)`로 이전 argv에서 만든 노드까지 포함한 전체 임시 리스트를 해제하고 `-1`을 반환한다.

---

## 7. 알고리즘 요약

### 7.1 Simple

관련 파일:

```text
src/sort/simple/simple_sort.c
src/sort/simple/simple_sort_cost.c
src/sort/simple/align.c
```

흐름:

```text
A에 하나만 남기고 모두 B로 pb
→ B top을 A의 원형 정렬 상태에 맞는 위치로 삽입
→ 가까운 방향으로 A 회전
→ pa
→ 모두 반환 후 최솟값을 A top으로 정렬
```

의도 복잡도: `O(n²)`.

### 7.2 Medium

관련 파일:

```text
src/sort/medium/medium_sort.c
src/sort/medium/medium_sort_divide.c
src/sort/medium/medium_sort_return.c
```

흐름:

```text
정렬 배열에서 값의 rank 계산
→ 약 √n 청크 구성
→ 두 청크씩 A에서 B로 분배
→ 상위 3개는 A에 남겨 small_sort
→ B에서 큰 청크부터, 각 청크의 최댓값부터 A로 pa
```

의도한 연산 복잡도: `O(n√n)`.

### 7.3 Complex

관련 파일:

```text
src/sort/complex/complex_sort.c
src/sort/complex/complex_sort_util.c
src/sort/complex/complex_sort_small.c
src/sort/three_sort.c
```

흐름:

```text
현재 부분 구간 rank 범위에서 1/3, 2/3 피벗 선택
→ A와 B를 3개 그룹으로 분할
→ 회전한 부분 rewind
→ A용/B용 재귀 helper가 서로 호출
→ 크기 3 이하에서 small_sort로 종료
```

의도한 연산 복잡도: `O(n log n)`.

---

## 8. 스택 구현 요약

`t_stack`은 연결 리스트가 아니라 `capacity + 1` 크기의 원형 배열이다.

```c
typedef struct s_stack
{
    int *datas;
    int capacity;
    int top_index;
    int bottom_index;
} t_stack;
```

크기 계산:

```c
(top_index - bottom_index + capacity + 1) % (capacity + 1)
```

논리적으로 top에서 bottom으로 이동할 때 `prev_idx()`를 쓴다.

연산:

```text
swap_stack    → top 두 개 교환
push_stack    → from top pop 후 to top push
rotate_stack  → top을 bottom으로
rrotate_stack → bottom을 top으로
```

원형 인덱스와 경계 데이터 복사를 사용하여 rotate/reverse rotate를 전체 배열 이동 없이 처리한다.

---

## 9. disorder와 benchmark

`compute_disorder()`는 모든 `(i, j), i < j` 쌍에서 앞 값이 뒤 값보다 큰 inversion 수를 센다.

```text
disorder = inversion 수 / (n × (n - 1) / 2)
```

- 0.0: 완전 정렬
- 1.0: 완전 역순
- 계산 복잡도: `O(n²)`

benchmark는 stderr에 다음을 출력한다.

```text
초기 disorder 백분율
선택된 전략
최종 op buffer 명령 수
각 명령별 개수
```

명령은 stdout, benchmark는 stderr이므로 파이프에서 분리된다.

---

## 10. 확인된 주요 오류

상세 내용과 재현법은 반드시 `error.md`를 읽는다. 현재 주요 항목은 다음과 같다.

### 10.1 3원소 정렬 실패

`src/sort/three_sort.c::three_sort_asc_dispatch()`의 두 회전 방향이 뒤바뀐 것으로 확인됐다.

```text
[1, 2, 0] --ra-->  [2, 0, 1] 실패
[2, 0, 1] --rra--> [1, 2, 0] 실패
```

재현:

```sh
./push_swap --medium 1 2 0 | ./checker_linux 1 2 0
# KO
```

이 함수가 재귀 종료에 사용되므로 Medium과 Complex에 모두 영향을 준다.

### 10.2 Complex 다수 입력 실패

예:

```sh
./push_swap --complex 0 1 3 4 2 | ./checker_linux 0 1 3 4 2
# KO
```

상당수는 3원소 정렬 오류가 전파된 형태로 관찰됐다. 결합 회전 오류도 영향을 줄 수 있다.

### 10.3 정수 범위 오버플로

`libft/src/ft_strtoi.c`는 `INT_MIN~INT_MAX` 범위를 검사하지 않는다.

```text
2147483648
-2147483649
매우 긴 숫자 문자열
```

에서 signed integer overflow(UBSan 확인)가 발생하고 오류로 거부되지 않을 수 있다.

### 10.4 부호만 있는 토큰 허용

상세 파서 분석 중 추가 발견되어 `error.md`에 기록했다.

```text
"+"   → 0으로 허용
"-"   → 0으로 허용
"+ 1" → 0, 1로 허용
"- 1" → 0, 1로 허용
```

부호 뒤 숫자가 한 자리 이상 있는지 검사하지 않기 때문이다.

### 10.5 `ss`, `rr`, `rrr` 명세 불일치

현재 두 스택 함수는 양쪽 스택 모두 원소가 2개 이상일 때만 결합 연산을 수행한다. 명세상 한쪽만 가능해도 가능한 쪽은 실행해야 한다.

```sh
printf 'ss\n' | 자체 checker 2 1
# KO

printf 'ss\n' | checker_linux 2 1
# OK
```

### 10.6 메모리/할당 오류 경로

- `parse_flag()` 또는 `parse_stack()` 실패 시 초기 op buffer 누수
- LeakSanitizer에서 일반 환경 기준 총 144바이트 확인
- 스택 일부 할당 실패 시 `datas` 내부 배열 누수 가능
- op buffer 초기화 실패를 검사하지 않아 `--bench`에서 NULL 역참조 가능
- merge sort 임시 배열 할당 실패를 호출자에게 전달하지 않음

### 10.7 기타

- 이미 정렬된 입력은 bench 출력 전에 조기 반환
- 저장된 `push_swap` 바이너리가 현재 소스보다 오래되어 동작이 다름
- `compile_commands.json`이 현재 소스 목록과 불일치
- `libft/Makefile`의 `OBJ`/`OBJS` 의존성 변수 오류
- `ft_stack/Makefile`의 `re` 규칙 오류
- 미사용 `libft/src/ft_abs.c`에서 `INT_MIN` 부호 반전 시 잠재적 overflow

---

## 11. 수행한 테스트 방식

원본 프로젝트를 수정하지 않기 위해 테스트 실행 파일과 스크립트는 `/tmp`에 생성했다.

확인 사항:

- 현재 소스 전체를 `-Wall -Werror -Wextra`로 별도 빌드 성공
- bonus checker 소스도 별도 빌드 성공
- ASan/UBSan/LeakSanitizer로 오버플로와 누수 확인
- 순열 테스트에서 Medium/Complex 실패 확인
- 공식 `checker_linux`와 자체 checker의 결합 명령 판정 차이 확인

프로젝트 루트의 기존 `push_swap`은 현재 소스와 빌드 시점이 다르므로, 소스의 현재 동작을 검증할 때 그대로 신뢰하면 안 된다.

---

## 12. 향후 대화 방식

새 세션에서는 사용자의 질문에 따라 필요한 파일을 다시 읽고, 이 문서의 내용을 현재 소스와 대조해야 한다. 이 문서는 인계용 요약이며 소스 자체를 대체하지 않는다.

설명 방식 권장:

1. 먼저 함수의 책임을 한 문장으로 정의
2. 호출자와 피호출자 관계 설명
3. 매개변수의 타입과 포인터 단계 설명
4. 구체적 입력 하나를 선택
5. 각 반복 시점의 지역 변수 상태 표시
6. 리스트/스택/배열을 ASCII 그림으로 표현
7. 정상 흐름과 오류 흐름을 분리
8. 마지막에 핵심 요약 제공

예를 들어 포인터 질문에는 다음을 분명히 구분한다.

```text
list   : 첫 노드 주소
a&list : 첫 노드 주소를 담은 변수의 주소
*lst   : 호출자 list에 저장된 첫 노드 주소
**lst  : 첫 노드 자체를 포인터 문맥에서 접근한 결과
```

실제 표기에서는 오타 없이 `&list`라고 설명한다.

오류 발견 시:

1. 재현 가능한지 확인
2. 사용자에게 명확히 알림
3. 원본 소스는 수정하지 않음
4. `error.md`에 새 항목 추가
5. 테스트용 산출물은 가능하면 `/tmp` 사용

사용자가 이후 명시적으로 수정 권한을 주면 그때 수정 범위와 우선순위를 다시 확인한다.
