*This project has been created as part of the 42 curriculum by slim.*

# Push_swap & Checker

제한된 명령어 집합(`pa`, `pb`, `sa`, `sb`, `ss`, `ra`, `rb`, `rr`, `rra`, `rrb`, `rrr`)만을 사용하여 이중 스택(`Stack A`, `Stack B`)의 데이터를 최소한의 연산 횟수로 오름차순 정렬하는 C언어 정렬 프로젝트.

---

## 📝 프로젝트 개요 (Description)

**Push_swap**은 데이터의 크기와 무질서도(Entropy)에 따른 복잡도 분석, 스택 자료구조 활용, 그리고 적응형 알고리즘 선택을 다루는 42 경산 커리큘럼 프로젝트입니다. 명령줄 인자로 중복 없는 32비트 정수 배열을 입력받아, 스택 A를 오름차순(위쪽에 작은 값, 아래쪽에 큰 값)으로 정렬하고 스택 B는 비우는 최소한의 명령어 수열을 출력합니다.

또한, 보너스 타겟으로 제출된 명령어가 스택을 올바르게 정렬하는지 검증하는 독립적인 체커 프로그램(**Checker**)을 포함하고 있습니다.

### 주요 특징 (Key Features)
- **적응형 정렬 전략 (`--adaptive`, 기본값)**: 정렬 전 스택의 무질서도($0.0 \sim 1.0$)를 동적으로 측정하여 최적의 정렬 알고리즘을 자동 선택합니다.
- **다양한 정렬 전략 지원**: `--simple` (비용 기반 정렬), `--medium` (청크 기반 분할 정렬), `--complex` (3-Way 퀵 정렬) 제공.
- **명령어 버퍼 및 인라인 최적화**: 상쇄되거나 결합 가능한 연산(예: `ra` + `rra` $\rightarrow$ 제거, `ra` + `rb` $\rightarrow$ `rr`)을 자동 최적화합니다.
- **벤치마크 분석 모드 (`--bench`)**: 정렬에 사용된 명령어 수, 초기 무질서도, 정렬 시간 및 선택된 전략 정보를 출력합니다.
- **독립된 보너스 구조**: 체커 관련 소스 및 헤더가 `./bonus/` 및 `./bonus/include/` 하위에 완전 격리되어 있으며, 42 Norminette 규정을 100% 준수합니다.

---

## 💡 알고리즘 선택 및 당위성 (Algorithm Choices & Justification)

### 1. 소규모 정렬 ($N \le 3$)
- **알고리즘**: 하드코딩된 순열 조건 분기 (`three_sort`).
- **선택 이유**: 3개 이하 원소의 순열은 $3! = 6$ 가지 경우의 수만 존재합니다. 불필요한 스택 순회 없이 최대 2회 이하의 연산으로 정렬을 완료합니다.

### 2. Simple 전략 (`--simple`): 비용 기반 정렬 (Cost-Based Insertion Sort)
- **알고리즘**: 원소 이동에 필요한 회전 비용(`ra`/`rb`, `rra`/`rrb`, `rr`/`rrr`)을 다각도로 계산하여 최소 비용이 드는 원소를 위치에 맞게 탐욕적으로 정렬합니다.
- **선택 이유**: 데이터 크기가 작거나($N \le 5$) 초기 무질서도가 낮은 데이터(Disorder $< 0.2$)에서 최소 비용 탐색을 통해 효율적으로 정렬을 수행합니다.

### 3. Medium 전략 (`--medium`): 청크 기반 분할 정렬 (Chunk-Based Divide & Conquer)
- **알고리즘**:
  1. 전체 원소의 랭크(Rank)를 기준으로 $\sqrt{N}$ 개 청크로 분할합니다.
  2. A에서 B로 청크를 넘길 때, 랭크가 큰 청크는 B의 상단, 랭크가 작은 청크는 `rb`를 수행하여 B의 하단에 배치합니다.
  3. B 스택에 모인 원소 중 최댓값을 추적하여 A 스택으로 차례대로 꺼내옵니다 (`selection_sort_to_b`).
- **선택 이유**: 청크 단위로 나누어 상/하단으로 밀어 넣음으로써 복원 시 B 스택 내부의 최댓값 탐색 거리를 최소화하여 정렬 연산 횟수를 대폭 절감합니다.

### 4. Complex 전략 (`--complex`): 재귀 3-Way 퀵 정렬 (Recursive 3-Way Quick Sort)
- **알고리즘**:
  1. 현재 구간의 최소/최대 값을 찾아 2개의 피벗(`pivots[0]`, `pivots[1]`)을 설정합니다.
  2. 스택 A와 B 사이에서 피벗 2개를 기준으로 데이터를 3개 구간(Small, Mid, Large)으로 분할(Partitioning)합니다.
  3. 회전한 스택 위치를 되돌리는 `rewind_stack`을 수행한 후, 각 구간에 대해 상/하귀 재귀 호출(`complex_sort_helper_a`, `complex_sort_helper_b`)을 통해 정렬을 수행합니다.
- **선택 이유**: 이중 스택 상에서 피벗 2개를 활용하는 3-Way 퀵 정렬 구조를 통해 분할 깊이를 $O(\log_3 N)$으로 낮추어 난수 데이터셋에서도 빠른 정렬 속도를 보장합니다.

### 5. 적응형 정렬 자동 선택 (`--adaptive` / 기본값)
- **무질서도 (Disorder Metric)**: 정규화된 역위수(Inversion Pair) 비율 $D(A) = \frac{\text{인버전 수}}{\frac{N(N-1)}{2}}$ 로 계산됩니다.
- **전환 기준**:
  - $D(A) < 0.2$: Simple 전략 (낮은 무질서도, 최소 삽입)
  - $0.2 \le D(A) < 0.5$: Medium 전략 (중간 무질서도)
  - $D(A) \ge 0.5$: Complex 전략 (높은 무질서도, 3-Way 퀵 정렬)

---

## 🛠️ 사용 설명서 (Instructions)

### 컴파일 (Compilation)

프로젝트 루트의 `Makefile`을 통해 메인 빌드(`push_swap`) 및 보너스 체커(`checker`)를 컴파일합니다.

```bash
# push_swap 컴파일
make

# checker 보너스 컴파일
make bonus

# 전체 재컴파일
make re

# 생성된 객체 및 실행 파일 삭제
make fclean
```

### 실행 예시 (Usage Examples)

```bash
# 기본 실행 (자동 적응형 전략 적용)
./push_swap 4 67 3 87 23

# 명시적 정렬 전략 지정 실행
./push_swap --complex 4 67 3 87 23
./push_swap --medium 4 67 3 87 23
./push_swap --simple 4 67 3 87 23

# 벤치마크 진단 모드 실행
./push_swap --bench 4 67 3 87 23

# 보너스 체커를 통한 정렬 결과 검증
ARG="4 67 3 87 23"; ./push_swap $ARG | ./checker $ARG
# 검증 성공 시 'OK', 실패 시 'KO' 출력
```

---

## 참고 자료 및 AI 활용

### 참고 문헌 및 자료 
- [Donald Knuth - The Art of Computer Programming, Vol 3: Sorting and Searching](https://en.wikipedia.org/wiki/The_Art_of_Computer_Programming)
- [Dual-Pivot Quick Sort Algorithms](https://en.wikipedia.org/wiki/Quicksort#Dual-pivot_quicksort)

### AI 활용 내역

