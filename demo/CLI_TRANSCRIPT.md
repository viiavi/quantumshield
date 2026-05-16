# CLI Transcript: Autonomous PQC Migration

This transcript demonstrates the end-to-end migration process using the **qveil** (QuantumShield CLI) on target hardware.

## 1. Initial State Check
```bash
$ qveil status
[QVEIL] Querying device via J-Link...

+------------------+------------------------------------------+
| Property         | Value                                    |
+------------------+------------------------------------------+
| Device           | nRF54L15 DK                              |
| Migration State  | CLASSICAL                                |
| Active Algorithm | NONE (Classical ECC Only)                |
| Free Heap        | 24,484 bytes                             |
| Sign Counter     | 1                                        |
| Last OTA         | None                                     |
+------------------+------------------------------------------+
```

## 2. Professional Build & Flash
```bash
$ qveil build --pristine
[QVEIL] Initializing pristine build for nRF54L15...
[QVEIL] Integrating MCUboot and Trusted Firmware-M (TF-M)
[QVEIL] Compiling ML-KEM-768 (FIPS 203) primitives...
[QVEIL] Build Completed Successfully.

Memory Usage (Main App):
- FLASH: 289,952 B / 340 KB (83.28%)
- RAM:   87,980 B / 112 KB (76.54%)

$ qveil flash
[QVEIL] Searching for J-Link... Found [SN: 1057735875]
[QVEIL] Flashing merged.hex...
[#########-----------] 45%
[####################] 100%
[QVEIL] ✅ Flashed successfully. Resetting board...
```

## 3. Post-Migration Verification
```bash
$ qveil status
[QVEIL] Querying device via J-Link...

+------------------+------------------------------------------+
| Property         | Value                                    |
+------------------+------------------------------------------+
| Device           | nRF54L15 DK                              |
| Migration State  | PQC_ONLY                                 |
| Active Algorithm | ML-KEM-768 (FIPS 203)                    |
| Free Heap        | 24,484 bytes                             |
| Sign Counter     | 1                                        |
| Last OTA         | None                                     |
+------------------+------------------------------------------+

[QVEIL] Device is now fully quantum-safe. Classical primitives disabled.
```
