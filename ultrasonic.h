/******************************************************************************
 *
 * Module: Ultrasonic
 *
 * File Name: ultrasonic.h
 *
 * Description: Header file for the Ultrasonic driver
 *
 * Engineer: Youssef Taha
 *
 *******************************************************************************/
#ifndef ULTRASONIC_H_
#define ULTRASONIC_H_
#include "icu.h"
#include "std_types.h"
#include "common_macros.h"
/*******************************************************************************
 *                      Preprocessor Macros                                    *
 *******************************************************************************/
#define Triger_CTRL_PORT PORTD
#define Triger_CTRL_PORT_DIR DDRD
#define Triger_PIN PD5
#define Ultrasonic_range 400 /*maximum range of the Ultrasonic*/
/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/
void Ultrasonic_init(void);
uint16 Ultrasonic_getLength(void);
#endif