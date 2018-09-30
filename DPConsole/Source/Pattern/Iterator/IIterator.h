#pragma once

#include <combaseapi.h>


template<typename T, typename U>
interface IIterator
{
public:

	// 다음 순회할 대상이 존재하는지 확인합니다.
	virtual bool HasNext() = 0;

	// 다음 순회할 대상으로 이동합니다.
	virtual U Next() = 0;

};