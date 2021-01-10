/* date = January 9th 2021 9:22 am */

#ifndef PCH_H
#define PCH_H

#ifdef _MSC_VER

#pragma warning(push, 0)

#else

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Weverything"

#endif

#include <Windows.h>
#include <d2d1.h>
#include <dwrite.h>

#ifdef _MSC_VER

#pragma warning(pop)

#else

#pragma clang diagnostic pop

#endif

#endif //PCH_H
