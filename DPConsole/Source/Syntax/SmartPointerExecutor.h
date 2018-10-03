#pragma once

#include <iostream>
#include <string>
#include <memory>


#include "Pattern\IPatternExecutor.h"



class NSmartPointerExecutor : public IPatternExecutor
{
public:
	// 스마트포인터에 대한 여러 예제들을 C 스타일의 함수로
	// 소스 파일로 작성한 것을 이 클래스 멤버 함수에서 취합하여
	// 보여주는 기능을 제공합니다.
	// 즉, 여러 개의 예제들을 보여주는 메인의 대리자이면서 게시판이라
	// 할 수 있습니다.
	void ExecutePattern() override;
};