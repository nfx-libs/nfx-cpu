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
 * @file CoreTopology.inl
 * @brief Implementation of CPU core topology detection
 * @details Implements physical/logical core count and hyper-threading detection using OS APIs
 */

#if defined( _WIN32 )
#	ifndef NOMINMAX
#		define NOMINMAX
#	endif
#	include <windows.h>
#elif defined( __linux__ )
#	include <cstdio>
#	include <set>
#	include <unistd.h>
#endif

#include <thread>

namespace nfx::cpu
{
	//=====================================================================
	// CPU core topology
	//=====================================================================

	namespace internal
	{
		//----------------------------------------------
		// Physical core detection
		//----------------------------------------------

		inline uint32_t detectPhysicalCores() noexcept
		{
#if defined( _WIN32 )
			// Windows: Use GetLogicalProcessorInformation
			::DWORD length = 0;
			::GetLogicalProcessorInformation( nullptr, &length );

			if ( length == 0 )
			{
				return static_cast<uint32_t>( std::thread::hardware_concurrency() );
			}

			// Use stack allocation with a reasonable max size
			::SYSTEM_LOGICAL_PROCESSOR_INFORMATION buffer[256];
			::DWORD bufferSize = sizeof( buffer );

			if ( !::GetLogicalProcessorInformation( buffer, &bufferSize ) )
			{
				return static_cast<uint32_t>( std::thread::hardware_concurrency() );
			}

			uint32_t coreCount = 0;
			::DWORD count = bufferSize / sizeof( ::SYSTEM_LOGICAL_PROCESSOR_INFORMATION );

			for ( ::DWORD i = 0; i < count; ++i )
			{
				if ( buffer[i].Relationship == ::RelationProcessorCore )
				{
					coreCount++;
				}
			}

			return coreCount > 0 ? coreCount : static_cast<uint32_t>( std::thread::hardware_concurrency() );

#elif defined( __linux__ )
			// Linux: Parse /sys/devices/system/cpu/cpu*/topology/core_id
			// This gives accurate physical core count by counting unique core IDs
			// Works correctly for hybrid architectures (P-cores + E-cores)
			std::set<int> uniqueCores;

			for ( int cpu = 0; cpu < 1024; ++cpu ) // Reasonable upper limit
			{
				char path[256];
				snprintf( path, sizeof( path ), "/sys/devices/system/cpu/cpu%d/topology/core_id", cpu );

				FILE* file = fopen( path, "r" );
				if ( !file )
					break; // No more CPUs

				int coreId;
				if ( fscanf( file, "%d", &coreId ) == 1 )
				{
					uniqueCores.insert( coreId );
				}
				fclose( file );
			}

			if ( !uniqueCores.empty() )
			{
				return static_cast<uint32_t>( uniqueCores.size() );
			}

			// Fallback: If /sys parsing fails, return logical count
			// (This is wrong for HT systems, but better than crashing)
			long cores = sysconf( ::_SC_NPROCESSORS_ONLN );
			return cores > 0 ? static_cast<uint32_t>( cores ) : static_cast<uint32_t>( std::thread::hardware_concurrency() );
#else
			// Fallback
			return static_cast<uint32_t>( std::thread::hardware_concurrency() );
#endif
		}

		//----------------------------------------------
		// Logical processor detection
		//----------------------------------------------

		inline uint32_t detectLogicalCores() noexcept
		{
			return static_cast<uint32_t>( std::thread::hardware_concurrency() );
		}

		//----------------------------------------------
		// Hyper-Threading ratio calculation
		//----------------------------------------------

		inline float calculateHyperThreadingRatio() noexcept
		{
			uint32_t physical = detectPhysicalCores();
			uint32_t logical = detectLogicalCores();

			if ( physical == 0 )
			{
				return 1.0f;
			}

			return static_cast<float>( logical ) / static_cast<float>( physical );
		}
	} // namespace internal

	//----------------------------------------------
	// Public API implementations
	//----------------------------------------------

	inline uint32_t physicalCoreCount() noexcept
	{
		static const uint32_t cached = internal::detectPhysicalCores();
		return cached;
	}

	inline uint32_t logicalCoreCount() noexcept
	{
		static const uint32_t cached = internal::detectLogicalCores();
		return cached;
	}

	inline bool hasHyperThreading() noexcept
	{
		static const bool cached = ( logicalCoreCount() > physicalCoreCount() );
		return cached;
	}

	inline float hyperThreadingRatio() noexcept
	{
		static const float cached = internal::calculateHyperThreadingRatio();
		return cached;
	}
} // namespace nfx::cpu
