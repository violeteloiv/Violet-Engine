/////////////////
///
/// vtpch.h
/// Violet McAllister
/// July 1st, 2022
/// Updated: July 23rd, 2022
///
/// Precompiled Header to allow for faster compilation.
///
/////////////////

#ifndef __VIOLET_ENGINE_PCH_H_INCLUDED__
#define __VIOLET_ENGINE_PCH_H_INCLUDED__

#include "Violet/Core/PlatformDetection.h"

#ifdef VT_PLATFORM_WINDOWS
	#ifndef NOMINMAX
		// See github.com/skypjack/entt/wiki/Frequently-Asked-Questions#warning-c4003-the-min-the-max-and-the-macro
		#define NOMINMAX
	#endif
#endif

#include <iostream>
#include <memory>
#include <utility>
#include <algorithm>
#include <functional>

#include <string>
#include <sstream>
#include <array>
#include <vector>
#include <unordered_map>
#include <unordered_set>

#include "Violet/Core/Base.h"
#include "Violet/Core/Log.h"
#include "Violet/Debug/Instrumentor.h"

#ifdef VT_PLATFORM_WINDOWS
	#include <Windows.h>
#endif // VT_PLATFORM_WINDOWS

#endif // __VIOLET_ENGINE_PCH_H_INCLUDED__
