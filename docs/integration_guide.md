#  Integration Guide

This guide outlines how to integrate the QuantumShield middleware into an existing Zephyr project.

## Prerequisites
- Zephyr SDK v0.16.x or later
- nRF Connect SDK (if targeting Nordic hardware)
- MCUboot enabled in your project configuration

## Step 1: Configuration
Add the following to your `prj.conf`:
```kconfig
CONFIG_QUANTUMSHIELD=y
CONFIG_PQC_ML_KEM_768=y
CONFIG_MIGRATION_ENGINE_AUTO=y
```

## Step 2: Initialization
Initialize the QuantumShield context in your `main.c`:
```c
#include <quantumshield/qs_core.h>

int main(void) {
    qs_init();
    // Your application logic
    return 0;
}
```

## Step 3: Secure Build
Use the provided `qveil` CLI tool to build the secure image:
```bash
qveil build --board nrf54l15dk_nrf54l15_cpuapp
```
