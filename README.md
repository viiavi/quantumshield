![QuantumShield Banner](assests/banner (2).png)

# QuantumShield: Runtime Cryptographic Agility for Zephyr RTOS

**Post-Quantum Cryptographic Migration and Autonomous Self-Healing for Resource-Constrained IoT Ecosystems.**

---

## Technical Overview

QuantumShield is a security-critical middleware layer designed for Zephyr RTOS, facilitating the seamless transition from classical asymmetric cryptography (RSA, ECC) to NIST-standardized Post-Quantum Cryptography (PQC). 

The framework addresses the "Harvest Now, Decrypt Later" threat by implementing hybrid cryptographic schemes (NIST FIPS 203/204) coupled with a hardware-aware migration engine. It is specifically optimized for ARM Cortex-M architecture and leverages Trusted Firmware-M (TF-M) for secure state isolation.

---

## Core Engineering Innovations

### 1. Hybrid Cryptographic Pipeline
To maintain backward compatibility and defense-in-depth, QuantumShield implements a dual-stack key exchange. By combining traditional Elliptic Curve Diffie-Hellman (ECDH) with Module-Lattice Key Encapsulation Mechanisms (ML-KEM-768), the system ensures cryptographic integrity even in the event of a partial primitive compromise.

### 2. Autonomous State-Machine Migration
The system utilizes a multi-stage migration state machine that governs the device's security posture:
*   **Legacy Mode:** Standard ECC/RSA primitives.
*   **Transition Mode (Hybrid):** Simultaneous use of classical and PQC primitives.
*   **Quantum-Ready Mode:** Pure PQC primitives (ML-KEM / ML-DSA).

### 3. Fault-Tolerant Rollback (Self-Healing)
A critical differentiator of QuantumShield is its autonomous self-healing capability. If the PQC handshake or signature verification fails above a predefined threshold, the device triggers an automated rollback to a known-safe Hybrid state via MCUboot. This prevents denial-of-service (DoS) scenarios during fleet-wide migration.

---

## DevOps & Tooling: Qveil CLI

The **Qveil CLI** serves as the central management engine for the QuantumShield ecosystem, bridging the gap between high-level security policy and low-level firmware deployment.

### Key Capabilities:
*   **Smart Hardware Profiling:** Automatically detects hardware capabilities (RAM, Flash, CPU architecture) and recommends optimal PQC algorithm configurations.
*   **Unified Build Orchestration:** Simplifies complex Zephyr **Sysbuild** workflows, automatically merging MCUboot, TF-M, and the application into a single signed `merged.hex`.
*   **Live Progress Streaming:** Provides real-time feedback during long-running Ninja builds and flashing operations.
*   **Lifecycle Management:** Enables remote querying of the device's cryptographic state and manual triggering of "Self-Healing" rollback tests.

*(See the `demo/CLI_TRANSCRIPT.md` for a full command-line walk-through.)*

---

## System Architecture

The architecture is built upon a modular abstraction layer that decouples cryptographic primitives from application logic, enabling "Cryptographic Agility."

### Key Components:
*   **Migration State Manager:** Orchestrates transitions between security levels based on health metrics.
*   **PSA Storage Integration:** Secures sensitive PQC key material and migration metadata within the Secure Processing Environment (SPE).
*   **Constraint-Aware Selector:** (Internal Research) An AI-driven model that selects optimal PQC parameters based on real-time hardware profiling (RAM/Flash/Cycle counts).

*(Refer to the `/architecture` directory for technical diagrams and security models.)*

---

## Performance Benchmarks

*Hardware: nRF54L15 DK (ARM Cortex-M33 @ 128MHz)*

| Metric | Classical (ECC P-256) | ML-KEM-768 (FIPS 203) |
| :--- | :--- | :--- |
| **Flash Footprint (App)** | 210 KB (Est.) | 289,952 B (83.28%) |
| **RAM Usage (Peak)** | 42 KB (Est.) | 87,980 B (76.54%) |
| **Bootloader Flash** | N/A | 51,064 B (92.35%) |
| **Bootloader RAM** | N/A | 22,176 B (28.50%) |
| **Active Algorithm** | ECDSA / ECDH | ML-KEM-768 |
| **Migration State** | CLASSICAL | PQC_ONLY |


---

## Implementation Sample

```c
/* Standardized API for Hybrid Key Encapsulation */
int quantum_shield_encapsulate(struct qs_context *ctx, 
                               uint8_t *ciphertext, 
                               uint8_t *shared_secret) {
    int rc;

    /* 1. Perform Classical ECC Encapsulation */
    rc = classical_ecc_encaps(ctx->ecc_pk, ciphertext, shared_secret);
    if (rc < 0) return ERR_CLASSICAL_FAILURE;

    /* 2. Perform PQC (ML-KEM) Encapsulation */
    rc = ml_kem_encaps(ctx->pqc_pk, ciphertext + ECC_SIZE, shared_secret + ECC_SECRET_SIZE);
    if (rc < 0) return ERR_PQC_FAILURE;

    /* 3. Derive Hybrid Secret via KDF */
    return hybrid_kdf_derive(shared_secret, FINAL_SECRET_SIZE);
}
```

---

## Project Structure

*   `architecture/`: Security models and Mermaid-based system flows.
*   `benchmarks/`: Empirical data on resource consumption and throughput.
*   `docs/`: Integration guides for Zephyr-based applications.
*   `sanitized_firmware/`: Reference implementation of the migration engine and core abstraction.
*   `research_notes/`: Analysis of NIST FIPS 203/204 and hybrid crypto standards.

---

## Acknowledgments

Developed as a submission for the **Unisys Innovation Program 2026**. Focused on advancing the state of post-quantum resilience in the global IoT ecosystem.
