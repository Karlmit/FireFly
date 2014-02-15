#ifndef LTBL_UTILS_H
#define LTBL_UTILS_H

#include <string>

namespace ltbl
{
	const float pif = 3.1415926f;
	const float pifTimes2 = pif * 2.0f;

	template<class T> T Wrap(T val, T size)
	{
		if(val < 0)
			return val + size;

		if(val >= size)
			return val - size;

		return val;
	}

	float GetFloatVal(std::string strConvert);
}

#endif
