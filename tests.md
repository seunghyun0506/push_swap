# 테스트 내역

## 빌드

```sh
make
make bonus
```

결과: 성공

컴파일 옵션:

```text
-Wall -Wextra -Werror
```

## 정렬 테스트

Simple, Medium, Complex, Adaptive에 대해 다음을 확인했다.

- 크기 2~7의 모든 순열
- 크기 8~200의 무작위 입력
- push_swap 출력과 checker 결과 비교

결과: 현재 테스트 범위에서 정렬 성공

## Benchmark

정렬된 입력:

```sh
./push_swap --simple --bench 1 2 3
```

확인 결과:

- stdout 명령 수: 0
- stderr benchmark 출력: 정상
- total_ops: 0

숫자 없이 flag만 있는 입력:

```sh
./push_swap --simple --bench
```

확인 결과:

- stdout: 빈 출력
- stderr: 빈 출력
- 정상 종료

## 파싱 (수정 전)

다음 입력이 수정 전 `ft_strtoi()`에서 오류로 거부되지 않는 현상을 확인했다.

```sh
./push_swap +
./push_swap -
./push_swap 2147483648
./push_swap -2147483649
```

`str_to_int()` 적용 후 위 입력들은 `Error`로 처리되며, `-2147483648`과 `2147483647`은 정상 처리된다.

## Medium 경계값

```sh
./push_swap --medium 1 2 3 -2147483648 \
    | ./checker_linux 1 2 3 -2147483648
```

수정 전 결과: `KO`
수정 후 결과: `OK`

## 결합 연산

```sh
printf 'ss\n' | ./checker_linux 2 1
printf 'rr\n' | ./checker_linux 2 1
printf 'rrr\n' | ./checker_linux 1 2
```

공식 checker는 각 단일 연산이 가능한 쪽만 실행하지만, 현재 자체 checker와 결과가 다르다.

## Norm

```sh
norminette src include libft/src
```

확인된 오류:

- `src/push_swap.c`: TOO_MANY_LINES
- `libft/src/ft_sqrt.c`: TOO_MANY_LINES
- `libft/src/ft_isspace.c`: TOO_MANY_TABS_FUNC
- `libft/src/ft_toupper.c`: typedef/정렬 관련 오류
