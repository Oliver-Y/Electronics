/* Copyright (c) 2014 Nordic Semiconductor. All Rights Reserved.
 *
 * The information contained herein is property of Nordic Semiconductor ASA.
 * Terms and conditions of usage are described in detail in NORDIC
 * SEMICONDUCTOR STANDARD SOFTWARE LICENSE AGREEMENT.
 *
 * Licensees are granted free, non-transferable use of the information. NO
 * WARRANTY of ANY KIND is provided. This heading must NOT be removed from
 * the file.
 *
 */

#include "conn_ble_user_mem.h"
#include "ser_config.h"
#include "nrf_error.h"
#include <stddef.h>



sercon_ble_user_mem_t m_conn_user_mem_table[SER_MAX_CONNECTIONS];

uint32_t conn_ble_user_mem_context_create(uint32_t *p_index)
{
  uint32_t err_code = NRF_ERROR_NO_MEM;
  uint32_t i;

  for (i=0; i<SER_MAX_CONNECTIONS; i++ )
  {
    if ( ! m_conn_user_mem_table[i].conn_active )
    {
        m_conn_user_mem_table[i].conn_active = 1;
        m_conn_user_mem_table[i].mem_block.p_mem = m_conn_user_mem_table[i].mem_table;
        *p_index = i;
        err_code = NRF_SUCCESS;
        break;
    }
  }

  return err_code;
}

uint32_t conn_ble_user_mem_context_destroy(uint16_t conn_handle)
{
  uint32_t err_code = NRF_ERROR_NOT_FOUND;
  uint32_t i;

  for (i=0; i<SER_MAX_CONNECTIONS; i++ )
  {
    if (  m_conn_user_mem_table[i].conn_handle == conn_handle )
    {
        m_conn_user_mem_table[i].conn_active = 0;
        m_conn_user_mem_table[i].mem_block.p_mem = NULL;
        err_code = NRF_SUCCESS;
        break;
    }
  }

  return err_code;
}

uint32_t conn_ble_user_mem_context_find(uint16_t conn_handle, uint32_t *p_index)
{
  uint32_t err_code = NRF_ERROR_NOT_FOUND;
  uint32_t i;

  for (i=0; i<SER_MAX_CONNECTIONS; i++ )
  {
    if ( (m_conn_user_mem_table[i].conn_handle == conn_handle) && (m_conn_user_mem_table[i].conn_active == 1) )
    {
        *p_index = i;
        err_code = NRF_SUCCESS;
        break;
    }
  }

  return err_code;
}

