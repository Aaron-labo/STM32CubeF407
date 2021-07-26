/*
 * app_main.h
 *
 *  Created on: Jul 11, 2021
 *      Author: Francis
 */

#ifndef APP_INC_APP_MAIN_H_
#define APP_INC_APP_MAIN_H_

#include <stdio.h>

void app_main_init(void);
void app_main(void);

#ifdef DEBUG
//#define print(format, ...) printf( format "\r\n",##__VA_ARGS__)
#define print(format, ...) printf("[%04d: %s ][ %10s ]:" format "\r\n",__LINE__,__FILE__,__func__, ##__VA_ARGS__)
#define debug(format, ...) printf("[%04d: %s ][ %10s ]:" format "\r\n",__LINE__,__FILE__,__func__, ##__VA_ARGS__)
#else
//#define print(format, ...)
#define print(format, ...) printf( format "\r\n",##__VA_ARGS__)
#define debug(format, ...)
#endif

#endif /* APP_INC_APP_MAIN_H_ */
