# Changelog

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.1.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## [Unreleased]

### Added

- NIL

### Changed

- NIL

### Deprecated

- NIL

### Removed

- NIL

### Fixed

- NIL

### Security

- NIL

## [0.1.2] - 2025-11-25

### Changed

- **CPU Feature Detection**: Optimized `has*Support()` functions to skip runtime CPUID checks when compiled with feature flags

  - When compiled with `-mavx2`, `__AVX2__`, etc., functions now return `true` immediately (zero overhead)
  - Runtime CPUID detection only occurs when feature is not compile-time guaranteed
  - Eliminates unnecessary static lambda initialization and CPUID calls in optimized builds
  - Maintains backward compatibility with existing code

## [0.1.1] - 2025-11-12

### Changed

- **CPU Feature Detection**: Refactored CPUID magic numbers into named constants in `internal` namespace

- **Documentation**: Refined README with better examples and clarifications

  - Rewrote overview section to match nfx-hashing style
  - Added x86-64 architecture requirement
  - Clarified AVX/AVX2 OS validation requirements
  - Improved real-world applications examples
  - Updated verification pattern to use library functions instead of manual checks

- **Build System**: Changed MSVC compiler flags from `/arch:AVX` to `/arch:AVX2` for benchmarks, samples, and tests

### Fixed

- **CPU Feature Detection**: Added proper OS support verification for AVX/AVX2 detection

  - Check OSXSAVE flag and verify XCR0 register via xgetbv instruction
  - Use inline assembly for GCC/Clang to avoid -mxsave flag dependency
  - Fix MSVC AVX2 detection to use `__cpuidex()` with proper sub-leaf
  - Prevents false positives where CPU supports AVX/AVX2 but OS doesn't save/restore the extended state

- **CI/CD**:

  - Split GitHub Pages build and deploy into separate jobs to fix artifact conflicts
  - Added concurrency control with cancel-in-progress to prevent deployment clashes
  - Updated documentation workflow to use renamed target `nfx-cpu-documentation`

- **Build System**: Renamed documentation target from `documentation` to `nfx-cpu-documentation` to avoid collision

## [0.1.0] - 2025-11-11 - Initial Release

### Added

- **CPU Feature Detection**: Runtime hardware capability detection with compile-time verification helpers

  - `hasSse42Support()`, `hasAvxSupport()`, `hasAvx2Support()` - Runtime detection functions
  - `verifySse42Support()`, `verifyAvxSupport()`, `verifyAvx2Support()` - Combined compile-time and runtime verification
  - Static caching for zero-overhead repeated queries

- **CPU Identification**: Added CPU identification API

- **Samples**: Added `Sample_CoreTopology.cpp`, `Sample_FeatureDetection.cpp` and `Sample_Identification.cpp`

  - Feature detection demonstration with compile-time vs runtime verification
  - Core topology detection examples with thread pool sizing recommendations
  - CPU identification and vendor information display

- **Benchmarks**: Added `BM_FeatureDetection` benchmark suite measuring CPU feature detection overhead

- **Tests**: Added `TESTS_FeatureDetection` test suite

- **Build System**

  - CMake 3.20+ configuration with modular structure
  - Header-only interface library target
  - Cross-platform support (Linux GCC/Clang, Windows MinGW/Clang/MSVC)
  - Google Test integration for unit testing
  - Google Benchmark integration for performance benchmarking
  - Doxygen documentation generation with GitHub Pages deployment
  - CPack packaging for distribution (DEB, RPM, TGZ, ZIP, WiX MSI)
  - Installation support with CMake package config files

- **Documentation**

  - README with feature overview and usage examples
  - Detailed API documentation with Doxygen comments and RFC references
  - Sample applications
  - Build and installation instructions

- **Testing & Benchmarking**
  - Unit test suite
  - Performance benchmarks for all operations
  - Cross-compiler performance validation
