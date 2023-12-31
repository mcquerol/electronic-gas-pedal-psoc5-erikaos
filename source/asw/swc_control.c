

/*
 * Filename: swc_control.c
 *
 * Author: Autogenerated by H-DA RTE Generator, (c) Prof. Fromm
 */

#include "project.h"
#include "global.h"
#include "rte.h"
#include "rte_types.h"
#include "swc_control.h"



/* USER CODE START SWC_CONTROL_INCLUDE */
#define MAX_AGE 3 // max age of signal allowed (cycles)
/* USER CODE END SWC_CONTROL_INCLUDE */


#include "sp_common.h"

/* USER CODE START SWC_CONTROL_USERDEFINITIONS */

/* USER CODE END SWC_CONTROL_USERDEFINITIONS */



/*
* component: swc_control
* cycletime: 0
* description: Runnable which translates joystick position into targetspeed for engines
* events: ev_joystick_onData
* name: CONTROL_calcControl_run
* shortname: calcControl
* signalIN: so_joystick
* signalOUT: so_targetspeed
* task: tsk_control
*/
void CONTROL_calcControl_run(RTE_event ev){
	
	/* USER CODE START CONTROL_calcControl_run */
    SC_JOYSTICK_data_t input = SC_JOYSTICK_INIT_DATA;
    SC_SPEED_data_t output = SC_SPEED_INIT_DATA;
    
    uint32_t age = RTE_SC_SPEED_getAge(&SO_TARGETSPEED_signal);
    
    RC_t res = RTE_SC_JOYSTICK_pullPort(&SO_JOYSTICK_signal);
    if (RC_SUCCESS == res)
    {
        input = RTE_SC_JOYSTICK_get(&SO_JOYSTICK_signal);
        if(input.y >=0) // only positive values give positive speed
        {
            output.rpm = 2 * input.y; // set the output signal to the input signal
        }
        else
        {
            output.rpm = 0;
        }
        if(age < MAX_AGE) //if the age of the data is not too old
        {
            RTE_SC_SPEED_set(&SO_TARGETSPEED_signal, output);
            RTE_SC_SPEED_pullPort(&SO_TARGETSPEED_signal);   
        }
    }
    else
    {
        //Some error handling
        res = RC_ERROR_BUFFER_EMTPY;
        return;
    }

    /* USER CODE END CONTROL_calcControl_run */
}

/* USER CODE START SWC_CONTROL_FUNCTIONS */

/* USER CODE END SWC_CONTROL_FUNCTIONS */

