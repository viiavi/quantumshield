# Performance Benchmarks and Resource Analysis

This document provides a detailed breakdown of the memory and flash consumption for QuantumShield running on the nRF54L15 DK. These metrics represent a "Full Migration" scenario where the device has transitioned from Classical to PQC-only mode.

## Hardware Configuration
- **SoC:** Nordic Semiconductor nRF54L15 (ARM Cortex-M33)
- **Clock:** 128 MHz
- **RTOS:** Zephyr RTOS (West build system)
- **Bootloader:** MCUboot with TF-M (Trusted Firmware-M)

## Application Memory Profile (zephyr.elf)
The following table details the resource usage of the main application including the QuantumShield PQC middleware and the CTAP2 application logic.

| Region | Used Space | Total Capacity | Utilization |
| :--- | :--- | :--- | :--- |
| **FLASH** | 289,952 B | 340 KB | **83.28%** |
| **RAM** | 87,980 B | 112 KB | **76.54%** |

## Secure Bootloader Profile (MCUboot)
The secure bootloader is critical for the "Self-Healing" rollback mechanism. Its footprint is optimized to ensure maximum space for the application images.

| Region | Used Space | Total Capacity | Utilization |
| :--- | :--- | :--- | :--- |
| **FLASH** | 51,064 B | 54 KB | **92.35%** |
| **RAM** | 22,176 B | 76 KB | **28.50%** |

## Cryptographic State Transition
| Property | Initial State | Final State (Post-Migration) |
| :--- | :--- | :--- |
| **Migration State** | `CLASSICAL` | `PQC_ONLY` |
| **Active Algorithm** | ECDSA (NIST P-256) | **ML-KEM-768 (FIPS 203)** |
| **Classical Status** | Enabled | **Disabled (Quantum-Safe)** |
| **Free Heap** | 24,484 B | 24,484 B |

## Key Observations
1. **Flash Efficiency:** Despite the complexity of ML-KEM-768 and the migration state machine, the application remains well within the 340 KB flash partition.
2. **RAM Overhead:** The RAM utilization (76.54%) is expected due to the larger public keys and ciphertext sizes required by Lattice-based cryptography compared to ECC.
3. **Deterministic Performance:** The heap remains stable (24,484 B) throughout the migration process, indicating a leak-free implementation of the state transition engine.
