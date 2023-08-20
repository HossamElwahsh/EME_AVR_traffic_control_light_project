/*
 * application_interface.h
 *
 * Created: 8/20/2023 9:38:37 AM
 *  Author: Team A
 */ 


#ifndef APPLICATION_INTERFACE_H_
#define APPLICATION_INTERFACE_H_

#define TRAFFIC_LIGHT_DELAY_TOTAL   5000
#define TRAFFIC_LIGHT_DELAY_SENSE   5

#define YELLOW_BLINK_DURATION       200

#define LCD_STR_PED "PEDESTRIAN"
#define LCD_STR_CAR "CAR   MODE"

void application_init();
void application_start();
void pedestrian_btn_event(void);


#endif /* APPLICATION_INTERFACE_H_ */