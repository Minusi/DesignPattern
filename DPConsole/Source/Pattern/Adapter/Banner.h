#pragma once

#include <string>
#include <iostream>



// 이전에 존재했던 명세(API)를 대표하는 클래스입니다.
// 개조되어야 할 대상(Adaptee) 클래스라고도 합니다.
class NBanner
{
private:
	std::string String;

public:
	// 입력된 문자열로 String을 초기화합니다.
	NBanner(std::string InString);

	// 가상 소멸자입니다.
	virtual ~NBanner();

	// 소괄호로 둘러싸인 문자열을 출력합니다.
	void ShowWithParen() const;

	// 애스터리스크로 둘러싸인 문자열을 출력합니다.
	void ShowWithAster() const;

};