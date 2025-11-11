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
 * @file Identification.h
 * @brief CPU identification functions
 * @details Runtime detection of CPU vendor, brand string, family, model, and stepping
 *          information using CPUID instructions with static caching for zero overhead
 */

#pragma once

#include <string>
#include <cstdint>

namespace nfx::cpu
{
	//=====================================================================
	// CPU identification
	//=====================================================================

	//----------------------------------------------
	// Vendor identification
	//----------------------------------------------

	/**
	 * @brief Gets the CPU vendor string
	 * @details Queries CPUID leaf 0 to retrieve the vendor identification string.
	 *          Result is cached via static initialization for zero runtime overhead.
	 *          Common values:
	 *          - "GenuineIntel" - Intel processors
	 *          - "AuthenticAMD" - AMD processors
	 * @return CPU vendor string (12 characters)
	 * @note This function is marked [[nodiscard]] - the return value should not be ignored
	 * @note Requires CPUID leaf 0, EBX:EDX:ECX registers
	 */
	[[nodiscard]] inline std::string vendor() noexcept;

	//----------------------------------------------
	// Brand string
	//----------------------------------------------

	/**
	 * @brief Gets the CPU brand string
	 * @details Queries CPUID leafs 0x80000002-0x80000004 to retrieve the processor brand string.
	 *          Result is cached via static initialization for zero runtime overhead.
	 *          Example: "Intel(R) Core(TM) i7-12800H @ 2.80GHz"
	 * @return CPU brand string (up to 48 characters, trimmed)
	 * @note This function is marked [[nodiscard]] - the return value should not be ignored
	 * @note Requires extended CPUID leafs 0x80000002, 0x80000003, 0x80000004
	 */
	[[nodiscard]] inline std::string brandString() noexcept;

	//----------------------------------------------
	// Family/Model/Stepping
	//----------------------------------------------

	/**
	 * @brief Gets the CPU family identifier
	 * @details Extracts the processor family from CPUID leaf 1.
	 *          Combines base family + extended family for processors with family >= 15.
	 *          Result is cached via static initialization for zero runtime overhead.
	 * @return CPU family identifier
	 * @note This function is marked [[nodiscard]] - the return value should not be ignored
	 * @note Requires CPUID leaf 1, EAX register bits [27:20] (extended) + [11:8] (base)
	 */
	[[nodiscard]] inline uint32_t family() noexcept;

	/**
	 * @brief Gets the CPU model identifier
	 * @details Extracts the processor model from CPUID leaf 1.
	 *          Combines base model + extended model for modern processors.
	 *          Result is cached via static initialization for zero runtime overhead.
	 * @return CPU model identifier
	 * @note This function is marked [[nodiscard]] - the return value should not be ignored
	 * @note Requires CPUID leaf 1, EAX register bits [19:16] (extended) + [7:4] (base)
	 */
	[[nodiscard]] inline uint32_t model() noexcept;

	/**
	 * @brief Gets the CPU stepping identifier
	 * @details Extracts the processor stepping/revision from CPUID leaf 1.
	 *          Stepping identifies minor hardware revisions within the same model.
	 *          Result is cached via static initialization for zero runtime overhead.
	 * @return CPU stepping identifier
	 * @note This function is marked [[nodiscard]] - the return value should not be ignored
	 * @note Requires CPUID leaf 1, EAX register bits [3:0]
	 */
	[[nodiscard]] inline uint32_t stepping() noexcept;
} // namespace nfx::cpu

#include "nfx/detail/cpu/Identification.inl"
