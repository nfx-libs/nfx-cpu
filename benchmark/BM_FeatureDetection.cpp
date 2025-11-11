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
 * @file BM_FeatureDetection.cpp
 * @brief Benchmark CPU feature detection overhead
 * @details Measures the actual cost of CPUID instruction and cached lookups
 */

#include <benchmark/benchmark.h>

#include <nfx/CPU.h>

namespace nfx::cpu::benchmark
{
	//=====================================================================
	// CPU Detection Overhead Benchmarks
	//=====================================================================

	/**
	 * @brief Benchmark SSE4.2 detection (cached)
	 */
	static void BM_Sse42Detection_Cached( ::benchmark::State& state )
	{
		for ( auto _ : state )
		{
			bool hasSSE42 = nfx::cpu::hasSse42Support();
			::benchmark::DoNotOptimize( hasSSE42 );
		}
	}

	/**
	 * @brief Benchmark AVX detection (cached)
	 */
	static void BM_AvxDetection_Cached( ::benchmark::State& state )
	{
		for ( auto _ : state )
		{
			bool hasAVX = nfx::cpu::hasAvxSupport();
			::benchmark::DoNotOptimize( hasAVX );
		}
	}

	/**
	 * @brief Benchmark AVX2 detection (cached)
	 */
	static void BM_Avx2Detection_Cached( ::benchmark::State& state )
	{
		for ( auto _ : state )
		{
			bool hasAVX2 = nfx::cpu::hasAvx2Support();
			::benchmark::DoNotOptimize( hasAVX2 );
		}
	}

	/**
	 * @brief Benchmark raw CPUID instruction overhead (x86/x64 only)
	 */
	static void BM_RawCPUID( ::benchmark::State& state )
	{
#if defined( __x86_64__ ) || defined( _M_X64 ) || defined( __i386__ ) || defined( _M_IX86 )
		for ( auto _ : state )
		{
#	if defined( __GNUC__ ) || defined( __clang__ )
			unsigned int eax, ebx, ecx, edx;
			// Use inline assembly to prevent compiler optimization
			asm volatile( "cpuid"
				: "=a"( eax ), "=b"( ebx ), "=c"( ecx ), "=d"( edx )
				: "a"( 1 ), "c"( 0 ) );
			::benchmark::DoNotOptimize( eax );
			::benchmark::DoNotOptimize( ebx );
			::benchmark::DoNotOptimize( ecx );
			::benchmark::DoNotOptimize( edx );
#	elif defined( _MSC_VER )
			int cpuInfo[4];
			__cpuid( cpuInfo, 1 );
			::benchmark::DoNotOptimize( cpuInfo[0] );
			::benchmark::DoNotOptimize( cpuInfo[1] );
			::benchmark::DoNotOptimize( cpuInfo[2] );
			::benchmark::DoNotOptimize( cpuInfo[3] );
#	endif
		}
#else
		state.SkipWithError( "CPUID not available on this architecture" );
#endif
	}

	// Register benchmarks
	BENCHMARK( BM_Sse42Detection_Cached );
	BENCHMARK( BM_AvxDetection_Cached );
	BENCHMARK( BM_Avx2Detection_Cached );
	BENCHMARK( BM_RawCPUID );
} // namespace nfx::cpu::benchmark

BENCHMARK_MAIN();
