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
 * @file Identification.inl
 * @brief Implementation of CPU identification functions
 * @details Implements vendor, brand string, family, model, and stepping detection using CPUID with static caching
 */

#if defined( __GNUC__ ) || defined( __clang__ )
#	include <cpuid.h>
#elif defined( _MSC_VER )
#	include <intrin.h>
#endif

#include <algorithm>
#include <array>

namespace nfx::cpu
{
	//=====================================================================
	// CPU identification
	//=====================================================================

	namespace internal
	{
		//----------------------------------------------
		// CPUID wrapper
		//----------------------------------------------

		inline void cpuid( uint32_t leaf, uint32_t subleaf, uint32_t& eax, uint32_t& ebx, uint32_t& ecx, uint32_t& edx ) noexcept
		{
#if defined( __GNUC__ ) || defined( __clang__ )
			__cpuid_count( leaf, subleaf, eax, ebx, ecx, edx );
#elif defined( _MSC_VER )
			int regs[4];
			__cpuidex( regs, static_cast<int>( leaf ), static_cast<int>( subleaf ) );
			eax = static_cast<uint32_t>( regs[0] );
			ebx = static_cast<uint32_t>( regs[1] );
			ecx = static_cast<uint32_t>( regs[2] );
			edx = static_cast<uint32_t>( regs[3] );
#else
			eax = ebx = ecx = edx = 0;
#endif
		}

		inline void cpuid( uint32_t leaf, uint32_t& eax, uint32_t& ebx, uint32_t& ecx, uint32_t& edx ) noexcept
		{
			cpuid( leaf, 0, eax, ebx, ecx, edx );
		}

		//----------------------------------------------
		// Vendor detection
		//----------------------------------------------

		inline std::string detectVendor() noexcept
		{
			uint32_t eax, ebx, ecx, edx;
			cpuid( 0, eax, ebx, ecx, edx );

			// Vendor string is in EBX, EDX, ECX (in that order)
			char vendor[13] = {};
			*reinterpret_cast<uint32_t*>( vendor + 0 ) = ebx;
			*reinterpret_cast<uint32_t*>( vendor + 4 ) = edx;
			*reinterpret_cast<uint32_t*>( vendor + 8 ) = ecx;
			vendor[12] = '\0';

			return std::string( vendor );
		}

		//----------------------------------------------
		// Brand string detection
		//----------------------------------------------

		inline std::string detectBrandString() noexcept
		{
			// Check if extended CPUID is available
			uint32_t eax, ebx, ecx, edx;
			cpuid( 0x80000000, eax, ebx, ecx, edx );

			if ( eax < 0x80000004 )
			{
				return "Unknown";
			}

			// Brand string is stored across 3 CPUID leafs (48 bytes total)
			std::array<char, 49> brand = {};

			for ( uint32_t i = 0; i < 3; ++i )
			{
				cpuid( 0x80000002 + i, eax, ebx, ecx, edx );
				*reinterpret_cast<uint32_t*>( brand.data() + i * 16 + 0 ) = eax;
				*reinterpret_cast<uint32_t*>( brand.data() + i * 16 + 4 ) = ebx;
				*reinterpret_cast<uint32_t*>( brand.data() + i * 16 + 8 ) = ecx;
				*reinterpret_cast<uint32_t*>( brand.data() + i * 16 + 12 ) = edx;
			}

			brand[48] = '\0';

			// Trim leading/trailing spaces
			std::string result( brand.data() );
			auto start = result.find_first_not_of( ' ' );
			auto end = result.find_last_not_of( ' ' );

			if ( start == std::string::npos )
			{
				return "Unknown";
			}

			return result.substr( start, end - start + 1 );
		}

		//----------------------------------------------
		// Family/Model/Stepping detection
		//----------------------------------------------

		inline void detectFamilyModelStepping( uint32_t& outFamily, uint32_t& outModel, uint32_t& outStepping ) noexcept
		{
			uint32_t eax, ebx, ecx, edx;
			cpuid( 1, eax, ebx, ecx, edx );

			// Extract fields from EAX
			uint32_t stepping = eax & 0xF;					// Bits [3:0]
			uint32_t baseModel = ( eax >> 4 ) & 0xF;		// Bits [7:4]
			uint32_t baseFamily = ( eax >> 8 ) & 0xF;		// Bits [11:8]
			uint32_t extendedModel = ( eax >> 16 ) & 0xF;	// Bits [19:16]
			uint32_t extendedFamily = ( eax >> 20 ) & 0xFF; // Bits [27:20]

			// Compute effective family and model
			// Family = (BaseFamily == 0xF) ? (BaseFamily + ExtendedFamily) : BaseFamily
			uint32_t family = ( baseFamily == 0xF ) ? ( baseFamily + extendedFamily ) : baseFamily;

			// Model = (BaseFamily == 0x6 || BaseFamily == 0xF) ? ((ExtendedModel << 4) + BaseModel) : BaseModel
			uint32_t model = ( baseFamily == 0x6 || baseFamily == 0xF ) ? ( ( extendedModel << 4 ) + baseModel ) : baseModel;

			outFamily = family;
			outModel = model;
			outStepping = stepping;
		}
	} // namespace internal

	//----------------------------------------------
	// Public API implementations
	//----------------------------------------------

	inline std::string vendor() noexcept
	{
		static const std::string cached = internal::detectVendor();
		return cached;
	}

	inline std::string brandString() noexcept
	{
		static const std::string cached = internal::detectBrandString();
		return cached;
	}

	inline uint32_t family() noexcept
	{
		static uint32_t cachedFamily = 0;
		static uint32_t cachedModel = 0;
		static uint32_t cachedStepping = 0;
		static bool initialized = false;

		if ( !initialized )
		{
			internal::detectFamilyModelStepping( cachedFamily, cachedModel, cachedStepping );
			initialized = true;
		}

		return cachedFamily;
	}

	inline uint32_t model() noexcept
	{
		static uint32_t cachedFamily = 0;
		static uint32_t cachedModel = 0;
		static uint32_t cachedStepping = 0;
		static bool initialized = false;

		if ( !initialized )
		{
			internal::detectFamilyModelStepping( cachedFamily, cachedModel, cachedStepping );
			initialized = true;
		}

		return cachedModel;
	}

	inline uint32_t stepping() noexcept
	{
		static uint32_t cachedFamily = 0;
		static uint32_t cachedModel = 0;
		static uint32_t cachedStepping = 0;
		static bool initialized = false;

		if ( !initialized )
		{
			internal::detectFamilyModelStepping( cachedFamily, cachedModel, cachedStepping );
			initialized = true;
		}

		return cachedStepping;
	}
} // namespace nfx::cpu
