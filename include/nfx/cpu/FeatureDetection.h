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
 * @file FeatureDetection.h
 * @brief CPU feature detection for SIMD instruction sets
 * @details Runtime detection of SSE4.2, AVX, and AVX2 support with static caching
 *          for zero-overhead repeated queries
 */

#pragma once

namespace nfx::cpu
{
	//=====================================================================
	// CPU feature detection
	//=====================================================================

	//----------------------------------------------
	// SSE4.2 Detection
	//----------------------------------------------

	/**
	 * @brief Gets the cached SSE4.2 support status.
	 * @details Checks CPU capabilities for SSE4.2 CRC32 instructions.
	 *          Result is cached via static initialization for zero runtime overhead.
	 * @return `true` if SSE4.2 is supported, `false` otherwise.
	 * @note This function is marked [[nodiscard]] - the return value should not be ignored
	 * @note Requires CPUID leaf 1, ECX bit 20
	 */
	[[nodiscard]] inline bool hasSse42Support() noexcept;

	//----------------------------------------------
	// AVX Detection
	//----------------------------------------------

	/**
	 * @brief Gets the cached AVX support status.
	 * @details Checks CPU capabilities for AVX (Advanced Vector Extensions) instructions,
	 *          which provide 256-bit SIMD operations for floating-point processing. AVX enables:
	 *          - 256-bit floating-point operations (vs 128-bit SSE)
	 *          - Vectorized mathematical computations
	 *          - SIMD-accelerated floating-point algorithms
	 *          Result is cached via static initialization for zero runtime overhead.
	 * @return `true` if AVX is supported, `false` otherwise.
	 * @note This function is marked [[nodiscard]] - the return value should not be ignored
	 * @note Requires CPUID leaf 1, ECX bit 28
	 */
	[[nodiscard]] inline bool hasAvxSupport() noexcept;

	//----------------------------------------------
	// AVX2 Detection
	//----------------------------------------------

	/**
	 * @brief Gets the cached AVX2 support status.
	 * @details Checks CPU capabilities for AVX2 (Advanced Vector Extensions 2) instructions,
	 *          which provide 256-bit SIMD operations for vectorized processing. AVX2 enables:
	 *          - 256-bit integer operations (vs 128-bit SSE)
	 *          - Vectorized string processing and comparison
	 *          - Parallel integer computation for multiple data elements
	 *          - SIMD-accelerated mathematical operations
	 *          Result is cached via static initialization for zero runtime overhead.
	 * @return `true` if AVX2 is supported, `false` otherwise.
	 * @note This function is marked [[nodiscard]] - the return value should not be ignored
	 * @note Requires CPUID leaf 7, subfunction 0, EBX bit 5
	 */
	[[nodiscard]] inline bool hasAvx2Support() noexcept;

	//----------------------------------------------
	// Compile-time verification helpers
	//----------------------------------------------

	/**
	 * @brief Verifies that compile-time flags match runtime capabilities for SSE4.2
	 * @details Checks if SSE4.2 was compiled in and is available at runtime.
	 *          Issues warnings or assertions if there's a mismatch.
	 * @return `true` if SSE4.2 is both compiled and available, `false` otherwise.
	 * @note In debug builds, this may assert on compile/runtime mismatches
	 */
	[[nodiscard]] inline bool verifySse42Support() noexcept;

	/**
	 * @brief Verifies that compile-time flags match runtime capabilities for AVX
	 * @details Checks if AVX was compiled in and is available at runtime.
	 *          Issues warnings or assertions if there's a mismatch.
	 * @return `true` if AVX is both compiled and available, `false` otherwise.
	 * @note In debug builds, this may assert on compile/runtime mismatches
	 */
	[[nodiscard]] inline bool verifyAvxSupport() noexcept;

	/**
	 * @brief Verifies that compile-time flags match runtime capabilities for AVX2
	 * @details Checks if AVX2 was compiled in and is available at runtime.
	 *          Issues warnings or assertions if there's a mismatch.
	 * @return `true` if AVX2 is both compiled and available, `false` otherwise.
	 * @note In debug builds, this may assert on compile/runtime mismatches
	 */
	[[nodiscard]] inline bool verifyAvx2Support() noexcept;
} // namespace nfx::cpu

#include "nfx/detail/cpu/FeatureDetection.inl"
