# Changelog

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.1.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## [Unreleased]

### Added

- NIL

### Changed

- **CPU Feature Detection**: Refactored CPUID magic numbers into named constants in `internal` namespace

### Deprecated

- NIL

### Removed

- NIL

### Fixed

- **CPU Feature Detection**: Added proper OS support verification for AVX/AVX2 detection

### Security

- NIL

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
