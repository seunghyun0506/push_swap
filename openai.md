# 현재 확인된 오류

> 이 파일에는 현재 코드에서 확인된 오류와 명세 위반만 기록한다.
> 수정 제안은 `suggestions.md`, 테스트 내역은 `tests.md`에 기록한다.

## P0 - 결합 stack 연산 명세 불일치

관련 파일:

- `src/ft_stack/stack_swap.c`
- `src/ft_stack/stack_rotate.c`
- `src/ft_stack/stack_rrotate.c`
- `src/bonus/ft_stack/stack_swap_bonus.c`
- `src/bonus/ft_stack/stack_rotate_bonus.c`
- `src/bonus/ft_stack/stack_rrotate_bonus.c`

`ss`, `rr`, `rrr`가 양쪽 stack 모두 연산 가능한 경우에만 실행된다.
한쪽 stack만 연산 가능해도 해당 stack의 단일 연산은 실행되어야 한다.

```sh
printf 'ss\n' | ./checker_linux 2 1
# 공식 checker: OK
```

현재 자체 checker는 같은 입력에 대해 `KO`가 될 수 있다.

## P1 - operation buffer resize 실패 후 잘못된 capacity 유지

관련 파일:

- `src/op_buffer/op_buffer.c`

`resize_op_buffer()`가 malloc 전에 `capacity`를 두 배로 변경한다.
할당이 실패하면 기존 배열은 그대로인데 capacity만 증가한다.
이후 `store_op()`가 기존 배열의 범위를 넘어 쓸 수 있다.

## P1 - stack push 실패 처리 불완전

관련 파일:

- `src/ft_stack/stack_push.c`
- `src/bonus/ft_stack/stack_push_bonus.c`

`push_stack()`이 from에서 먼저 pop한 뒤 to에 push한다.
to가 가득 차 push가 실패해도 반환값을 확인하지 않아 데이터가 사라질 수 있다.
현재 push_swap의 정상 invariant에서는 발생 가능성이 낮지만 stack API의 실패 처리가 완전하지 않다.

또한 `push_stack_data()`의 실패 반환값이 `~data`라서 데이터 값에 따라 성공/실패 판단이 불명확하다.

## P1 - PDF의 허용 외부 함수와 `abs()` 사용 불일치

관련 파일:

- `src/sort/simple/simple_sort.c`
- `src/sort/medium/medium_sort_return.c`

현재 표준 라이브러리의 `abs()`를 사용한다.
PDF의 허용 외부 함수 목록에 맞추려면 자체 `ft_abs()` 또는 동일한 내부 로직을 사용해야 한다.

## P1 - Norm 오류

현재 `norminette`에서 다음 오류가 확인된다.

- `src/push_swap.c`: 함수 25줄 초과
- `libft/src/ft_sqrt.c`: 함수 25줄 초과
- `libft/src/ft_isspace.c`: 불필요한 탭
- `libft/src/ft_toupper.c`: typedef 및 정렬 오류

PDF는 bonus 파일까지 Norm 오류가 있으면 평가에 영향을 준다고 명시한다.

## P1 - README 필수 내용 누락

현재 `README.md`가 PDF가 요구하는 다음 내용을 충족하지 않는다.

- 첫 줄의 학습자 login
- Description
- Instructions
- Resources
- AI 사용 내역
- 두 학습자의 기여 내용
- 알고리즘 선택 및 복잡도 설명

## P1 - libft dependency 변수명 오류

관련 파일:

- `libft/Makefile`

실제 object 변수는 `OBJS`인데 dependency 변수는 `OBJ`를 사용한다.

```make
OBJS = ...
DEPS = $(OBJ:.o=.d)
```

따라서 libft의 `.d` 의존성이 정상적으로 관리되지 않는다.
