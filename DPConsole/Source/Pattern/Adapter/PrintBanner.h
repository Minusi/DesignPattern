#pragma once

#include <string>
#include <memory>

#include "IPrint.h"
#include "Banner.h"


// Banner 클래스의 구현을 IPrint 인터페이스에 맞춥니다
class NPrintBanner : public IPrint
{
private:
	std::unique_ptr<NBanner> Banner;

public:
	NPrintBanner(std::string InString);


	/* IPrint 인터페이스 구현 */

	// 소괄호에 감싸서 문자열을 출력합니다.
	void PrintWeak() const override;

	// 애스터리스크에 감싸서 문자열을 출력합니다.
	void PrintStrong() const override;
};