/**
 * @file qs_core.h
 * @brief Core Abstraction Layer for QuantumShield PQC Middleware.
 * 
 * This header defines the unified interface for hybrid cryptographic 
 * operations and migration state management.
 */

#ifndef QUANTUM_SHIELD_CORE_H
#define QUANTUM_SHIELD_CORE_H

#include <stdint.h>
#include <stddef.h>

/**
 * @brief Cryptographic Migration States.
 */
typedef enum {
    QS_STATE_LEGACY = 0,    /**< Classical ECC/RSA only. */
    QS_STATE_HYBRID,        /**< Combined Classical + PQC. */
    QS_STATE_PQC,           /**< Post-Quantum Only. */
    QS_STATE_ERROR          /**< Fault state / Rollback triggered. */
} qs_state_t;

/**
 * @brief QuantumShield Context structure.
 */
struct qs_context {
    qs_state_t current_state;
    uint32_t health_counter;
    void *platform_data;
};

/**
 * @brief Initialize the QuantumShield middleware.
 * 
 * @return 0 on success, negative error code on failure.
 */
int qs_init(struct qs_context *ctx);

/**
 * @brief Perform a hybrid key encapsulation operation.
 * 
 * @param ctx Pointer to the initialized context.
 * @param pk Public key buffer (Classical + PQC).
 * @param ct Output ciphertext buffer.
 * @param ss Output shared secret buffer.
 * @return 0 on success.
 */
int qs_hybrid_encapsulate(struct qs_context *ctx, 
                          const uint8_t *pk, 
                          uint8_t *ct, 
                          uint8_t *ss);

/**
 * @brief Report operation success to the migration engine.
 * 
 * This helps the autonomous state machine decide when to advance 
 * to the next security phase.
 */
void qs_report_success(struct qs_context *ctx);

/**
 * @brief Report operation failure to trigger potential self-healing.
 */
void qs_report_failure(struct qs_context *ctx);

#endif /* QUANTUM_SHIELD_CORE_H */
