# 🛡️ QuantumShield: Runtime Cryptographic Agility for Zephyr RTOS

**Securing the IoT ecosystem against quantum threats with autonomous self-healing and hybrid cryptographic agility.**

---

## 🌟 Overview

As quantum computing advances, existing asymmetric cryptographic standards (RSA, ECC) face obsolescence. **QuantumShield** is a portfolio-safe, high-performance middleware designed for **Zephyr RTOS** that enables seamless, runtime migration to **Post-Quantum Cryptography (PQC)** without requiring hardware replacements.

This project demonstrates a production-ready architecture for implementing **ML-KEM (FIPS 203)** and **ML-DSA (FIPS 204)** in resource-constrained IoT environments, featuring a unique "Self-Healing" migration engine.

---

## 🚀 Key Innovations

### 1. Hybrid Cryptographic Agility
QuantumShield doesn't just replace classical crypto; it utilizes a **Hybrid Key Exchange** pipeline. By combining classical ECC with PQC (e.g., ML-KEM-768), the system maintains security even if one algorithm is compromised, meeting the highest standards of NIST's transition guidelines.

### 2. Autonomous Self-Healing Migration
The core of QuantumShield is a multi-stage migration state machine:
- **Phase 1 (Classical):** Standard ECC/RSA security.
- **Phase 2 (Hybrid):** Combined Classical + PQC.
- **Phase 3 (Post-Quantum):** Pure PQC for maximum future-proofing.
- **🛡️ Self-Healing:** If a PQC anomaly or performance degradation is detected, the device autonomously rolls back to a known-safe Hybrid state via **MCUboot** and **OTA rollback** mechanisms.

### 3. TrustZone-Aware Design
Engineered to leverage **ARM TrustZone** (TF-M/PSA), ensuring that PQC key material and sensitive migration states are isolated in the Secure Processing Environment (SPE).

---

## 🏗️ Architecture

The system is built on a modular architecture that separates the migration logic from the underlying cryptographic primitives.

### System Flow
1. **Boot Verification:** Secure boot via MCUboot validates the PQC-ready image.
2. **State Evaluation:** The State Manager determines the current cryptographic phase.
3. **Migration Engine:** Handles the transition between classical and quantum-safe states.
4. **Hardware Acceleration:** Interfaces with hardware-accelerated crypto engines (e.g., nRF54 series) for optimal performance.

*(Diagrams coming soon: See `/architecture` and `/diagrams` folders)*

---

## 📊 Benchmarks

*Measured on nRF54L15 DK (ARM Cortex-M33 @ 128MHz)*

| Metric                | Classical (ECC P-256) | Hybrid (ECC + ML-KEM) | PQC (ML-KEM-768) |
|-----------------------|-----------------------|-----------------------|------------------|
| **Key Generation**    | [Result] ms          | [Result] ms           | [Result] ms      |
| **Encapsulation**     | N/A                   | [Result] ms           | [Result] ms      |
| **Decapsulation**     | [Result] ms          | [Result] ms           | [Result] ms      |
| **RAM Usage**         | [Result] KB          | [Result] KB           | [Result] KB      |
| **Flash Footprint**   | [Result] KB          | [Result] KB           | [Result] KB      |

---

## 🛠️ Tech Stack

- **RTOS:** Zephyr RTOS
- **Hardware:** nRF54L15, Nucleo F401RE
- **Security:** TF-M (Trusted Firmware-M), PSA Security APIs, MCUboot
- **Algorithms:** ML-KEM (Kyber), ML-DSA (Dilithium), SLH-DSA (Sphinx+)
- **Management:** Qveil (QuantumShield CLI)

---

## 📂 Repository Structure

- `architecture/`: High-level system design and security model.
- `benchmarks/`: Detailed performance analysis and resource consumption reports.
- `diagrams/`: Visual representations of OTA flows, state machines, and TrustZone separation.
- `docs/`: Technical specifications and integration guides.
- `sanitized_firmware/`: Public-safe modules and abstraction layers.
- `research_notes/`: Notes on PQC migration strategies and standards (NIST FIPS 203/204).

---

## 📺 Demo

*(Videos and serial logs showing OTA switching and migration state changes can be found in the `/demo` and `/screenshots` folders)*

---

## 🏆 Acknowledgments

Developed as part of a research initiative into **Post-Quantum Security for Embedded Systems**. Special thanks to the community and mentors who supported the exploration of cryptographic agility in RTOS environments.

---

## 📝 License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.
