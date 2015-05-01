테스팅을 실습으로 진행하겠음.
=============================

-	새 슬라이드.
-	함수 점검하기
	-	호출해보기

```cpp
#include <iostream>

using namespace std;

int abs(int n);

int main() {
  if (abs(-1) == 1) cout << "성공!" << endl;
  else cout << "실패!..." << endl;
}

OR

int n;
cin >> n;
cout << abs(n);
```

-	굳이 main 으로 안 짜더라도 자동으로 테스트해줬으면 좋겠다
-	→ 단위 테스트를 자동화
-	→ JUnit (이클립스 기본 플러그인)

JUnit 기본
----------

-	기본 : AssertEquals() 가 기본.
-	`@Test` 가 문법
-	위의 C++ 코드와 결론적으로는 같은 역할.

```java
assertEquals("failure - not abs", n, abs(n));
```

```java
public class AssertTests {
  @Test
  public void testAssertArrayEquals() {
    byte[] expected = "trial".getBytes();
    byte[] actual = "trial".getBytes();

    assertArrayEquals("failure - byte arrays not same", expected, actual);
  }

  @Test
  public void testAssertEquals() {
    assertEquals("Failure - strings not same", 5l, 5l);
  }
}
```

-	함수의 존재 알아두기
	-	`assertEquals("오류출력", 예상, 실제)`
	-	`assertArrayEquals(위와동일)`
	-	`assertTrue("오류출력",실제)`
	-	`assertFalse("오류출력", 실제)`
	-	`assertNull("오류출력", 실제)`
	-	`assertNotNull("오류출력", 실제)`
	-	`assertSame("오류출력", A객체, B객체)`
	-	`assertNotSame("오류출력")`
	-	`assertThat("출력", 복잡한 조건)` - 복잡한 조건인 경우
	-	1 :
	-	2 :
	-	3 :
-	coverage 라는 것. : 소스코드에서 몇 퍼센트의 길을 실제로 지나갔는지 보여주는 도구
	-	EclEmma

실습
----

-	eclispe 를 연다, 새 프로젝트
-	메뉴의 버튼과 coverage 에 대한 설명
-	충분한 테스트는 사실상 불가
-	1. 코드
-	2. test case 파일
-	3. test suite 파일
-	만능은 아니지만 테스트를 자동화하는데 도움이 될 수 있음.

---

-	중간값을 위한 테스트케이스를 만들어보세요. 대체 몇 개가 필요할까?
-	어떻게 할까.
-	EclEmma의 실행. ← 코드의 coverage 보기
	-	median 함수의 모든 루트 테스트 : 적어도 6개 : return이 6개
	-	지금 하고있는 것 : 테스트 케이스의 설계

---

휴식

---

-	median 에 번호를 붙여보세요
	-	else에는 안 붙고, 닫는 괄호에는 안 붙는데, 함수의 마지막 괄호에는 붙는다 ← 함수의 종료
		-	→ 함수의 실행되는 부분

```java

public class TheClass {
	public static int median(int a, int b, int c) {
		if (a <= b) {			// 1
			if (b <= c)			// 2
				return b;		// 3
			else if (a <= c)		// 4
				return c;		// 5
			else
				return a;		// 6
		}
		else {
			if (a <= c)			// 7
				return a;		// 8
			else if (b <= c)		// 9
				return c;		// 10
			else
				return b;		// 11
		}
	}
}// 12
```

-	뭔 그래프그림. (flow graph)
-	23장 605p

### 23.3.3 구조 시험

-	테스트 시험을 구현하는 기법
-	블랙박스 시험과 대조 : 화이트박스, 유리상자, 투명상자 실험
	-	구조단위 시험 방법 : 내부 구조를 보지 않고 시험하 9
-	1 → Node 갯수 : 3, Edge 갯수 : 4 → 조합을 생ㅐ=랠해제난 ㅡ얃- ← 뭐라고 쓴 거지????
-	경로 조합은 무한하기에 그걸 다 테스트하기 어렵다 →

---

-	Cyclomatic complexity : 사이클로매틱 복잡도 : 프로그램의 경로 갯수
	-	단순 조건 갯수 + 1
		-	단순 조건 = and 나 or 같은 연결자가 없는 조건들
		-	and, or 의 경우, 그 사이의 것들을 각각 하나로 생각해야
	-	(플로우 그래프의) 엣지 갯수 - 노드 갯수
-	switch 구문은 어떻게 셀까?
	-	복합 조건의 경로 갯수 세기와 관련됨.

```cpp
int monthLength(int m) {
  switch (m) {
    case 2:
      return 28;
    case 1: case 3: case 5: case 7:
    case 8: case 10: case 12:
      return 31;
    case 4: case 6: case 9: case 11:
      return 30;
    default:
      return 0;
  }
}
```

제 22장 : 증명과 검증 (V & V : Verification and Validation)
===========================================================

-	둘은 다르다
	-	validation (검증) : 올바른 제품을 생성하고 있는가
		-	→ 가치있는, 필요한 프로덕트를 만들고 있느냐
	-	verification (증명) : 제품을 올바르게 생성하고 있는가
		-	→ Spec과 일치하는가
-	V & V 프로세스의 두 분석방법
	1.	Software Inspection 소프트웨어 검사 ← 이클립스 플로그인으로도 있음
		-	정적
		-	실행하지는 않는 것들
		-	소프트웨어의 어떤 표현도 검사 대상이 될 수 있음
		-	버그를 잡을수는 없다, 성능을 확인할수는 없다 → 프로토타입을 만든다
			-	UI의 프로토타입
			-	메시지 프로토콜의 프로토타입 등 → 모형을 가지고 실험하는 것이 중요
	2.	Software Testing 소프트웨어 실험
		-	실행중에 나오는 오류
-	책에 안 나오는 얘기
	-	리퀘스트를 발생시키는 장비도 있음 ← 매우 비쌈 (기록해놨다 발생)
-	두 가지 시험 : 목적에 따라 분류
	-	검증 시험 (validation testing)
	-	테스팅? - 결점 시험 (defect testing)

22.1 증명과 검증 계획 수립
--------------------------

-	책 버리지 않는 걸 추천.
-	필요한 부분이지만 지금은 필요 없으므로 통과

22.2 소프트웨어 검사
--------------------

> 검사에 대해서 얘기했죠~ 하고넘어감
