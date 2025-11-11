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
 * @file TESTS_FeatureDetection.cpp
 * @brief Unit tests for CPU feature detection
 * @details Tests runtime CPU detection for SSE4.2, AVX, AVX2 support and feature hierarchy validation
 */

#include <gtest/gtest.h>

#include <nfx/CPU.h>

namespace nfx::cpu::test
{
	using namespace nfx::cpu;

	//=====================================================================
	// CPU feature detection tests
	//=====================================================================

	//----------------------------------------------
	//  CPU feature hierarchy
	//----------------------------------------------

	// AVX2 implies AVX
	TEST( CPUDetection, Avx2ImpliesAvx )
	{
		bool hasAVX = hasAvxSupport();
		bool hasAVX2 = hasAvx2Support();

		if ( hasAVX2 )
		{
			EXPECT_TRUE( hasAVX ) << "AVX2 support requires AVX support";
		}
	}

	// AVX implies SSE4.2 (on x86-64)
	TEST( CPUDetection, AvxImpliesSse42 )
	{
		bool hasSSE42 = hasSse42Support();
		bool hasAVX = hasAvxSupport();

		if ( hasAVX )
		{
			EXPECT_TRUE( hasSSE42 ) << "AVX support typically implies SSE4.2 support";
		}
	}
} // namespace nfx::cpu::test
