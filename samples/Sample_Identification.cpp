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
 * @file Sample_Identification.cpp
 * @brief Demonstrates CPU identification capabilities
 * @details This sample shows how to query CPU vendor, brand string, family, model,
 *          and stepping information for processor identification
 */

#include <iostream>
#include <iomanip>

#include <nfx/CPU.h>

int main()
{
	using namespace nfx::cpu;

	std::cout << "=== nfx-cpu CPU Identification ===\n\n";

	//=====================================================================
	// 1. CPU vendor
	//=====================================================================
	{
		std::cout << "1. CPU vendor\n";
		std::cout << "-------------\n";

		std::string cpuVendor = vendor();

		std::cout << "Vendor ID: " << cpuVendor << "\n";

		// Interpret vendor string
		if ( cpuVendor == "GenuineIntel" )
		{
			std::cout << "Manufacturer: Intel Corporation\n";
		}
		else if ( cpuVendor == "AuthenticAMD" )
		{
			std::cout << "Manufacturer: Advanced Micro Devices (AMD)\n";
		}
		else
		{
			std::cout << "Manufacturer: " << cpuVendor << "\n";
		}

		std::cout << "\n";
	}

	//=====================================================================
	// 2. CPU brand string
	//=====================================================================
	{
		std::cout << "2. CPU brand string\n";
		std::cout << "-------------------\n";

		std::string brand = brandString();

		std::cout << "Brand: " << brand << "\n";
		std::cout << "Note: Full processor marketing name\n";
		std::cout << "\n";
	}

	//=====================================================================
	// 3. CPU family, model, stepping
	//=====================================================================
	{
		std::cout << "3. CPU family, model, stepping\n";
		std::cout << "----------------------------\n";

		uint32_t fam = family();
		uint32_t mod = model();
		uint32_t step = stepping();

		std::cout << "Family:   " << std::dec << std::setw( 3 ) << fam << " (0x" << std::hex << std::setw( 2 ) << std::setfill( '0' ) << fam << ")\n";
		std::cout << "Model:    " << std::dec << std::setw( 3 ) << std::setfill( ' ' ) << mod << " (0x" << std::hex << std::setw( 2 ) << std::setfill( '0' ) << mod << ")\n";
		std::cout << "Stepping: " << std::dec << std::setw( 3 ) << std::setfill( ' ' ) << step << "\n";

		std::cout << "\nInterpretation:\n";
		std::cout << "  Family:   Processor architecture generation\n";
		std::cout << "  Model:    Specific processor variant within family\n";
		std::cout << "  Stepping: Hardware revision (bug fixes, minor changes)\n";
		std::cout << "\n";
	}

	//=====================================================================
	// 4. Complete CPU summary
	//=====================================================================
	{
		std::cout << "4. Complete CPU summary\n";
		std::cout << "-----------------------\n";

		std::cout << vendor() << " - " << brandString() << "\n";
		std::cout << "Architecture: Family " << std::dec << family() << ", Model " << model() << ", Stepping " << stepping() << "\n";

		std::cout << "\nFeature Detection:\n";
		std::cout << "  SSE4.2: " << ( hasSse42Support() ? "YES" : "NO" ) << "\n";
		std::cout << "  AVX:    " << ( hasAvxSupport() ? "YES" : "NO" ) << "\n";
		std::cout << "  AVX2:   " << ( hasAvx2Support() ? "YES" : "NO" ) << "\n";
		std::cout << "\n";
	}

	return 0;
}
