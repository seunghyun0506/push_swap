# 수정 제안

> 현재 오류가 아닌 구조·가독성·성능 개선 제안이다.
> 실제 오류는 `openai.md`, 테스트 내역은 `tests.md`를 참고한다.

## 우선순위

### 1단계

- `ss`, `rr`, `rrr`의 양쪽 연산을 독립적으로 처리
- operation buffer resize를 새 배열 할당 성공 후 commit하는 구조로 변경

### 2단계

- `push_stack()`이 destination push 실패를 복구하도록 변경
- `push_stack_data()`의 반환값을 명확한 성공/실패 규약으로 변경
- stack API에 NULL 및 capacity 검증 추가
- parser의 임시 list 및 정수별 할당 수 줄이기

### 3단계

- `t_op`의 `OP_COUNT` 도입
- `names[13]`, `counts[13]` 등의 하드코딩 제거
- 정렬 알고리즘과 operation 기록을 공통 wrapper로 통합
- Medium/Complex에서 rank를 사전 계산
- 사용하지 않는 함수 인자와 중복 prototype 정리
- normal/bonus stack 구현 통합 가능성 검토
- `libft`와 root Makefile의 `CC`, flags, dependency 관리 통일
- checker에서 사용하지 않는 operation buffer 할당 제거
- 공용 헤더와 내부 구현 헤더의 의존성 단순화

## 참고

- `free_resources()`의 mandatory/bonus 중복은 현재 별도 실행 파일과 `_bonus.c` 구조에 따른 의도된 중복으로 본다.
- `compute_disorder()`는 PDF의 mandatory 요구사항에 따른 구현이므로 수정 대상이 아니다.
- `ft_sqrt()`는 표준 `sqrt()`를 사용할 수 없는 환경에서 자체 구현한 함수이므로, 표준 라이브러리 사용을 권장하는 제안은 하지 않는다.
