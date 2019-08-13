/*
 * inputmanager.h
 *
 *  Created on: Aug 6, 2019
 *      Author: chris
 */

#ifndef INPUTMANAGER_H_
#define INPUTMANAGER_H_

void im_menuExtiHandler();

void im_muxKeys1_4();
void readKey5();
void readKey6();
void readKey7();

void setKeypadBuffer(uint32_t pValue);
void clearKeypadBuffer();
uint32_t getKeypadBuffer();
uint32_t getKeypadBufferMax();
void setKeypadDebounceCounter(uint16_t pValue);


#endif /* INPUTMANAGER_H_ */
