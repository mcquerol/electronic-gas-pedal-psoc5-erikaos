

/*
 * Filename: swc_engine.c
 *
 * Author: Autogenerated by H-DA RTE Generator, (c) Prof. Fromm
 */

#include "project.h"
#include "global.h"
#include "rte.h"
#include "rte_types.h"
#include "swc_engine.h"



/* USER CODE START SWC_ENGINE_INCLUDE */

/* USER CODE END SWC_ENGINE_INCLUDE */


#include "sp_common.h"

/* USER CODE START SWC_ENGINE_USERDEFINITIONS */
#include "led.h"
/* USER CODE END SWC_ENGINE_USERDEFINITIONS */



/*
* component: swc_engine
* cycletime: 100
* description: Runnable which sets the speed of the engine
* events: 
* name: ENGINE_setEngine_run
* shortname: setEngine
* signalIN: so_targetspeed
* signalOUT: 
* task: tsk_io
*/
void ENGINE_setEngine_run(RTE_event ev){
	
	
	/* USER CODE START ENGINE_setspeed_run */
    
    SC_SPEED_data_t targetspeed = SC_SPEED_INIT_DATA;
    
    //Read in targetspeed
    targetspeed = RTE_SC_SPEED_get(&SO_TARGETSPEED_signal);
    
    RC_t res = RTE_SC_SPEED_pullPort(&SO_TARGETSPEED_signal);
    if (RC_SUCCESS == res)
    {
        UART_LOG_PutChar(targetspeed.rpm);
        LED_RGB_Set(0,targetspeed.rpm,0); //turn on green channel of RGB led with targetspeed as PWM value
    }
    else
    {
        //Some error handling
        res = RC_ERROR_BUFFER_EMTPY;
        return;
    }

    RTE_SC_SPEED_set(&SO_TARGETSPEED_signal, targetspeed);
    RTE_SC_SPEED_pullPort(&SO_TARGETSPEED_signal);
    /* USER CODE END ENGINE_setspeed_run */
}

/*
* component: swc_engine
* cycletime: 0
* description: Runnable that sets the engine brake light
* events: 
* name: ENGINE_setBrakeLight_run
* shortname: setBrakeLight
* signalIN: so_targetspeed
* signalOUT: 
* task: tsk_io
*/
void ENGINE_setBrakeLight_run(RTE_event ev){
	
	/* USER CODE START ENGINE_setBrakeLight_run */
    SC_SPEED_data_t targetspeed = SC_SPEED_INIT_DATA;
    
    //Read in targetspeed
    targetspeed = RTE_SC_SPEED_get(&SO_TARGETSPEED_signal);
    
    RC_t res = RTE_SC_SPEED_pullPort(&SO_TARGETSPEED_signal);
    if (RC_SUCCESS == res)
    {
        if(targetspeed.rpm == 5) // if joystick is in the middle position turn on led
        {
            LED_Set(LED_GREEN,LED_ON); // red led on
        }
        else
        {
            LED_Set(LED_GREEN,LED_OFF);
        }
    }
    else
    {
        //Some error handling
        res = RC_ERROR_BUFFER_EMTPY;
        return;
    }
    /* USER CODE END ENGINE_setBrakeLight_run */
}

/* USER CODE START SWC_ENGINE_FUNCTIONS */

/* USER CODE END SWC_ENGINE_FUNCTIONS */

