/*
 * Copyright (c) 2007-2016, Juniper Networks, Inc.
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
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 * MA 02111-1307 USA
 */

#ifndef __SRX_SIEGE_TPM_H__
#define __SRX_SIEGE_TPM_H__

/*
 * Capability flag to get capability
 * information from TPM according to
 * sub type value.
 */
#define TPM_CAP_FLAG    0x04

/*
 * Capability Sub Type values
 * Permanent/Volatile type capability data
 */

/*
 * Return the TPM_PERMANENT_FLAGS structure.
 * Each flag in the structure is returned as a byte.
 */
#define TPM_CAP_FLAG_PERMANENT  0x108

/*
 * Return the TPM_STCLEAR_FLAGS structure.
 * Each flag in the structure is returned as a byte.
 */
#define TPM_CAP_FLAG_VOLATILE   0x109

/*
 * TPM_CAP_VERSION_VAL -  returns TPM_CAP_VERSION_INFO structure.
 * TPM fills in the structure and returns the information indicating
 * what the TPM currently supports. Sub type is 0x00 for this cap val.
 */
#define TPM_CAP_VERSION_VAL     0x1A

/*
 * Deactivated flag offset in permanent flags data
 */
#define TPM_CAP_DEACTIVATED_OFFSET 0x04

/*
 * Life Time Lock bit for PP offset (including 2 bytes structure type)
 */
#define TPM_CAP_PP_LL_OFFSET 0x08



#endif
