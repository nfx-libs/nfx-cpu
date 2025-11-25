# nfx-cpu

<!-- Project Info -->

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg?style=flat-square)](https://github.com/nfx-libs/nfx-cpu/blob/main/LICENSE.txt) [![GitHub release (latest by date)](https://img.shields.io/github/v/release/nfx-libs/nfx-cpu?style=flat-square)](https://github.com/nfx-libs/nfx-cpu/releases) [![GitHub tag (latest by date)](https://img.shields.io/github/tag/nfx-libs/nfx-cpu?style=flat-square)](https://github.com/nfx-libs/nfx-cpu/tags)<br/>

![C++20](https://img.shields.io/badge/C%2B%2B-20-blue?style=flat-square) ![CMake](https://img.shields.io/badge/CMake-3.20%2B-green.svg?style=flat-square) ![Cross Platform](https://img.shields.io/badge/Platform-Linux_Windows-lightgrey?style=flat-square)

<!-- CI/CD Status -->

[![Linux GCC](https://img.shields.io/github/actions/workflow/status/nfx-libs/nfx-cpu/build-linux-gcc.yml?branch=main&label=Linux%20GCC&style=flat-square)](https://github.com/nfx-libs/nfx-cpu/actions/workflows/build-linux-gcc.yml) [![Linux Clang](https://img.shields.io/github/actions/workflow/status/nfx-libs/nfx-cpu/build-linux-clang.yml?branch=main&label=Linux%20Clang&style=flat-square)](https://github.com/nfx-libs/nfx-cpu/actions/workflows/build-linux-clang.yml) [![Windows MinGW](https://img.shields.io/github/actions/workflow/status/nfx-libs/nfx-cpu/build-windows-mingw.yml?branch=main&label=Windows%20MinGW&style=flat-square)](https://github.com/nfx-libs/nfx-cpu/actions/workflows/build-windows-mingw.yml) [![Windows MSVC](https://img.shields.io/github/actions/workflow/status/nfx-libs/nfx-cpu/build-windows-msvc.yml?branch=main&label=Windows%20MSVC&style=flat-square)](https://github.com/nfx-libs/nfx-cpu/actions/workflows/build-windows-msvc.yml) [![CodeQL](https://img.shields.io/github/actions/workflow/status/nfx-libs/nfx-cpu/codeql.yml?branch=main&label=CodeQL&style=flat-square)](https://github.com/nfx-libs/nfx-cpu/actions/workflows/codeql.yml)

> A modern C++20 header-only library providing CPU feature detection and system identification capabilities

## Overview

nfx-cpu is a CPU feature detection library optimized for performance across multiple platforms and compilers. It delivers runtime CPU capability detection with automatic feature verification, enabling optimal algorithm selection at runtime. Built with modern C++20, the library offers zero-cost abstractions, constexpr support, and cross-platform compatibility.

## Features

### 🧠 CPU Feature Detection

- **SSE4.2 Detection**: Detects SSE4.2 support for hardware acceleration capabilities
- **AVX Detection**: 256-bit floating-point SIMD operations (validates both CPU and OS support)
- **AVX2 Detection**: 256-bit integer SIMD operations (validates both CPU and OS support via XCR0)
- **Runtime Detection**: Dynamic CPU feature detection with cached results
- **Single Binary**: Works optimally on both old and new CPUs without recompilation
- **Cross-Platform**: Supports GCC, Clang, and MSVC compiler intrinsics

### 📊 Real-World Applications

- **SIMD Algorithm Dispatching**: Choose optimal string processing, cryptography, or compression routines
- **Image/Video Processing**: Select SSE/AVX/AVX2 codepaths for filters and transformations
- **Data Science Libraries**: Optimize matrix operations and mathematical computations
- **Game Engines**: Runtime selection of physics, collision detection, and rendering paths

### ⚡ Performance Optimized

- Header-only library with zero runtime dependencies
- Zero-cost abstractions with constexpr support
- Compiler-optimized inline implementations
- Runtime CPU feature detection with cached results
- Cross-platform compatibility and consistent behavior

### 🌍 Cross-Platform Support

- **Platforms**: Linux, Windows
- **Architecture**: x86-64 (x86 SIMD features: SSE4.2, AVX, AVX2)
- **Compilers**: GCC 14+, Clang 19+, MSVC 2022+
- Thread-safe operations
- Consistent behavior across platforms
- CI/CD testing on multiple compilers

## Quick Start

### Requirements

- C++20 compatible compiler:
  - **GCC 14+** (14.2.0 tested)
  - **Clang 18+** (19.1.7 tested)
  - **MSVC 2022+** (19.44+ tested)
- CMake 3.20 or higher

### CMake Integration

```cmake
# Development options
option(NFX_CPU_BUILD_TESTS          "Build tests"                        OFF )
option(NFX_CPU_BUILD_SAMPLES        "Build samples"                      OFF )
option(NFX_CPU_BUILD_BENCHMARKS     "Build benchmarks"                   OFF )
option(NFX_CPU_BUILD_DOCUMENTATION  "Build Doxygen documentation"        OFF )

# Installation
option(NFX_CPU_INSTALL_PROJECT      "Install project"                    OFF )

# Packaging
option(NFX_CPU_PACKAGE_SOURCE       "Enable source package generation"   OFF )
option(NFX_CPU_PACKAGE_ARCHIVE      "Enable TGZ/ZIP package generation"  OFF )
option(NFX_CPU_PACKAGE_DEB          "Enable DEB package generation"      OFF )
option(NFX_CPU_PACKAGE_RPM          "Enable RPM package generation"      OFF )
option(NFX_CPU_PACKAGE_WIX          "Enable WiX MSI installer"           OFF )
```

### Using in Your Project

#### Option 1: Using FetchContent (Recommended)

```cmake
include(FetchContent)
FetchContent_Declare(
  nfx-cpu
  GIT_REPOSITORY https://github.com/nfx-libs/nfx-cpu.git
  GIT_TAG        main  # or use specific version tag like "0.1.1"
)
FetchContent_MakeAvailable(nfx-cpu)

# Link with header-only interface library
target_link_libraries(your_target PRIVATE nfx-cpu::nfx-cpu)
```

#### Option 2: As a Git Submodule

```bash
# Add as submodule
git submodule add https://github.com/nfx-libs/nfx-cpu.git third-party/nfx-cpu
```

```cmake
# In your CMakeLists.txt
add_subdirectory(third-party/nfx-cpu)
target_link_libraries(your_target PRIVATE nfx-cpu::nfx-cpu)
```

#### Option 3: Using find_package (After Installation)

```cmake
find_package(nfx-cpu REQUIRED)
target_link_libraries(your_target PRIVATE nfx-cpu::nfx-cpu)
```

### Building

> ⚠️ **Important**: CPU feature detection tells you what the CPU supports, but you must compile your code with appropriate flags to actually use those SIMD instructions.

**Compiler Flags for SIMD:**

- **GCC/Clang**: `-march=native` (auto-detect) or specific flags like `-msse4.2`, `-mavx`, `-mavx2`
- **MSVC**: `/arch:AVX` or `/arch:AVX2`

**CMake Example:**

```cmake
target_compile_options(your_target PRIVATE
    $<$<CXX_COMPILER_ID:MSVC>:/arch:AVX2>
    $<$<OR:$<CXX_COMPILER_ID:GNU>,$<CXX_COMPILER_ID:Clang>>:-march=native>
)
```

**Build Commands:**

```bash
# Clone the repository
git clone https://github.com/nfx-libs/nfx-cpu.git
cd nfx-cpu

# Create build directory
mkdir build && cd build

# Configure with CMake
cmake .. -DCMAKE_BUILD_TYPE=Release

# Build the library
cmake --build . --config Release --parallel

# Run tests (optional)
ctest -C Release --output-on-failure

# Run benchmarks (optional)
./bin/benchmarks/BM_FeatureDetection
```

### Documentation

nfx-cpu includes API documentation generated with Doxygen.

#### 📚 Online Documentation

The complete API documentation is available online at:
**https://nfx-libs.github.io/nfx-cpu**

#### Building Documentation Locally

```bash
# Configure with documentation enabled
cmake .. -DCMAKE_BUILD_TYPE=Release -DNFX_CPU_BUILD_DOCUMENTATION=ON

# Build the documentation
cmake --build . --target nfx-cpu-documentation
```

#### Requirements

- **Doxygen** - Documentation generation tool
- **Graphviz Dot** (optional) - For generating class diagrams

#### Accessing Local Documentation

After building, open `./build/doc/html/index.html` in your web browser.

## Usage Example

```cpp
#include <iostream>
#include <nfx/CPU.h>

int main() {
    std::cout << "CPU Vendor: " << nfx::cpu::vendor() << std::endl;
    std::cout << "CPU Brand: " << nfx::cpu::brandString() << std::endl;

    std::cout << "\nFeature Detection:" << std::endl;
    std::cout << "  SSE4.2: " << (nfx::cpu::hasSse42Support() ? "Yes" : "No") << std::endl;
    std::cout << "  AVX:    " << (nfx::cpu::hasAvxSupport() ? "Yes" : "No") << std::endl;
    std::cout << "  AVX2:   " << (nfx::cpu::hasAvx2Support() ? "Yes" : "No") << std::endl;

    return 0;
}
```

## Best Practices

### Runtime Feature Detection with Compile-Time Optimization

nfx-cpu provides feature detection that automatically optimizes based on your compile flags:

- **When compiled WITH a feature** (e.g., `-mavx2`): Detection returns `true` immediately (zero overhead, no CPUID call)
- **When compiled WITHOUT a feature**: Performs runtime CPUID detection with cached results

This means you can write a single codebase that adapts to any CPU:

```cpp
#include <vector>
#include <nfx/CPU.h>

void processData(const std::vector<float>& data) {
    // Automatically uses compile-time optimization when built with -mavx2
    // Falls back to runtime detection when built without flags
    if (nfx::cpu::hasAvx2Support()) {
        processData_AVX2(data);  // Safe to use AVX2 intrinsics
        return;
    }

    if (nfx::cpu::hasAvxSupport()) {
        processData_AVX(data);   // Safe to use AVX intrinsics
        return;
    }

    if (nfx::cpu::hasSse42Support()) {
        processData_SSE42(data); // Safe to use SSE4.2 intrinsics
        return;
    }

    processData_scalar(data);    // Fallback implementation
}
```

**Note on MSVC Behavior**: MSVC doesn't define `__SSE4_2__` preprocessor macro, even when SSE4.2 is available. The library handles this automatically:

- On x64 builds, SSE4.2 is always assumed (all x64 CPUs since 2008 have it)
- When `/arch:AVX` or `/arch:AVX2` is used, SSE4.2 is implied and detected

### Debug Verification Pattern

For development builds, use `verify*Support()` functions to catch cases where intrinsics are used without proper compile flags:

```cpp
#include <cassert>
#include <nfx/CPU.h>

void processData(const std::vector<float>& data) {
    // verify*Support() returns false if not compiled with the feature flag
    // Triggers assertion if you try to use AVX2 intrinsics without -mavx2
    if (nfx::cpu::verifyAvx2Support()) {
        processData_AVX2(data);  // Compiler will error if -mavx2 not used
        return;
    }

    // Graceful fallback if feature not compiled or not supported
    processData_scalar(data);
}
```

The `verify*Support()` functions ensure:

- **Compile-time safety**: Returns `false` if feature flag not used (prevents linking errors)
- **Runtime safety**: Asserts if binary compiled with feature but CPU doesn't support it
- **Best practice**: Use in debug builds to catch configuration mistakes early

## Installation & Packaging

nfx-cpu provides packaging options for distribution.

### Package Generation

```bash
# Configure with packaging options
cmake .. -DCMAKE_BUILD_TYPE=Release \
         -DNFX_CPU_PACKAGE_ARCHIVE=ON \
         -DNFX_CPU_PACKAGE_DEB=ON \
         -DNFX_CPU_PACKAGE_RPM=ON

# Generate binary packages
cmake --build . --target package
# or
cd build && cpack

# Generate source packages
cd build && cpack --config CPackSourceConfig.cmake
```

### Supported Package Formats

| Format      | Platform       | Description                        | Requirements |
| ----------- | -------------- | ---------------------------------- | ------------ |
| **TGZ/ZIP** | Cross-platform | Compressed archive packages        | None         |
| **DEB**     | Debian/Ubuntu  | Native Debian packages             | `dpkg-dev`   |
| **RPM**     | RedHat/SUSE    | Native RPM packages                | `rpm-build`  |
| **WiX**     | Windows        | Professional MSI installer         | `WiX 3.11+`  |
| **Source**  | Cross-platform | Source code distribution (TGZ+ZIP) | None         |

### Installation

```bash
# Linux (DEB-based systems)
sudo dpkg -i nfx-cpu_*_amd64.deb

# Linux (RPM-based systems)
sudo rpm -ivh nfx-cpu-*-Linux.rpm

# Windows
# Run the .exe installer with administrator privileges
nfx-cpu-*-win64.exe

# Manual installation (extract archive)
tar -xzf nfx-cpu-*-Linux.tar.gz -C /usr/local/
```

## Project Structure

```
nfx-cpu/
├── benchmark/             # Benchmarks with Google Benchmark
├── cmake/                 # CMake modules and configuration
├── include/nfx/           # Public headers
├── samples/               # Example usage and demonstrations
└── test/                  # Unit tests with GoogleTest
```

## Performance

nfx-cpu is optimized for high performance with:

- **Zero-cost abstractions** - No runtime overhead for feature detection after initial caching
- **Runtime detection with static caching** - CPU feature detection at startup, cached for zero overhead thereafter

For detailed performance metrics and benchmarks, see the [benchmark documentation](benchmark/README.md).

## Roadmap

See [TODO.md](TODO.md) for upcoming features and project roadmap.

## Changelog

See [CHANGELOG.md](CHANGELOG.md) for a detailed history of changes, new features, and bug fixes.

## License

This project is licensed under the MIT License.

## Development Dependencies

- **[GoogleTest](https://github.com/google/googletest)**: Testing framework (BSD 3-Clause License) - Development only
- **[Google Benchmark](https://github.com/google/benchmark)**: Performance benchmarking framework (Apache 2.0 License) - Development only

All dependencies are automatically fetched via CMake FetchContent when building tests or benchmarks.

---

_Updated on November 15, 2025_
