/**
 * @file qs_core_abstraction.c
 * @brief Implementation of the QuantumShield Core Abstraction.
 * 
 * Demonstrates the autonomous state management and hybrid cryptographic 
 * orchestration logic.
 */

#include "qs_core.h"
#include <string.h>

/* Internal threshold constants */
#define SUCCESS_THRESHOLD_ADVANCE 100
#define FAILURE_THRESHOLD_ROLLBACK 5

int qs_init(struct qs_context *ctx) {
    if (!ctx) return -1;
    
    /* Load state from secure storage (Simulated) */
    ctx->current_state = QS_STATE_LEGACY; 
    ctx->health_counter = 0;
    
    return 0;
}

int qs_hybrid_encapsulate(struct qs_context *ctx, 
                          const uint8_t *pk, 
                          uint8_t *ct, 
                          uint8_t *ss) {
    int rc = 0;

    switch (ctx->current_state) {
        case QS_STATE_LEGACY:
            /* Execute classical ECDH only */
            // rc = classical_ecdh_encaps(pk, ct, ss);
            break;

        case QS_STATE_HYBRID:
            /* Execute Classical + PQC (NIST FIPS 203) */
            // rc = classical_ecdh_encaps(pk, ct, ss);
            // rc |= ml_kem_encaps(pk + OFFSET, ct + OFFSET, ss + OFFSET);
            break;

        case QS_STATE_PQC:
            /* Execute ML-KEM Only */
            // rc = ml_kem_encaps(pk, ct, ss);
            break;

        default:
            return -1;
    }

    if (rc == 0) {
        qs_report_success(ctx);
    } else {
        qs_report_failure(ctx);
    }

    return rc;
}

void qs_report_success(struct qs_context *ctx) {
    ctx->health_counter++;

    if (ctx->health_counter >= SUCCESS_THRESHOLD_ADVANCE) {
        if (ctx->current_state == QS_STATE_LEGACY) {
            ctx->current_state = QS_STATE_HYBRID;
            ctx->health_counter = 0;
        } else if (ctx->current_state == QS_STATE_HYBRID) {
            ctx->current_state = QS_STATE_PQC;
            ctx->health_counter = 0;
        }
    }
}

void qs_report_failure(struct qs_context *ctx) {
    static int consecutive_failures = 0;
    consecutive_failures++;

    if (consecutive_failures >= FAILURE_THRESHOLD_ROLLBACK) {
        /* Trigger autonomous rollback to Hybrid or Legacy */
        if (ctx->current_state == QS_STATE_PQC) {
            ctx->current_state = QS_STATE_HYBRID;
        } else {
            ctx->current_state = QS_STATE_LEGACY;
        }
        consecutive_failures = 0;
        ctx->health_counter = 0;
    }
}
