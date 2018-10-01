#pragma once

#include <combaseapi.h>
#include <string>



// 새로운 명세(API)에 해당하는 Print 인터페이스입니다.
// 타겟 클래스라고도 부를 수 있겠습니다.
interface IPrint
{
public:
	// 소괄호에 감싸서 문자열을 출력합니다.
	virtual void PrintWeak() const = 0;

	// 애스터리스크에 감싸서 문자열을 출력합니다.
	virtual void PrintStrong() const = 0;

};