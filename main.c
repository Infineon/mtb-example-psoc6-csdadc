/******************************************************************************
* File Name:   main.c
*
* Description: This example measures an external voltage using CSDADC and
*              displays the voltage along with the equivalent digital count
*              via the UART terminal.
*
* Related Document: See README.md
*
*
*******************************************************************************
* Copyright 2019-2021, Cypress Semiconductor Corporation (an Infineon company) or
* an affiliate of Cypress Semiconductor Corporation.  All rights reserved.
*
* This software, including source code, documentation and related
* materials ("Software") is owned by Cypress Semiconductor Corporation
* or one of its affiliates ("Cypress") and is protected by and subject to
* worldwide patent protection (United States and foreign),
* United States copyright laws and international treaty provisions.
* Therefore, you may use this Software only as provided in the license
* agreement accompanying the software package from which you
* obtained this Software ("EULA").
* If no EULA applies, Cypress hereby grants you a personal, non-exclusive,
* non-transferable license to copy, modify, and compile the Software
* source code solely for use in connection with Cypress's
* integrated circuit products.  Any reproduction, modification, translation,
* compilation, or representation of this Software except as specified
* above is prohibited without the express written permission of Cypress.
*
* Disclaimer: THIS SOFTWARE IS PROVIDED AS-IS, WITH NO WARRANTY OF ANY KIND,
* EXPRESS OR IMPLIED, INCLUDING, BUT NOT LIMITED TO, NONINFRINGEMENT, IMPLIED
* WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. Cypress
* reserves the right to make changes to the Software without notice. Cypress
* does not assume any liability arising out of the application or use of the
* Software or any product or circuit described in the Software. Cypress does
* not authorize its products for use in any products where a malfunction or
* failure of the Cypress product may reasonably be expected to result in
* significant property damage, injury or death ("High Risk Product"). By
* including Cypress's product in a High Risk Product, the manufacturer
* of such system or application assumes all risk of such use and in doing
* so agrees to indemnify Cypress against all liability.
*******************************************************************************/

#include "cy_pdl.h"
#include "cycfg.h"
#include "cyhal.h"
#include "cybsp.h"
#include "cy_retarget_io.h"
#include "cy_csdadc.h"

/*******************************************************************************
* Macros
********************************************************************************/
#define CHANNEL0_ID                     (0u) /* Channel 0 */
#define CHANNEL0_MASK                   (1u << CHANNEL0_ID)
#define CSDADC_INTERRUPT_PRIORITY       (7u)
#define CSDADC_SAMPLING_DELAY_MS        (100u) /* in milliseconds */
#define CSDADC_CONVERSION_DELAY_MS      (1u) /* in milliseconds */
#define CSDADC_RESOLUTION_8BIT_MAX      ((1UL << 8) - 1)
#define CSDADC_RESOLUTION_10BIT_MAX     ((1UL << 10) - 1)
#define CSDADC_RESOLUTION_MAX_VAL       CSDADC_RESOLUTION_10BIT_MAX
#define CSDADC_GET_VOLTAGE(x)           (CY_CFG_PWR_VDDA_MV * x / CSDADC_RESOLUTION_MAX_VAL)

/*******************************************************************************
* Function Prototypes
********************************************************************************/
static void csdadc_isr(void);
static void check_status(const char *message, uint32_t status);
static void initialize_csdadc(void);

/*******************************************************************************
* Global Variables
********************************************************************************/
/* Context variable used during the CSDADC operation */
cy_stc_csdadc_context_t csdadc_context;

/*******************************************************************************
* Function Name: main
********************************************************************************
* Summary:
*  System entrance point. This function performs initial setup of device,
*  configures CSD ADC block, converts the input voltage in equivalent digital
*  value, and displays the conversion result on a terminal application.
*
* Return:
*  int
*
*******************************************************************************/
int main(void)
{
    /* Variable used for storing return status of CSDADC APIs */
    cy_en_csdadc_status_t csdadc_status;

    /* Variable used for storing conversion result */
    uint32_t csdadc_ch0_result;
    cy_rslt_t result;

    /* Initialize the device and board peripherals */
    result = cybsp_init();
    if (result != CY_RSLT_SUCCESS)
    {
        CY_ASSERT(0);
    }

    __enable_irq();

    /* Initialize retarget-io to use the debug UART port */
    cy_retarget_io_init(CYBSP_DEBUG_UART_TX, CYBSP_DEBUG_UART_RX,
                        CY_RETARGET_IO_BAUDRATE);

    /* \x1b[2J\x1b[;H - ANSI ESC sequence for clear screen */
    printf("\x1b[2J\x1b[;H");
    printf("****************** "
           "PSoC 6 MCU: CSDADC Code Example "
           "****************** \r\n\n\n");
  
    /* Initializes the CSDADC firmware modules */
    initialize_csdadc();

    /* Enable the CSDADC firmware modules */
    csdadc_status = Cy_CSDADC_Enable(&csdadc_context);
    check_status("CSDADC enable API failed", csdadc_status);

    for (;;)
    {
        /* Start first conversion */
        csdadc_status = Cy_CSDADC_StartConvert(CY_CSDADC_SINGLE_SHOT,
                                               CHANNEL0_MASK, &csdadc_context);
        check_status("Unable to start ADC conversion", csdadc_status);
        cyhal_system_delay_ms(CSDADC_CONVERSION_DELAY_MS);
        csdadc_status = Cy_CSDADC_IsEndConversion(&csdadc_context);

        /* Check if CSDHW is not busy and previously started conversion is not
         * completed.
        */
        if (CY_CSDADC_HW_BUSY != csdadc_status)
        {
            if (CY_CSDADC_OVERFLOW == csdadc_status)
            {
                printf("Last conversion caused overflow."
                       " Re-calibrating CSDADC\n\r");
                csdadc_status = Cy_CSDADC_Calibrate(&csdadc_context);
                check_status("CSDADC calibration failed", csdadc_status);
            }

            if (CY_CSDADC_SUCCESS == csdadc_status)
            {
                csdadc_ch0_result = Cy_CSDADC_GetResult(CHANNEL0_ID, &csdadc_context);
                printf("\x1b[AADC Count: %lu, Calculated Voltage: %lu mV      \r\n",
                       (unsigned long)csdadc_ch0_result, CSDADC_GET_VOLTAGE(csdadc_ch0_result));

                /* Give delay between commands */
                cyhal_system_delay_ms(CSDADC_SAMPLING_DELAY_MS);
            }
        }
    }
}

/*******************************************************************************
* Function Name: initialize_csdadc
********************************************************************************
* Summary:
* This function initializes the Csdadc and configure the Csdadc
* interrupt.
*
*******************************************************************************/
static void initialize_csdadc(void)
{
    /* Variable used for storing return status of SysInt APIs */
    cy_en_sysint_status_t sysint_status;

    /* Variable used for storing return status of CSDADC APIs */
    cy_en_csdadc_status_t csdadc_status;

    /* CSDADC interrupt configuration */
    static const cy_stc_sysint_t csdadc_intr_cfg =
        {
            .intrSrc = csd_interrupt_IRQn,
            .intrPriority = CSDADC_INTERRUPT_PRIORITY,
        };

    /* Initialize CSDADC HW block */
    csdadc_status = Cy_CSDADC_Init(&CSDADC_csdadc_config, &csdadc_context);
    check_status("CSDADC initialization failed", csdadc_status);

    /* Configure CSDADC interrupt */
    sysint_status = Cy_SysInt_Init(&csdadc_intr_cfg, &csdadc_isr);
    check_status("Interrupt initialization failed", sysint_status);
    NVIC_ClearPendingIRQ(csdadc_intr_cfg.intrSrc);
    NVIC_EnableIRQ(csdadc_intr_cfg.intrSrc);
}

/*****************************************************************************
* Function Name: csdadc_isr
******************************************************************************
* Summary:
* Wrapper function for handling interrupts from CSD block.
*
*****************************************************************************/
static void csdadc_isr(void)
{
    Cy_CSDADC_InterruptHandler(CSDADC_HW, &csdadc_context);
}

/******************************************************************************
* Function Name: check_status
*******************************************************************************
* Summary:
* Asserts the non-zero status and prints the message.
*
* Note: It is not mandatory to halt program execution in case of CSDADC API
*        failure. User can implement their own error handler. This application
*        uses halt approach since the application does not implement other
*        functionality except CSDADC.
*
* Parameters:
* char *message : message to print if status is non-zero.
* uint32_t status : status for evaluation.
*
*******************************************************************************/
static void check_status(const char *message, uint32_t status)
{
    if (0u != status)
    {
        printf("[Error] : %s, Error Code: 0x%08lX\r\n", message,
               (unsigned long)status);
        while (1)
            ;
    }
}

/* [] END OF FILE */
