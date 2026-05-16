#  PQC Research & Standards

QuantumShield is designed with a focus on emerging NIST standards for Post-Quantum Cryptography.

## NIST FIPS 203 (ML-KEM)
Formerly known as Kyber, ML-KEM is the primary Key Encapsulation Mechanism used in this project. We focus on the **ML-KEM-768** variant as it provides a balance between security (Category 3) and performance on embedded M33/M34 cores.

## NIST FIPS 204 (ML-DSA)
Formerly known as Dilithium, ML-DSA is used for digital signatures within the OTA update verification process.

## Hybrid Cryptography (RFC 9370)
Our implementation follows the principles of hybrid key exchange, ensuring that devices remain secure against both classical and quantum adversaries. By XORing or concatenating keys from ECDH and ML-KEM, we provide a robust security layer that is compliant with modern "transition-era" requirements.
