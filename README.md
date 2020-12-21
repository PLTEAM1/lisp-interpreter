# lisp-interpreter

LISP Interpreter 구현

## Interpreter 분석

LISP은 프로그래밍 언어의 계열로서, 오랜 역사와 독특하게 괄호를 사용하는
문법으로 유명하다. 1958년에 초안이 작성된 이 언어는 현재 널리 사용되는 포트란에 이어 두 번째로 오래된 고급 프로그래밍 언어이다.
LISP 라는 이름 자체는 "LISt Processing"(리스트 프로세싱)의 줄임말이다. 연결 리스트는 LISP의 주요 자료구조 중 하나로서, LISP 코드는 그 자체로 하나의 리스트이다.
전체 프로그램 코드는 S-표현식 이나 괄호로 묶인 리스트로 작성되며, 함수 호출의 경우 함수 이름 혹은 연산자가 첫 번째로 위치하여 피연산자가 이어 위치하게 된다.

- Common LISP 예제 코드

<img width="550" alt="스크린샷 2020-12-21 오후 5 51 08" src="https://user-images.githubusercontent.com/33109677/102757762-268f5000-43b5-11eb-82dc-50496e149bc6.png">

## Interpreter 설계

![Untitled Diagram-Page-10](https://user-images.githubusercontent.com/33109677/102756910-e1b6e980-43b3-11eb-9580-bfb3db58dfc3.png)

## Interpreter 구현

Tech Stack : C++

#### List Class

LISP 코드는 그 자체로 하나의 리스트이다. Interpreter를 사용하는 동안에, 사용자에게 보여 줄 수행 결과들 또한 리스트로 저장하고, 이용하기 위해서 Linked List 클래스를 구현하였다.

#### Lexer Class 

입력받은 LISP 코드를 토큰화 하여 반환하는 Lexer 클래스를 구현하였다.

#### Parser Class

입력받은 토큰의 syntax를 확인하고, 해당 함수를 호출하여 결과값을 반환하는 Parser 클래스를 구현하였다.

#### Arithmetic Class

Interpreter 사칙연산 함수를 담당하는 Arithmetic 클래스를 구현하였다.
기본적으로 사칙연산의 모든 파라미터는 정수, 실수여야 한다.
덧셈, 뺄셈, 곱셈은 예외가 없지만, 나눗셈은 0으로 나누는 경우 예외처리를 해주도록 구현 하였다.

#### Basic Class

Interpreter 기본 함수를 담당하는 Basic 클래스를 구현하였다.
(SETQ, LIST, CAR, CDR, NTH, CONS, REVERSE, APPEND, LENGTH, MEMBER, ASSOC, REMOVE, SUBST)

#### Predicate Class

Interpreter Predicate 함수를 담당하는 Predicate 클래스를 구현하였다.
(ATOM, NULL, NUMBERP, ZEROP, MINUSP, EQUAL, <, >=, STRINGP)

#### Conditional Class

Interpreter 조건 함수를 담당하는 Conditional 클래스를 구현하였다.
(IF, COND)

#### Exception Class

Interpreter의 여러 예외처리를 위한 Exception 클래스를 구현하였다.

## Interpreter 구현 결과
