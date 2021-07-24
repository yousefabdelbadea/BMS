/******************************************************************************
 *
 * Module: BMS
 *
 * File Name: BMS_config.h
 *
 * Description: header file for BMS Driver
 *
 * Author: my team
	
 ******************************************************************************/
 #ifndef BMS_CONFIG_H_
 #define BMS_CONFIG_H_
 


 #define NUM_OF_CELLS						6U
 #define NUM_OF_BRANCHES					3U


 /*global   data min && max*/

 #define MAX_TEMP                          40
 #define MIN_TEMP                          15

 #define MAX_VOLT                          4.16
 #define MIN_VOLT                          3.48

 #define MAX_CURRENT                       4
 #define MIN_CURRENT                       0


/**       charge control     **/

#define MIN_STATE_OF_CHARGE                20U
#define MAX_STATE_OF_CHARGE				   90U
#define CHARGE_CONTROL_HIGH                 1
#define CHARGE_CONTROL_LOW                  0
#define CHARGE_CONTROL_MARGIN               5
 

 #endif
