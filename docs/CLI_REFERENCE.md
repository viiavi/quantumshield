# Qveil CLI Reference

**Qveil** is the primary interface for managing the QuantumShield firmware lifecycle. It is designed to be used by security engineers during development and by automated CI/CD pipelines for secure deployment.

## Command Overview

### `qveil init`
Initializes a new QuantumShield project. It performs a "Safe Init" by scanning existing `prj.conf` and `CMakeLists.txt` files to ensure no existing user configurations are overwritten.

### `qveil build`
Orchestrates the Zephyr build system.
- `--pristine`: Force a clean build.
- `--board <board_id>`: Specify the target hardware (e.g., `nrf54l15dk_nrf54l15_cpuapp`).
- **Feature:** Automatically injects the necessary PQC Kconfig fragments into the build process.

### `qveil flash`
Deploys the signed firmware to the target device.
- Uses `nrfutil` and J-Link for high-reliability flashing.
- Verifies the board serial number before writing to prevent accidental flashing of the wrong device.

### `qveil status`
Queries the live device for its cryptographic posture.
- **Migration State:** Reports if the device is in `CLASSICAL`, `HYBRID`, or `PQC_ONLY` mode.
- **Health Metrics:** Displays heap usage and success/failure counters.
- `--revert`: Forces a manual rollback to the previous cryptographic state (for testing the self-healing engine).

## Technical Implementation
Qveil is built as a Python-based wrapper around the Zephyr `west` tool, leveraging `subprocess` with real-time pipe streaming for an enhanced developer experience.
