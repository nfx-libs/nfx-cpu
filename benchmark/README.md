# Benchmarks

---

## Test Environment

### Hardware Configuration

| Component                | Specification                                                 |
| ------------------------ | ------------------------------------------------------------- |
| **Computer Model**       | Lenovo ThinkPad P15v Gen 3                                    |
| **CPU**                  | 12th Gen Intel Core i7-12800H (20 logical, 14 physical cores) |
| **Base Clock**           | 2.80 GHz                                                      |
| **Turbo Clock**          | 4.80 GHz                                                      |
| **L1 Data Cache**        | 48 KiB (×6 P-cores) + 32 KiB (×8 E-cores)                     |
| **L1 Instruction Cache** | 32 KiB (×6 P-cores) + 64 KiB (×2 E-core clusters)             |
| **L2 Unified Cache**     | 1.25 MiB (×6 P-cores) + 2 MiB (×2 E-core clusters)            |
| **L3 Unified Cache**     | 24 MiB (×1 shared)                                            |
| **RAM**                  | DDR4-3200 (32GB)                                              |
| **GPU**                  | NVIDIA RTX A2000 4GB GDDR6                                    |

### Software Configuration

| Platform    | OS         | Benchmark Framework     | C++ Compiler              | nfx-cpu Version |
| ----------- | ---------- | ----------------------- | ------------------------- | --------------- |
| **Linux**   | LMDE 7     | Google Benchmark v1.9.4 | GCC 14.2.0-x64            | v0.0.0          |
| **Windows** | Windows 10 | Google Benchmark v1.9.4 | MinGW GCC 14.2.0-x64      | v0.0.0          |
| **Windows** | Windows 10 | Google Benchmark v1.9.4 | Clang-GNU-CLI 19.1.5-x64  | v0.0.0          |
| **Windows** | Windows 10 | Google Benchmark v1.9.4 | Clang-MSVC-CLI 19.1.5-x64 | v0.0.0          |
| **Windows** | Windows 10 | Google Benchmark v1.9.4 | MSVC 19.44.35217.0-x64    | v0.0.0          |

---

# Performance Results

## CPU Detection Overhead

| Operation                | Linux GCC    | Linux Clang | Windows MinGW GCC | Windows Clang-GNU-CLI | Windows Clang-MSVC-CLI | Windows MSVC |
| ------------------------ | ------------ | ----------- | ----------------- | --------------------- | ---------------------- | ------------ |
| BM_Sse42Detection_Cached | **0.217 ns** | 0.235 ns    | 0.299 ns          | 0.240 ns              | 0.517 ns               | 0.726 ns     |
| BM_AvxDetection_Cached   | **0.216 ns** | 0.238 ns    | 0.315 ns          | 0.238 ns              | 0.513 ns               | 0.721 ns     |
| BM_Avx2Detection_Cached  | **0.217 ns** | 0.235 ns    | 0.313 ns          | 0.274 ns              | 0.517 ns               | 0.728 ns     |
| BM_RawCPUID              | 324 ns       | **321 ns**  | 438 ns            | 647 ns                | 355 ns                 | 335 ns       |

---

_Benchmarks executed on November 11, 2025_
