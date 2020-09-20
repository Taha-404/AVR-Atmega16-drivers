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

#include "ultrasonic.h"

uint8 g_edgeCount = 0;
uint32 g_overflowCounter = 0;
uint16 g_timeHigh = 0;
uint32 g_ticks = 0;

ISR(TIMER1_OVF_vect)
{
    g_overflowCounter++; /* Increment Timer Overflow count */
}
/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/

/*
/* Description : Call Back Function For Ultrasonic Edge Processing
/* 1.Once Rising Edge Detected Clear Timer Value
/* 2.Configure ICU To Detect Falling Edge
/* 3.Once Falling Edge Detected Store The Timer Value and Deinit ICU
*/
static void Ultrasonic_EdgeProcessing(void)
{
    g_edgeCount++;
    if (g_edgeCount == 1)
    {
        /*
		 * Clear the timer counter register to start measurements from the
		 * first detected rising edge
		 */
        Icu_clearTimerValue();
        /* Detect falling edge */
        Icu_setEdgeDetectionType(FALLING);
    }
    else if (g_edgeCount == 2)
    {
        /* Store the High time value */
        g_timeHigh = Icu_getInputCaptureValue();
        /*if over flow occurs we add (2^16*number of over flows) to the ticks*/
        g_ticks = (g_overflowCounter * 65535) + g_timeHigh;
        g_edgeCount = 0;
        g_overflowCounter = 0;
        /* Disable ICU Driver */
        Icu_DeInit();
    }
}
/*******************************************************************************/
/*
/* Description : Function To Initialize Ultrasonic
/* 1.Enable Triger Pin as Output Pin 
/* 2.Initialize Triger Pin To Zero
*/
void Ultrasonic_init(void)
{ /*Enable Triger Pin as Output Pin*/
    SET_BIT(Triger_CTRL_PORT_DIR, Triger_PIN);
    /*Initialize Triger Pin To Zero*/
    CLEAR_BIT(Triger_CTRL_PORT, Triger_PIN);
}
/*******************************************************************************/
/*
/* Description : Function to Get The Length Measured From Ultrasonic
/* 1.Enable Global Interrupt I Bit
/* 2.Set Call Back Function For Edge Processing To ICU ISR
/* 3.Enable Triger Pin for 10 ms
/* 4.Initialize ICU To Detect Rising Edge
*/
uint16 Ultrasonic_getLength(void)
{
    SET_BIT(TIMSK, TOIE1);
    /* Enable Timer1 Over Flow Interrupt*/
    Icu_ConfigType Icu_Config = {F_CPU_CLOCK, RISING};
    /* Set Call Back Function To ICU ISR*/
    Icu_setCallBack(Ultrasonic_EdgeProcessing);
    /*Enable Triger Pin For 10 us*/
    SET_BIT(Triger_CTRL_PORT, Triger_PIN);
    _delay_us(10);
    CLEAR_BIT(Triger_CTRL_PORT, Triger_PIN);
    /*Initialize ICU To Detect Rising Edge*/
    Icu_init(&Icu_Config);
    /* Distance = (Sound velocity * Time)/2
    /* Time = (Prescaler/F_CPU)*Ticks
    /* Time=(1/1000000)*Ticks
    /* there is error -3cm due to floating point calculations so we add it to distance 
    */
    uint16 distance = (((g_ticks * 34300 * 0.000001) / 2) + 3);
    return (distance);
}