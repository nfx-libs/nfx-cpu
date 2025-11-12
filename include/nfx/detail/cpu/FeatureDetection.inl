/*
 * MIT License
 *
 * Copyright (c) 2025 nfx
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

/**
 * @file FeatureDetection.inl
 * @brief Implementation of CPU feature detection functions
 * @details Implements SSE4.2, AVX, and AVX2 detection using CPUID instructions with static caching
 */

#if defined( __GNUC__ ) || defined( __clang__ )
#	include <cpuid.h>
#endif
#if defined( _MSC_VER )
#	include <intrin.h>
#endif

#include <array>
#include <cassert>

namespace nfx::cpu
{
	//=====================================================================
	// CPU feature detection
	//=====================================================================

	namespace internal
	{
		constexpr int CPUID_FEATURE_INFO_LEAF = 1;
		constexpr int CPUID_EXTENDED_FEATURES_LEAF = 7;

		constexpr int ECX_SSE42_BIT = 20;
		constexpr int ECX_AVX_BIT = 28;
		constexpr int ECX_OSXSAVE_BIT = 27;
		constexpr int EBX_AVX2_BIT = 5;
	} // namespace internal

	//----------------------------------------------
	// SSE4.2 Detection
	//----------------------------------------------

	inline bool hasSse42Support() noexcept
	{
		static const bool s_hasSse42 = []() {
			bool hasSupport = false;
#if defined( __GNUC__ ) || defined( __clang__ )
			unsigned int eax, ebx, ecx, edx;
			if ( __get_cpuid( internal::CPUID_FEATURE_INFO_LEAF, &eax, &ebx, &ecx, &edx ) )
			{
				hasSupport = ( ecx & ( 1 << internal::ECX_SSE42_BIT ) ) != 0; // ECX bit 20 = SSE4.2
			}
#elif defined( _MSC_VER )
			std::array<int, 4> cpuInfo{};
			__cpuid( cpuInfo.data(), internal::CPUID_FEATURE_INFO_LEAF );
			hasSupport = ( cpuInfo[2] & ( 1 << internal::ECX_SSE42_BIT ) ) != 0; // ECX bit 20 = SSE4.2
#endif
			return hasSupport;
		}();

		return s_hasSse42;
	}

	//----------------------------------------------
	// AVX Detection
	//----------------------------------------------

	inline bool hasAvxSupport() noexcept
	{
		static const bool s_hasAvx = []() {
			bool hasSupport = false;
			bool hasXsave = false;

#if defined( __GNUC__ ) || defined( __clang__ )
			unsigned int eax, ebx, ecx, edx;
			if ( __get_cpuid( internal::CPUID_FEATURE_INFO_LEAF, &eax, &ebx, &ecx, &edx ) )
			{
				hasSupport = ( ecx & ( 1 << internal::ECX_AVX_BIT ) ) != 0;	  // ECX bit 28 = AVX
				hasXsave = ( ecx & ( 1 << internal::ECX_OSXSAVE_BIT ) ) != 0; // ECX bit 27 = OSXSAVE
			}
#elif defined( _MSC_VER )
			std::array<int, 4> cpuInfo{};
			__cpuid( cpuInfo.data(), internal::CPUID_FEATURE_INFO_LEAF );
			hasSupport = ( cpuInfo[2] & ( 1 << internal::ECX_AVX_BIT ) ) != 0;	 // ECX bit 28 = AVX
			hasXsave = ( cpuInfo[2] & ( 1 << internal::ECX_OSXSAVE_BIT ) ) != 0; // ECX bit 27 = OSXSAVE
#endif

			if ( !hasSupport || !hasXsave )
				return false;

			// Check OS support via XCR0
			unsigned long long xcr0 = 0;
#if defined( _MSC_VER )
			xcr0 = _xgetbv( 0 );
#elif defined( __GNUC__ ) || defined( __clang__ )
			// Use inline assembly to avoid requiring -mxsave flag
			unsigned int xcr0_eax, xcr0_edx;
			__asm__ __volatile__( "xgetbv" : "=a"( xcr0_eax ), "=d"( xcr0_edx ) : "c"( 0 ) : );
			xcr0 = ( static_cast<unsigned long long>( xcr0_edx ) << 32 ) | xcr0_eax;
#else
			return false;
#endif

			// Bits 1 (XMM) and 2 (YMM) must be set
			return ( xcr0 & 0x6 ) == 0x6;
		}();

		return s_hasAvx;
	}

	//----------------------------------------------
	// AVX2 Detection
	//----------------------------------------------

	inline bool hasAvx2Support() noexcept
	{
		static const bool s_hasAvx2 = []() {
			bool hasSupport = false;
			bool hasXsave = false;

#if defined( __GNUC__ ) || defined( __clang__ )
			// Check for AVX2 support in extended features
			unsigned int eax, ebx, ecx, edx;
			if ( __get_cpuid_count( internal::CPUID_EXTENDED_FEATURES_LEAF, 0, &eax, &ebx, &ecx, &edx ) )
			{
				hasSupport = ( ebx & ( 1 << internal::EBX_AVX2_BIT ) ) != 0; // EBX bit 5 = AVX2
			}

			// Also need to check OSXSAVE from basic features
			if ( hasSupport && __get_cpuid( internal::CPUID_FEATURE_INFO_LEAF, &eax, &ebx, &ecx, &edx ) )
			{
				hasXsave = ( ecx & ( 1 << internal::ECX_OSXSAVE_BIT ) ) != 0;
			}
#elif defined( _MSC_VER )
			std::array<int, 4> cpuInfo{};

			// Check for AVX2 support in extended features
			__cpuidex( cpuInfo.data(), internal::CPUID_EXTENDED_FEATURES_LEAF, 0 );
			hasSupport = ( cpuInfo[1] & ( 1 << internal::EBX_AVX2_BIT ) ) != 0; // EBX bit 5 = AVX2

			// Check for OSXSAVE in basic features
			__cpuid( cpuInfo.data(), internal::CPUID_FEATURE_INFO_LEAF );
			hasXsave = ( cpuInfo[2] & ( 1 << internal::ECX_OSXSAVE_BIT ) ) != 0; // ECX bit 27 = OSXSAVE
#endif

			if ( !hasSupport || !hasXsave )
				return false;

			// Check OS support via XCR0 (same as AVX - both need XMM and YMM state)
			unsigned long long xcr0 = 0;
#if defined( _MSC_VER )
			xcr0 = _xgetbv( 0 );
#elif defined( __GNUC__ ) || defined( __clang__ )
			// Use inline assembly to avoid requiring -mxsave flag
			unsigned int xcr0_eax, xcr0_edx;
			__asm__ __volatile__( "xgetbv" : "=a"( xcr0_eax ), "=d"( xcr0_edx ) : "c"( 0 ) : );
			xcr0 = ( static_cast<unsigned long long>( xcr0_edx ) << 32 ) | xcr0_eax;
#else
			return false;
#endif

			// Bits 1 (XMM) and 2 (YMM) must be set
			return ( xcr0 & 0x6 ) == 0x6;
		}();

		return s_hasAvx2;
	}

	//----------------------------------------------
	// Compile-time verification helpers
	//----------------------------------------------

	inline bool verifySse42Support() noexcept
	{
		const bool runtimeSupport = hasSse42Support();

#if defined( __SSE4_2__ )
		// GCC/Clang: __SSE4_2__ is defined when -msse4.2 is used
		assert( runtimeSupport && "Compiled with SSE4.2 but CPU doesn't support it!" );
		return runtimeSupport;
#elif defined( _MSC_VER ) && ( defined( __AVX__ ) || defined( __AVX2__ ) || defined( _M_X64 ) )
		// MSVC: Doesn't define __SSE4_2__, but SSE4.2 is available on:
		//   - x64 builds (all x64 CPUs since 2008 have SSE4.2)
		//   - When /arch:AVX or /arch:AVX2 is used (implies SSE4.2)
		assert( runtimeSupport && "Compiled with SSE4.2 but CPU doesn't support it!" );
		return runtimeSupport;
#else
		// Not compiled with SSE4.2 - can't use it even if CPU supports it
		return false;
#endif
	}

	inline bool verifyAvxSupport() noexcept
	{
		const bool runtimeSupport = hasAvxSupport();

#ifdef __AVX__
		assert( runtimeSupport && "Compiled with AVX but CPU doesn't support it!" );
		return runtimeSupport;
#else
		// Not compiled with AVX - can't use it even if CPU supports it
		return false;
#endif
	}

	inline bool verifyAvx2Support() noexcept
	{
		const bool runtimeSupport = hasAvx2Support();

#ifdef __AVX2__
		assert( runtimeSupport && "Compiled with AVX2 but CPU doesn't support it!" );
		return runtimeSupport;
#else
		// Not compiled with AVX2 - can't use it even if CPU supports it
		return false;
#endif
	}
} // namespace nfx::cpu
