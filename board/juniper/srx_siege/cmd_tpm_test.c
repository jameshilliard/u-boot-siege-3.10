/*
 * Copyright (c) 2015-2016, Juniper Networks, Inc.
 * All rights reserved.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see
 * <http://www.gnu.org/licenses/old-licenses/gpl-2.0.html>
 */
#include <common.h>
#include <command.h>
#include <tpm.h>
#include "../common/upgrade_public_key_info.h"
#include "srx_siege_board.h"
#include "srx_siege_cpld.h"
#include "srx_siege_tpm.h"


extern uint32_t tpm_raw_transfer(uint8_t *command, uint8_t *response, size_t response_length);
extern int tpm_read_int_cert(void *data, size_t count);
extern void print_byte_string(uint8_t *data, size_t count);


int do_tpm_test(cmd_tbl_t *cmdtp, int flag, int argc, char *argv[])
{
    unsigned int rc;
    char data_val[0x1ff];
    uint8_t *data = (uint8_t *) data_val;
    int count = 100;
    uint8_t int_cert[2048];
    uint8_t *int_cert_ptr = int_cert;
    uint8_t response[512];
    uint8_t *resp_ptr;
    uint8_t int_cert_loop_bytes;
    int int_cert_bytes;
    int count_cert;
    size_t response_length = sizeof(response);
    uint8_t command[] = { 0x00, 0xc1, 0x00, 0x00, 0x00, 0x16, 0x00,
        0x00, 0x00, 0xcf, 0x30, 0x00, 0x00, 0x01,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00 };

    printf("\n\nStarting TPM test commands...");
    printf("\nPlease power cycle the board after test is finished...\n\n");


    memset(data_val, 0x0, sizeof(data_val));
    printf("\nTPM: Self Test Full...");
    rc = tpm_self_test_full();
    if (!rc) {
        printf("\nTPM: Command Success\n");
    }

    /*
     * Get TPM_CAP_VERSION_INFO structure contents
     * Capability flag = TPM_CAP_VERSION_VAL
     * Sub Flag = 0x0
     * Refer to TPM Main - Part 2 TPM Structures
     * section 21
     */
    printf("\nTPM: Reading TPM_CAP_VERSION_VAL structure...");
    rc = tpm_get_capability(TPM_CAP_VERSION_VAL, 0x0, data, count);
    if (!rc) {
        printf("\nTPM: Command Success");
        printf("\nTPM: TPM_CAP_VERSION_VAL contents: \n");
        print_byte_string(data, count);
    } else {
        printf("\nTPM Test Error...");
        return 0;
    }


    /*
     * Get TPM_STCLEAR_FLAGS structure contents
     * Capability flag = TPM_CAP_FLAG
     * Sub Flag = TPM_CAP_FLAG_VOLATILE
     */
    memset(data_val, 0x0, sizeof(data_val));
    printf("\nTPM: Reading TPM_CAP_FLAG_VOLATILE structure...");
    rc = tpm_get_capability(TPM_CAP_FLAG, TPM_CAP_FLAG_VOLATILE, data, count);
    if (!rc) {
        printf("\nTPM: Command Success");
        printf("\nTPM: TPM_CAP_FLAG_VOLATILE contents: \n");
        print_byte_string(data, count);
    } else {
        printf("\nTPM Test Error...");
        return 0;
    }

    printf("\nTPM: Enable TPM...");
    rc = tpm_tsc_physical_presence(TPM_PHYSICAL_PRESENCE_PRESENT);
    if (rc) {
        printf("\nTPM Test Error...");
        return 0;
    }

    rc = tpm_physical_enable();
    if (!rc) {
        printf("\nTPM: Command Success");
    }

    printf("\n\nTPM: Clear Physical De-Activated bit");
    rc = tpm_physical_set_deactivated(0);
    if (!rc) {
        printf("\nTPM: Command Success");
    }

    count = 0x500;
    memset(data_val, 0x0, sizeof(data_val));
    printf("\n\nTPM: Read Public EK...");
    rc = tpm_read_pubek(data, count);
    if (!rc) {
        printf("\nTPM: Command Success");
        printf("\nTPM: Public EK: \n");
        print_byte_string(data, count);
    } else {
        printf("\nTPM Test Error...");
        return 0;
    }

    /*
     * Get TPM_PERMANENT_FLAGS structure contents
     * Capability flag = TPM_CAP_FLAG
     * Sub Flag = TPM_CAP_FLAG_PERMANENT
     */
    count = 100;
    memset(data_val, 0x0, sizeof(data_val));
    printf("\nTPM: Reading  TPM_CAP_FLAG_PERMANENT structure...");
    rc = tpm_get_capability(TPM_CAP_FLAG, TPM_CAP_FLAG_PERMANENT, data, count);
    if (!rc) {
        printf("\nTPM: Command Success");
        printf("\nTPM: TPM_CAP_FLAG_PERMANENT contents: \n");
        print_byte_string(data, count);
    } else {
        printf("\nTPM Test Error...");
        return 0;
    }

    /*
     * Check Life time lock bit of physical presence.
     * If not set, set it with option of controlling Physical Presence
     * either through software or hardware.
     * Offset values includes structure ID (2 bytes)
     */
    memset(data_val, 0x0, sizeof(data_val));
    printf("\nTPM: Life Time Lock Bit for PP...");
    if (data[TPM_CAP_PP_LL_OFFSET] == 0x00) {
        rc = tpm_tsc_physical_presence(TPM_PHYSICAL_PRESENCE_HW_ENABLE |
                TPM_PHYSICAL_PRESENCE_CMD_ENABLE |
                TPM_PHYSICAL_PRESENCE_LIFETIME_LOCK);
        rc = tpm_get_capability(TPM_CAP_FLAG, TPM_CAP_FLAG_PERMANENT, data, count);
        if (data[TPM_CAP_PP_LL_OFFSET] == 0x00) {
            printf("\nTPM Test Error...");
            return 0;
        } else {
            printf("set.");
            printf("\nTPM: TPM_CAP_FLAG_PERMANENT contents: \n");
            print_byte_string(data, count);
        }
    } else {
        printf("set.");
    }

    memset(data_val, 0x0, sizeof(data_val));
    printf("\nTPM: PCR Register 15 contents...");
    count = 20;
    rc = tpm_pcr_read(15, data, count);
    if (!rc) {
        puts("\nTPM: PCR 15 content:\n");
        print_byte_string(data, count);
    } else {
        printf("\nTPM Test Error...");
        return 0;
    }

    memset(data_val, 0x0, sizeof(data_val));
    printf("\nTPM: PCR Register 20 contents...");
    rc = tpm_pcr_read(20, data, count);
    if (!rc) {
        puts("\nTPM: PCR 20 content:\n");
        print_byte_string(data, count);
    } else {
        printf("\nTPM Test Error...");
        return 0;
    }


    /*
     * Read and match with Juniper Intermediate Certificate
     * raw data
     */

    /* Send command in chunks of 256 bytes to read */
    for (int_cert_loop_bytes = 0; int_cert_loop_bytes <=5; int_cert_loop_bytes++)
    {
        command[16] = int_cert_loop_bytes;
        if (int_cert_loop_bytes == 5) {
            command[20] = 0x0;
            command[21] = 0x97;
        }

        response_length = sizeof(response);
        rc = tpm_raw_transfer(command, response, response_length);

        if (!rc) {
            resp_ptr = (response + 0x0e);

            if (int_cert_loop_bytes == 5) {
                response_length = 0x97;
#ifdef DEBUG
                print_byte_string(resp_ptr, 0x97);
#endif
            } else {
                response_length = 256;
#ifdef DEBUG
                print_byte_string(resp_ptr, 256);
#endif
            }

            /* Strip header from response */
            for (count = 0; count < response_length; count++)
            {
                *int_cert_ptr++ = *resp_ptr++;
            }
        }
    }

    int_cert_bytes = sizeof(jnpr_intermediate_cert_23_year);

#ifdef DEBUG
    printf("\n Intermediate certificate size is %d bytes", int_cert_bytes);
#endif

    int_cert_ptr = int_cert;
    for (count_cert = 0; count_cert < int_cert_bytes; count_cert++)
    {
        if (*int_cert_ptr == jnpr_intermediate_cert_23_year[count_cert]) {
            int_cert_ptr++;
        } else {
            break;
        }
    }

    if (count_cert == int_cert_bytes) {
        printf("\nTPM: Juniper 23 year Intermediate Certificate matched");
        goto tpm_test_pass;
    } else {
        printf("\n 23 year Intermediate Certificate mismatch at %d byte", count_cert);
    }

tpm_test_10_year_cert:
    int_cert_bytes = sizeof(jnpr_intermediate_cert_10_year);

#ifdef DEBUG
    printf("\n Intermediate certificate size is %d bytes", int_cert_bytes);
#endif

    int_cert_ptr = int_cert;
    for (count_cert = 0; count_cert < int_cert_bytes; count_cert++)
    {
        if (*int_cert_ptr == jnpr_intermediate_cert_10_year[count_cert]) {
            int_cert_ptr++;
        } else {
            break;
        }
    }

    if (count_cert == int_cert_bytes) {
        printf("\nTPM: Juniper 10 year Intermediate Certificate matched");
    } else {
        printf("\n 10 Intermediate Certificate mismatch at %d byte", count_cert);
        printf("\nTPM Test Error...");
        return 0;
    }

tpm_test_pass:
    printf("\n\nTPM Test Passed...\n\n\n");

    return 0;
}

U_BOOT_CMD(tpm_test, 1, 1, do_tpm_test,
           "tpm_test - Test TPM\n",
           "Test TPM and display pass/fail\n");


