/**  Manages the event handling functions in the superloop
 *
 * StageManager.cpp
 * Created 1-28-18 By: Smitty
 *
 * A longer description.
 */

#include "StageManager.hpp"



/** 
 * @brief  StageManager constructor
 */
StageManager::StageManager(void)
{
    timerList = new Timer[TIMER_NUM];
    timerList[0].limit = LED_1_POLL;
    timerList[1].limit = LED_2_POLL;
    

    //initializing the variables in the Timer array
    for(int i = 0; i < TIMER_NUM; i++) 
    {
        //creating the individual mask for each timer
        timerList[i].TFmask = 1 << i;
        timerList[i].count = 0;
    }
}


/** 
 * @brief  Handles the multiple timers running off of a single 1ms timer from main
 * @note   Might have to be fleshed out more
 * @retval uint32_t with each bit coresponding to which timers went off
 */
uint32_t StageManager::processTimers(Stage currentStage)
{
    //Goes through the array of timers to increment their count and store which ones popped
    for (int i = 0; i < TIMER_NUM; i++)
    {
        timerList[i].count++;
        if(timerList[i].count >= timerList[i].limit)
        {
            //store which timer popped
            timerTF |= timerList[i].TFmask;

            //resetting the count of the timer that just popped
            timerList[i].count = 0;
        }

    }

    return timerTF;
}


/** 
 * @brief  
 * @note   
 * @retval 
 */
uint32_t StageManager::processCan(Stage currentStage)
{
    //do CAN stuff
    return 0;
}


/** 
 * @brief  
 * @note   
 * @retval 
 */
uint32_t StageManager::processCooling(Stage currentStage)
{
    //do Cooling stuff
    return 0;
}

/** 
 * @brief  
 * @note   
 * @retval 
 */
uint32_t StageManager::processDash(Stage currentStage)
{
    //do Dash processing

    return 0;
}


/** 
 * @brief  
 * @note   
 * @retval 
 */
uint32_t StageManager::processGlcd(Stage currentStage)
{
    //glcd view display updating

    return 0;
}


/** 
 * @brief  
 * @note   
 * @retval 
 */
uint32_t StageManager::processImd(Stage currentStage)
{    
    return 0;
}

/** 
 * @brief  
 * @note   
 * @retval 
 */
uint32_t StageManager::processOrion(Stage currentStage)
{
    return 0;
}


/** 
 * @brief  
 * @note   
 * @retval 
 */
uint32_t StageManager::processPedal(Stage currentStage)
{
    return 0;
}


/** 
 * @brief  
 * @note   
 * @retval 
 */
uint32_t StageManager::processSdCard(Stage currentStage)
{
    return 0;
}

/** 
 * @brief  
 * @note   
 * @retval 
 */
uint32_t StageManager::processUnitek(Stage currentStage)
{
    return 0;
}


/** 
 * @brief  
 * @note   
 * @retval 
 */
uint32_t StageManager::processBatlog(Stage currentStage)
{
    return 0;
}


/** 
 * @brief  
 * @note   
 * @retval 
 */
uint32_t StageManager::processPrecharge(Stage currentStage)
{
    return 0;
}


/** 
 * @brief  
 * @note   
 * @retval 
 */
uint32_t StageManager::processReadyToDrive(Stage currentStage)
{
    return 0;
}

/** 
 * @brief  
 * @note   
 * @retval 
 */
uint32_t StageManager::processLaunch(Stage currentStage)
{
    return 0;
}


/** 
 * @brief  
 * @note   
 * @retval 
 */
uint32_t StageManager::processShutdown(Stage currentStage)
{
    return 0;
}


/** 
 * @brief  
 * @note   Entry condition: EVOS finishes subsystem testing
 *         Exit condition:  Driver requests Precharging
 * @param  &localEventFlags: 
 * @param  urgencyLevel: 
 * @retval 
 */
StageManager::Stage StageManager::processEventsStandby(uint32_t &localEventFlags, Priority urgencyLevel)
{
    Stage currentStage = Stage::STAGE_STANDBY;

    switch(urgencyLevel)
    {
        case PRIORITY_CRITICAL:

            if(localEventFlags && EF_SHUTDOWN)
            {
                processShutdown(currentStage);
                
                //clearing the EF so we don't trigger this again
                localEventFlags &= ~EF_SHUTDOWN;
            }


            if(localEventFlags && EF_IMD)
            {
                processImd(currentStage);
                
                //clearing the EF so we don't trigger this again
                localEventFlags &= ~EF_IMD;
            }

        break;

        
        case PRIORITY_HIGH:
        
            if(localEventFlags && EF_CAN)
            {
                processCan(currentStage);   
                
                //clearing the EF so we don't trigger this again
                localEventFlags &= ~EF_CAN;
            }


            if(localEventFlags && EF_UNITEK)
            {
                processUnitek(currentStage);
                
                //clearing the EF so we don't trigger this again
                localEventFlags &= ~EF_UNITEK;
            }


            if(localEventFlags && EF_ORION)
            {
                processOrion(currentStage);
                
                //clearing the EF so we don't trigger this again
                localEventFlags &= ~EF_ORION;
            }
        
        break;


        case PRIORITY_MEDIUM:

             if(localEventFlags && EF_COOLING)
            {
                processCooling(currentStage);
                
                //clearing the EF so we don't trigger this again
                localEventFlags &= ~EF_COOLING;
            }


            if(localEventFlags && EF_BATLOG)
            {
                processBatlog(currentStage);
                
                //clearing the EF so we don't trigger this again
                localEventFlags &= ~EF_BATLOG;
            }


            if(localEventFlags && EF_DASH)
            {
                processDash(currentStage);
                
                //clearing the EF so we don't trigger this again
                localEventFlags &= ~EF_DASH;
            }

        break;


        case PRIORITY_LOW:

            if(localEventFlags && TF_GLCD)
            {
                processGlcd(currentStage);
                
                //clearing the EF so we don't trigger this again
                localEventFlags &= ~TF_GLCD;
            }


            if(localEventFlags && TF_SDCARD)
            {
                processSdCard(currentStage);
                
                //clearing the EF so we don't trigger this again
                localEventFlags &= ~TF_SDCARD;
            }

        break;

    } //End switch

    return currentStage;
}


/** 
 * @brief  
 * @note   Entry condition: Driver requests Precharging
 *         Exit condition:  Precharge done signal recieved from Unitek
 * @param  &localEventFlags: 
 * @param  urgencyLevel: 
 * @retval 
 */
StageManager::Stage StageManager::processEventsPrecharge(uint32_t &localEventFlags, Priority urgencyLevel)
{
    Stage currentStage = Stage::STAGE_PRECHARGE;

    switch(urgencyLevel)
    {
        case PRIORITY_CRITICAL:
            //code here
            if(localEventFlags && EF_SHUTDOWN)
            {
                processShutdown(currentStage);
                
                //clearing the EF so we don't trigger this again
                localEventFlags &= ~EF_SHUTDOWN;
            }


            if(localEventFlags && EF_IMD)
            {
                processImd(currentStage);
                
                //clearing the EF so we don't trigger this again
                localEventFlags &= ~EF_IMD;
            }

        break;

        
        case PRIORITY_HIGH:
            //code here
            if(localEventFlags && EF_CAN)
            {
                processCan(currentStage);   
                
                //clearing the EF so we don't trigger this again
                localEventFlags &= ~EF_CAN;
            }


            if(localEventFlags && EF_UNITEK)
            {
                processUnitek(currentStage);
                
                //clearing the EF so we don't trigger this again
                localEventFlags &= ~EF_UNITEK;
            }


            if(localEventFlags && EF_ORION)
            {
                processOrion(currentStage);
                
                //clearing the EF so we don't trigger this again
                localEventFlags &= ~EF_ORION;
            }
        
        break;


        case PRIORITY_MEDIUM:
            //code here

             if(localEventFlags && EF_COOLING)
            {
                processCooling(currentStage);
                
                //clearing the EF so we don't trigger this again
                localEventFlags &= ~EF_COOLING;
            }


            if(localEventFlags && EF_BATLOG)
            {
                processBatlog(currentStage);
                
                //clearing the EF so we don't trigger this again
                localEventFlags &= ~EF_BATLOG;
            }


            if(localEventFlags && EF_DASH)
            {
                processDash(currentStage);
                
                //clearing the EF so we don't trigger this again
                localEventFlags &= ~EF_DASH;
            }

        break;


        case PRIORITY_LOW:
            //code here
            if(localEventFlags && TF_SDCARD)
            {
                processSdCard(currentStage);
                
                //clearing the EF so we don't trigger this again
                localEventFlags &= ~TF_SDCARD;
            }


            if(localEventFlags && TF_GLCD)
            {
                processGlcd(currentStage);
                
                //clearing the EF so we don't trigger this again
                localEventFlags &= ~TF_GLCD;
            }

        break;

    } //End switch

    return currentStage;
}


/** 
 * @brief  
 * @note   Entry condition: Precharge done signal recieved from Unitek
 *         Exit condition:  Driver requests ready to drive
 * @param  &localEventFlags: 
 * @param  urgencyLevel: 
 * @retval 
 */
StageManager::Stage StageManager::processEventsEnergized(uint32_t &localEventFlags, Priority urgencyLevel)
{
    Stage currentStage = Stage::STAGE_ENERGIZED;

    switch(urgencyLevel)
    {
        case PRIORITY_CRITICAL:
            //code here
            if(localEventFlags && EF_SHUTDOWN)
            {
                processShutdown(currentStage);
                
                //clearing the EF so we don't trigger this again
                localEventFlags &= ~EF_SHUTDOWN;
            }


            if(localEventFlags && EF_IMD)
            {
                processImd(currentStage);
                
                //clearing the EF so we don't trigger this again
                localEventFlags &= ~EF_IMD;
            }

        break;

        
        case PRIORITY_HIGH:
            //code here
            if(localEventFlags && EF_CAN)
            {
                processCan(currentStage);   
                
                //clearing the EF so we don't trigger this again
                localEventFlags &= ~EF_CAN;
            }


            if(localEventFlags && EF_UNITEK)
            {
                processUnitek(currentStage);
                
                //clearing the EF so we don't trigger this again
                localEventFlags &= ~EF_UNITEK;
            }


            if(localEventFlags && EF_ORION)
            {
                processOrion(currentStage);
                
                //clearing the EF so we don't trigger this again
                localEventFlags &= ~EF_ORION;
            }
        
        break;


        case PRIORITY_MEDIUM:
            //code here

             if(localEventFlags && EF_COOLING)
            {
                processCooling(currentStage);
                
                //clearing the EF so we don't trigger this again
                localEventFlags &= ~EF_COOLING;
            }


            if(localEventFlags && EF_BATLOG)
            {
                processBatlog(currentStage);
                
                //clearing the EF so we don't trigger this again
                localEventFlags &= ~EF_BATLOG;
            }


            if(localEventFlags && EF_DASH)
            {
                processDash(currentStage);
                
                //clearing the EF so we don't trigger this again
                localEventFlags &= ~EF_DASH;
            }

        break;


        case PRIORITY_LOW:
            //code here
            if(localEventFlags && TF_GLCD)
            {
                processGlcd(currentStage);
                
                //clearing the EF so we don't trigger this again
                localEventFlags &= ~TF_GLCD;
            }


            if(localEventFlags && TF_SDCARD)
            {
                processSdCard(currentStage);
                
                //clearing the EF so we don't trigger this again
                localEventFlags &= ~TF_SDCARD;
            }

        break;

    } //End switch

    return currentStage;
}


/** 
 * @brief  
 * @note   Entry condition: Driver requests ready to drive
 *         Exit condition:  Driver requests standby
 * @param  &localEventFlags: 
 * @param  urgencyLevel: 
 * @retval 
 */
StageManager::Stage StageManager::processEventsDriving(uint32_t &localEventFlags, Priority urgencyLevel)
{
    Stage currentStage = Stage::STAGE_STANDBY;

    switch(urgencyLevel)
    {
        case PRIORITY_CRITICAL:
            //code here
            if(localEventFlags && EF_SHUTDOWN)
            {
                processShutdown(currentStage);
                
                //clearing the EF so we don't trigger this again
                localEventFlags &= ~EF_SHUTDOWN;
            }


            if(localEventFlags && EF_IMD)
            {
                processImd(currentStage);
                
                //clearing the EF so we don't trigger this again
                localEventFlags &= ~EF_IMD;
            }

        break;

        
        case PRIORITY_HIGH:
            //code here
            if(localEventFlags && EF_CAN)
            {
                processCan(currentStage);   
                
                //clearing the EF so we don't trigger this again
                localEventFlags &= ~EF_CAN;
            }


            if(localEventFlags && EF_UNITEK)
            {
                processUnitek(currentStage);
                
                //clearing the EF so we don't trigger this again
                localEventFlags &= ~EF_UNITEK;
            }


            if(localEventFlags && EF_ORION)
            {
                processOrion(currentStage);
                
                //clearing the EF so we don't trigger this again
                localEventFlags &= ~EF_ORION;
            }
        
        break;


        case PRIORITY_MEDIUM:
            //code here

             if(localEventFlags && EF_COOLING)
            {
                processCooling(currentStage);
                
                //clearing the EF so we don't trigger this again
                localEventFlags &= ~EF_COOLING;
            }


            if(localEventFlags && EF_BATLOG)
            {
                processBatlog(currentStage);
                
                //clearing the EF so we don't trigger this again
                localEventFlags &= ~EF_BATLOG;
            }


            if(localEventFlags && EF_DASH)
            {
                processDash(currentStage);
                
                //clearing the EF so we don't trigger this again
                localEventFlags &= ~EF_DASH;
            }

        break;


        case PRIORITY_LOW:
            //code here
            if(localEventFlags && TF_GLCD)
            {
                processGlcd(currentStage);
                
                //clearing the EF so we don't trigger this again
                localEventFlags &= ~TF_GLCD;
            }


            if(localEventFlags && TF_SDCARD)
            {
                processSdCard(currentStage);
                
                //clearing the EF so we don't trigger this again
                localEventFlags &= ~TF_SDCARD;
            }

        break;

    } //End switch

    return currentStage;
}