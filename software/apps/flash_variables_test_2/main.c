/* Flash Variables Test
 */

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "nrf.h"
#include "nrf_timer.h"
#include "nrf_delay.h"
#include "nrf_gpio.h"
#include "nrf_power.h"
#include "nrf_log.h"
#include "nrf_log_ctrl.h"
#include "nrf_log_default_backends.h"

#include "simple_thread.h"

#include "fds.h"
#include "nrf_atfifo.h"

//#include "nrf_fstorage.h"
//#include "nrf_fstorage_nvmc.h"

#define DEFAULT_CHILD_TIMEOUT    40                                         /**< Thread child timeout [s]. */
#define DEFAULT_POLL_PERIOD      1000                                       /**< Thread Sleepy End Device polling period when MQTT-SN Asleep. [ms] */
#define NUM_SLAAC_ADDRESSES      4                                          /**< Number of SLAAC addresses. */

/**@brief Function for initializing the nrf log module.
 */
static void log_init(void)
{
    ret_code_t err_code = NRF_LOG_INIT(NULL);
    APP_ERROR_CHECK(err_code);
    NRF_LOG_DEFAULT_BACKENDS_INIT();
}

static void fds_evt_handler(fds_evt_t const * p_fds_evt)
{
    switch (p_fds_evt->id)
    {
        case FDS_EVT_INIT:
            if (p_fds_evt->result != FDS_SUCCESS)
            {
                // Initialization failed.
            }
            break;
        default:
            break;
    }
}


int main(void) {
    nrf_power_dcdcen_set(1);
    log_init();
    NRF_LOG_INFO("Start");

    ret_code_t rc = fds_register(fds_evt_handler);
    if (rc != FDS_SUCCESS)
    {
        // Registering of the FDS event handler has failed.
        NRF_LOG_INFO("FDS register failed");
    } else {
        NRF_LOG_INFO("FDS register OK");
    }
    
    rc = fds_init();
    if (rc != FDS_SUCCESS)
    {
        NRF_LOG_INFO("FDS init failed");
    } else {
        NRF_LOG_INFO("FDS init OK");
    }

    uint16_t FILE_ID = 0x0001;  /* The ID of the file to write the records into. */
    uint16_t RECORD_KEY_1 = 0x1111;  /* A key for the first record. */
    uint16_t RECORD_KEY_2 = 0x2222;  /* A key for the second record. */
    static uint32_t const m_deadbeef = 0xDEADBEEF;
    static char const m_hello[]  = "Hello, world!";
    fds_record_t        record;
    fds_record_desc_t   record_desc;

    // Set up record.
    record.file_id           = FILE_ID;
    record.key               = RECORD_KEY_1;
    record.data.p_data       = &m_deadbeef;
    record.data.length_words = 1;   /* one word is four bytes. */
    
    rc = fds_record_write(&record_desc, &record);
    if (rc != FDS_SUCCESS)
    {
        NRF_LOG_INFO("FDS write 1 failed");
    } else {
        NRF_LOG_INFO("FDS write 1 OK");
    }

    // Set up record.
    record.file_id           = FILE_ID;
    record.key               = RECORD_KEY_2;
    record.data.p_data       = &m_hello;
    /* The following calculation takes into account any eventual remainder of the division. */
    record.data.length_words = (sizeof(m_hello) + 3) / 4;
    rc = fds_record_write(&record_desc, &record);
    if (rc != FDS_SUCCESS)
    {
        NRF_LOG_INFO("FDS write 2 failed");
    } else {
        NRF_LOG_INFO("FDS write 2 OK");
    }
}
