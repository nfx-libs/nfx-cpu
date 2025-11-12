# nfx-cpu TODO

Project roadmap and task tracking for the nfx-cpu library.

### Todo

- [ ] Extended SIMD detection:
  - [ ] SSE3, SSSE3, SSE4.1 detection
    - [ ] Add `hasSSE3Support()`, `hasSSSE3Support()`, `hasSSE41Support()`
    - [ ] Add unit tests in `TESTS_FeatureDetection.cpp`
    - [ ] Add benchmarks in `BM_FeatureDetection.cpp`
  - [ ] FMA (Fused Multiply-Add) detection
    - [ ] Add `hasFmaSupport()`
    - [ ] Add `verifyFmaSupport()` compile-time helper
    - [ ] Add unit tests and benchmarks
  - [ ] AVX-512 detection (F, CD, ER, PF, BW, DW, VL, IFMA, VBMI variants)
    - [ ] Add granular AVX-512 variant detection functions
    - [ ] Add unit tests for each variant
    - [ ] Add performance benchmarks
  - [ ] ARM NEON detection (cross-platform)
    - [ ] Requires ARM CI/CD infrastructure
    - [ ] Platform-specific CPUID equivalent
    - [ ] Full test coverage on ARM hardware
- [ ] Cache topology:
  - [ ] `CacheInfo` struct with L1/L2/L3 sizes, line size
  - [ ] `cacheInfo()` - Complete cache hierarchy
  - [ ] Add `TESTS_CacheTopology.cpp` test suite
  - [ ] Add `BM_CacheTopology.cpp` benchmark suite
  - [ ] Sample demonstrating cache-aware optimization
- [ ] TSC and frequency:
  - [ ] `hasTSC()`, `hasInvariantTSC()`
  - [ ] `readTSC()` - Timestamp counter access
  - [ ] `baseFrequency()`, `maxFrequency()` (MHz)
  - [ ] `hasTurboBoost()` detection
  - [ ] Add unit tests for frequency detection
  - [ ] Add TSC benchmark for overhead measurement
- [ ] Additional x86 instructions:
  - [ ] `hasBMI()` - Bit manipulation instructions (BMI1/BMI2)
  - [ ] `hasPOPCNT()` - Population count
  - [ ] `hasFMA()` - Already in Phase 1 SIMD
  - [ ] Add unit tests for each instruction set
  - [ ] Add benchmarks comparing with/without hardware support
- [ ] ARM extensions:
  - [ ] `hasSVE()` - Scalable Vector Extension
  - [ ] `hasCRC32()` - ARM CRC32 (different from x86)
- [ ] Security features:
  - [ ] `hasAESNI()` - Hardware AES encryption
  - [ ] `hasSHA()` - SHA-1/SHA-256 acceleration
  - [ ] `hasRDRAND()`, `hasRDSEED()` - Hardware RNG
  - [ ] `hasSGX()` - Software Guard Extensions
  - [ ] `hasSMEP()` - Supervisor Mode Execution Prevention
  - [ ] Add security feature tests
  - [ ] Add benchmarks for crypto hardware acceleration
  - [ ] Sample demonstrating AES-NI usage detection
- [ ] NUMA topology:
  - [ ] `numaNodeCount()` - NUMA nodes
  - [ ] NUMA-aware memory allocation helpers
  - [ ] Add NUMA detection tests
  - [ ] Add NUMA-aware allocation benchmarks
  - [ ] Platform-specific implementation (Windows vs Linux)
- [ ] Power management:
  - [ ] `hasSpeedStep()`, `hasThermalMonitor()`
  - [ ] `thermalThreshold()` - Thermal limits
- [ ] Low-level intrinsics:
  - [ ] `prefetch(addr)` - Cache prefetch hint
  - [ ] `pause()` - Spinlock optimization
  - [ ] `serialize()` - Memory fence
  - [ ] Add unit tests for intrinsic wrappers
  - [ ] Add benchmarks measuring prefetch impact
  - [ ] Cross-platform intrinsic abstraction
- [ ] Add `CpuInfo` struct:
  - [ ] `const CpuInfo& cpuInfo()` - Singleton with full CPU capabilities
  - [ ] Structured organization: identification, topology, cache, features, frequency
  - [ ] Single detection pass, cache everything at once
  - [ ] Keep free function API (`hasAvx2Support()`, etc.) for backward compatibility
  - [ ] Hybrid approach: free functions OR struct depending on use case

### In Progress

- NIL

### Done ✓

#### v0.1.1 (2025-11-12)

- [x] **CPU Feature Detection - OS Support Verification**
  - [x] Add OSXSAVE flag check for AVX/AVX2 detection
  - [x] Verify XCR0 register state (XMM/YMM bits) via `xgetbv` instruction
  - [x] Use inline assembly for GCC/Clang to avoid `-mxsave` flag dependency
  - [x] Fix MSVC AVX2 detection to use `__cpuidex()` properly
  - [x] Refactor magic numbers into named constants in `internal` namespace
