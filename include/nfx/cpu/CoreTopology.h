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
 * @file CoreTopology.h
 * @brief CPU core topology detection
 * @details Runtime detection of physical cores, logical processors, and hyper-threading
 *          using CPUID and OS APIs with static caching for zero overhead
 */

#pragma once

#include <cstdint>

namespace nfx::cpu
{
	//=====================================================================
	// CPU core topology
	//=====================================================================

	//----------------------------------------------
	// Physical core count
	//----------------------------------------------

	/**
	 * @brief Gets the number of physical CPU cores
	 * @details Queries the operating system to retrieve the actual number of physical cores.
	 *          This excludes logical processors created by Hyper-Threading/SMT.
	 *          Result is cached via static initialization for zero runtime overhead.
	 * @return Number of physical CPU cores
	 * @note This function is marked [[nodiscard]] - the return value should not be ignored
	 * @note Uses std::thread::hardware_concurrency() on platforms without native core detection
	 */
	[[nodiscard]] inline uint32_t physicalCoreCount() noexcept;

	//----------------------------------------------
	// Logical processor count
	//----------------------------------------------

	/**
	 * @brief Gets the number of logical processors (threads)
	 * @details Queries the operating system to retrieve the total number of logical processors.
	 *          This includes both physical cores and hyper-threaded logical cores.
	 *          Result is cached via static initialization for zero runtime overhead.
	 * @return Number of logical processors
	 * @note This function is marked [[nodiscard]] - the return value should not be ignored
	 * @note Uses std::thread::hardware_concurrency() which returns logical processors
	 */
	[[nodiscard]] inline uint32_t logicalCoreCount() noexcept;

	//----------------------------------------------
	// Hyper-Threading detection
	//----------------------------------------------

	/**
	 * @brief Detects if Hyper-Threading (or SMT) is enabled
	 * @details Compares logical processor count to physical core count.
	 *          If logical > physical, hyper-threading is enabled.
	 *          Result is cached via static initialization for zero runtime overhead.
	 * @return `true` if HT/SMT is enabled, `false` otherwise
	 * @note This function is marked [[nodiscard]] - the return value should not be ignored
	 */
	[[nodiscard]] inline bool hasHyperThreading() noexcept;

	/**
	 * @brief Gets the Hyper-Threading ratio (logical cores / physical cores)
	 * @details Calculates the ratio of logical processors to physical cores.
	 *          For traditional HT: 2.0 (2 threads per core)
	 *          For hybrid architectures: varies (e.g., 1.43 for 6P+8E cores = 20/14)
	 *          For no HT: 1.0 (1 thread per core)
	 *          Result is cached via static initialization for zero runtime overhead.
	 * @return Hyper-Threading ratio as floating point value
	 * @note This function is marked [[nodiscard]] - the return value should not be ignored
	 */
	[[nodiscard]] inline float hyperThreadingRatio() noexcept;
} // namespace nfx::cpu

#include "nfx/detail/cpu/CoreTopology.inl"
