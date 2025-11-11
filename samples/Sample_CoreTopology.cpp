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
 * @file Sample_CoreTopology.cpp
 * @brief Demonstrates CPU core topology detection
 * @details This sample shows how to query physical cores, logical processors,
 *          and hyper-threading status for workload optimization
 */

#include <iostream>

#include <nfx/CPU.h>

int main()
{
	using namespace nfx::cpu;

	std::cout << "=== nfx-cpu CPU Core Topology ===\n\n";

	//=====================================================================
	// 1. Physical cores
	//=====================================================================
	{
		std::cout << "1. Physical cores\n";
		std::cout << "-----------------\n";

		uint32_t physical = physicalCoreCount();

		std::cout << "Physical cores: " << physical << "\n";
		std::cout << "Note: Actual CPU cores (excluding hyper-threading)\n";
		std::cout << "\n";
	}

	//=====================================================================
	// 2. Logical processors
	//=====================================================================
	{
		std::cout << "2. Logical processors\n";
		std::cout << "---------------------\n";

		uint32_t logical = logicalCoreCount();

		std::cout << "Logical processors: " << logical << "\n";
		std::cout << "Note: Total thread capacity (includes hyper-threading)\n";
		std::cout << "\n";
	}

	//=====================================================================
	// 3. Hyper-Threading detection
	//=====================================================================
	{
		std::cout << "3. Hyper-Threading detection\n";
		std::cout << "----------------------------\n";

		bool ht = hasHyperThreading();
		uint32_t physical = physicalCoreCount();
		uint32_t logical = logicalCoreCount();
		float ratio = hyperThreadingRatio();

		std::cout << "Hyper-Threading: " << ( ht ? "ENABLED" : "DISABLED" ) << "\n";

		if ( ht )
		{
			std::cout << "Impact: " << logical << " logical threads available ("
					  << physical << " physical cores × " << ratio << ")\n";
		}
		else
		{
			std::cout << "Impact: " << logical << " logical threads available (1:1 mapping)\n";
		}

		std::cout << "\n";
	}

	//=====================================================================
	// 4. Complete topology summary
	//=====================================================================
	{
		std::cout << "4. Complete topology summary\n";
		std::cout << "----------------------------\n";

		std::cout << "CPU: " << vendor() << " - " << brandString() << "\n";
		std::cout << "Physical cores:      " << physicalCoreCount() << "\n";
		std::cout << "Logical processors:  " << logicalCoreCount() << "\n";
		std::cout << "Hyper-Threading:     " << ( hasHyperThreading() ? "YES" : "NO" ) << "\n";

		if ( hasHyperThreading() )
		{
			float ratio = static_cast<float>( logicalCoreCount() ) / static_cast<float>( physicalCoreCount() );
			std::cout << "Thread multiplier:   " << ratio << "x\n";
		}

		std::cout << "\n";
	}

	//=====================================================================
	// 5. Practical use case
	//=====================================================================
	{
		std::cout << "5. Practical use case - Thread pool sizing\n";
		std::cout << "-------------------------------------------\n";

		uint32_t physical = physicalCoreCount();
		uint32_t logical = logicalCoreCount();

		std::cout << "Recommended thread pool sizes:\n";
		std::cout << "  CPU-bound tasks:  " << physical << " threads (1 per physical core)\n";
		std::cout << "  I/O-bound tasks:  " << logical << " threads (utilize hyper-threading)\n";
		std::cout << "  Mixed workload:   " << ( physical + logical ) / 2 << " threads (balanced)\n";

		std::cout << "\nRationale:\n";
		std::cout << "  - CPU-bound: Avoid oversubscription, match physical cores\n";
		std::cout << "  - I/O-bound: Maximize concurrency, use all logical threads\n";
		std::cout << "  - Mixed: Balance between throughput and context switching\n";
		std::cout << "\n";
	}

	return 0;
}
