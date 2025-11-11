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
 * @file Sample_FeatureDetection.cpp
 * @brief Demonstrates CPU feature detection capabilities
 * @details This sample shows how to detect SSE4.2, AVX, and AVX2 support
 *          for runtime algorithm selection and optimization
 */

#include <iostream>
#include <cassert>

#include <nfx/CPU.h>

int main()
{
	std::cout << "=== nfx-cpu CPU Feature Detection ===\n\n";

	//=====================================================================
	// 1. SSE4.2 detection (SIMD instruction support)
	//=====================================================================
	{
		std::cout << "1. SSE4.2 (Streaming SIMD Extensions 4.2)\n";
		std::cout << "------------------------------------------\n";

		bool hasSSE42 = nfx::cpu::hasSse42Support();

		std::cout << "Status: " << ( hasSSE42 ? "SUPPORTED" : "NOT SUPPORTED" ) << "\n";
		std::cout << "Features: Enhanced SIMD instructions including string processing\n";
		std::cout << "Impact: " << ( hasSSE42 ? "Advanced SIMD instructions available" : "Limited to older SIMD instruction sets" ) << "\n";
		std::cout << "\n";
	}

	//=====================================================================
	// 2. AVX detection (256-bit floating-point SIMD)
	//=====================================================================
	{
		std::cout << "2. AVX (Advanced Vector Extensions)\n";
		std::cout << "------------------------------------\n";

		bool hasAvx = nfx::cpu::hasAvxSupport();

		std::cout << "Status: " << ( hasAvx ? "SUPPORTED" : "NOT SUPPORTED" ) << "\n";
		std::cout << "Features: 256-bit floating-point SIMD operations\n";
		std::cout << "Impact: " << ( hasAvx ? "Vectorized FP math available" : "Limited to 128-bit SSE" ) << "\n";
		std::cout << "\n";
	}

	//=====================================================================
	// 3. AVX2 detection (256-bit integer SIMD)
	//=====================================================================
	{
		std::cout << "3. AVX2 (Advanced Vector Extensions 2)\n";
		std::cout << "--------------------------------------\n";

		bool hasAvx2 = nfx::cpu::hasAvx2Support();

		std::cout << "Status: " << ( hasAvx2 ? "SUPPORTED" : "NOT SUPPORTED" ) << "\n";
		std::cout << "Features: 256-bit integer SIMD operations\n";
		std::cout << "Impact: " << ( hasAvx2 ? "Parallel integer SIMD operations possible" : "Sequential processing only" ) << "\n";
		std::cout << "\n";
	}

	//=====================================================================
	// 4. Feature summary
	//=====================================================================
	{
		std::cout << "4. Feature summary\n";
		std::cout << "------------------\n";

		bool hasSSE42 = nfx::cpu::hasSse42Support();
		bool hasAvx = nfx::cpu::hasAvxSupport();
		bool hasAvx2 = nfx::cpu::hasAvx2Support();

		int supportedFeatures = 0;
		if ( hasSSE42 )
			supportedFeatures++;
		if ( hasAvx )
			supportedFeatures++;
		if ( hasAvx2 )
			supportedFeatures++;

		std::cout << "Detected features: " << supportedFeatures << " / 3\n";

		if ( supportedFeatures == 3 )
		{
			std::cout << "Excellent! Full SIMD support available:\n";
			std::cout << "  Applications can use the most advanced optimizations\n";
		}
		else if ( supportedFeatures >= 1 )
		{
			std::cout << "Good! Partial SIMD support available:\n";
			std::cout << "  Applications can use available hardware acceleration\n";
		}
		else
		{
			std::cout << "Warning: No SIMD extensions detected:\n";
			std::cout << "  Applications should use scalar implementations\n";
		}
		std::cout << "\n";
	}

	//=====================================================================
	// 5. Using detection results for optimization
	//=====================================================================
	{
		std::cout << "5. Using detection results for optimization\n";
		std::cout << "--------------------------------------------\n";

		bool hasSSE42 = nfx::cpu::hasSse42Support();
		bool hasAvx = nfx::cpu::hasAvxSupport();
		bool hasAvx2 = nfx::cpu::hasAvx2Support();

		std::cout << "Example: How applications can use these results:\n\n";

		std::cout << "// Safe feature usage with verification:\n";

		if ( nfx::cpu::verifyAvx2Support() )
		{
			std::cout << "if (nfx::cpu::verifyAvx2Support()) {\n";
			std::cout << "    // Safe to use AVX2 intrinsics - both compiled and available\n";
			std::cout << "    processData_AVX2(data);\n";
			std::cout << "}\n";
		}
		else if ( nfx::cpu::verifyAvxSupport() )
		{
			std::cout << "else if (nfx::cpu::verifyAvxSupport()) {\n";
			std::cout << "    // Safe to use AVX intrinsics - both compiled and available\n";
			std::cout << "    processData_AVX(data);\n";
			std::cout << "}\n";
		}
		else if ( nfx::cpu::verifySse42Support() )
		{
			std::cout << "else if (nfx::cpu::verifySse42Support()) {\n";
			std::cout << "    // Safe to use SSE4.2 intrinsics - both compiled and available\n";
			std::cout << "    processData_SSE42(data);\n";
			std::cout << "}\n";
		}
		else
		{
			std::cout << "else {\n";
			std::cout << "    // Use scalar fallback implementation\n";
			std::cout << "    processData_scalar(data);\n";
			std::cout << "}\n";
		}

		std::cout << "\nThe verify*() functions check both compile-time and runtime support!\n";
		std::cout << "\n";
	}

	return 0;
}
