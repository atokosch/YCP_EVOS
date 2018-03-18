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
    timerList[0].limit = POLL_TIME_GLCD;
    timerList[1].limit = POLL_TIME_SDCARD;
    timerList[2].limit = POLL_TIME_PEDAL;
    

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
uint32_t StageManager::processTimers(void)
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
uint32_t StageManager::processCan(void)
{
    //do CAN stuff
    return 0;
}


/** 
 * @brief  
 * @note   
 * @retval 
 */
uint32_t StageManager::processCooling(void)
{
    //do Cooling stuff
    return 0;
}


/** 
 * @brief  
 * @note   
 * @param  currentStage: 
 * @param  tasks: 
 * @retval 
 */
uint32_t StageManager::processDash(uint8_t* taskFlags)
{
    //do Dash processing
    Serial.print("Dash tasks: ");
    Serial.println(taskFlags[DASH], BIN); 

    switch(currentStage){
        case STAGE_STANDBY:
        {
            if(taskFlags[DASH] & TF_DASH_PRECHARGE)
            {
               taskFlags[DASH] &= ~TF_DASH_PRECHARGE;
                Serial.print("PrechargeBtn task: ");
                Serial.println(taskFlags[DASH], BIN);
            }

            if(taskFlags[DASH] & TF_DASH_RTD)
            {
               taskFlags[DASH] &= ~TF_DASH_RTD;
                Serial.print("TF_DASH_RTD task: ");
                Serial.println(taskFlags[DASH], BIN);
            }

            if(taskFlags[DASH] & TF_DASH_WAYNE_WORLD)
            {
               taskFlags[DASH] &= ~TF_DASH_WAYNE_WORLD;
                Serial.print("TF_DASH_WAYNE_WORLD task: ");
                Serial.println(taskFlags[DASH], BIN);
            }

            if(taskFlags[DASH] & TF_DASH_STANDBY)
            {
               taskFlags[DASH] &= ~TF_DASH_STANDBY;
                Serial.print("TF_DASH_STANDBY task: ");
                Serial.println(taskFlags[DASH], BIN);
            }

        }
        break;


        case STAGE_PRECHARGE:
            Serial.println("Precharge Stage");
        break;


        case STAGE_ENERGIZED:
            Serial.println("Energized Stage");
        break;


        case STAGE_DRIVING:
        {
            Serial.println("Driving Stage");            
        }
        break;


        case STAGE_LAUNCH:

        break;


        case STAGE_SHUTDOWN:

        break;


        default:
            //shouldn't get here
        break;
    }

    Serial.println();

    return 0;
}


/** 
 * @brief  
 * @note   
 * @retval 
 */
uint32_t StageManager::processGlcd(void)
{
    //glcd view display updating

    return 0;
}


/** 
 * @brief  
 * @note   
 * @retval 
 */
uint32_t StageManager::processImd(void)
{    
    return 0;
}

/** 
 * @brief  
 * @note   
 * @retval 
 */
uint32_t StageManager::processOrion(void)
{
    return 0;
}


/** 
 * @brief  
 * @note   
 * @retval 
 */
uint32_t StageManager::processPedal(void)
{
    return 0;
}


/** 
 * @brief  
 * @note   
 * @retval 
 */
uint32_t StageManager::processSdCard(void)
{
    return 0;
}

/** 
 * @brief  
 * @note   
 * @retval 
 */
uint32_t StageManager::processUnitek(void)
{
    
    switch(currentStage){
        case STAGE_BOOTUP:

        break;

      
        case STAGE_TEST:

        break;


        case STAGE_STANDBY:

        break;


        case STAGE_PRECHARGE:
            
        break;


        case STAGE_ENERGIZED:

        break;


        case STAGE_DRIVING:
        {
            //set RPM Setpoint in MC
            float pedalPercent=PedalController::getInstance()->getPercentageGas();  //get percentage that the gas pedal is pressed
            uint16_t numericSpeedSetPoint=UnitekController::getInstance()->calculateSpeedSetPoint(pedalPercent);   //calculates speed to send to MC from 0-32767
            //send the speed over CAN to the MC (param: speed value register, upper 8 bits of numeric speed, lower 8 bits of numeric speed)
            CanController::getInstance()->sendUnitekWrite(REG_SPEEDVAL, (uint8_t)(numericSpeedSetPoint >> 8), numericSpeedSetPoint);
        }
        break;


        case STAGE_LAUNCH:

        break;


        case STAGE_SHUTDOWN:

        break;
    }

    return 0;
}


/** 
 * @brief  
 * @note   
 * @retval 
 */
uint32_t StageManager::processBatlog(void)
{
    return 0;
}


/** 
 * @brief  
 * @note   
 * @retval 
 */
uint32_t StageManager::processPrecharge(void)
{
    return 0;
}


/** 
 * @brief  
 * @note   
 * @retval 
 */
uint32_t StageManager::processReadyToDrive(void)
{
    return 0;
}

/** 
 * @brief  
 * @note   
 * @retval 
 */
uint32_t StageManager::processLaunch(void)
{
    return 0;
}


/** 
 * @brief  
 * @note   
 * @retval 
 */
uint32_t StageManager::processShutdown(void)
{
    return 0;
}


/** 
 * @brief  
 * @note   
 * @param  currentStage: 
 * @retval None
 */
void StageManager::resetAllStagesExcept(Stage nonResetStage)
{
    //initially setting all the stage configurations to false, then "enabling" the current Stage
    isStandbyConfigured = false;
    isPrechargeConfigured = false;
    isEnergizedConfigured = false;
    isDrivingConfigured = false;
    isLaunchConfigured = false;


    //checking which stage we're currently in (same as which stage is configured correctly)
    switch(nonResetStage)
    {
        //Standby stage is configured
        case Stage::STAGE_STANDBY:
            isStandbyConfigured = true;
        break;

        
        //Precharge stage is configured
        case Stage::STAGE_PRECHARGE:
            isPrechargeConfigured = true;
        break;


        //Energized stage is configured
        case Stage::STAGE_ENERGIZED:
            isEnergizedConfigured = true;
        break;


        //Driving stage is configured
        case Stage::STAGE_DRIVING:
            isDrivingConfigured = true;
        break;


        //Launch stage is configured
        case Stage::STAGE_LAUNCH:
            isLaunchConfigured = true;
        break;


        default:
            //shouldn't get here
        break;
    }
}


/** 
 * @brief  Contains the initial configuration steps for the standby stage
 * @note   
 * @retval None
 */
void StageManager::configureStandby(void)
{

    //check to make sure this hasn't been ran before for this stage
    if(isStandbyConfigured == false)
    {
        //set variable to "configured"
        resetAllStagesExcept(Stage::STAGE_STANDBY);

        //TODO: Standby setup code
        Serial.println("Standby Stage");



    }
}


/** 
 * @brief  Contains the initial configuration steps for the precharge stage
 * @note   
 * @retval None
 */
void StageManager::configurePrecharge(void)
{

    //check to make sure this hasn't been ran before for this stage
    if(isPrechargeConfigured == false)
    {
        //set variable to "configured"
        resetAllStagesExcept(Stage::STAGE_PRECHARGE);

        //TODO: Precharge setup code
        Serial.print("Precharge Stage");
        
        //set 90% charge
        float batteryVoltage=OrionController::getInstance()->getPackVoltage();
        uint16_t charge90Numeric=UnitekController::getInstance()->calculate90Charge(batteryVoltage);
        CanController::getInstance()->sendUnitekWrite(REG_VAR1, (uint8_t)(charge90Numeric >> 8), charge90Numeric);
        

    }
}


/** 
 * @brief  Contains the initial configuration steps for the energized stage
 * @note   
 * @retval None
 */
void StageManager::configureEnergized(void)
{

    //check to make sure this hasn't been ran before for this stage
    if(isEnergizedConfigured == false)
    {
        //set variable to "configured"
        resetAllStagesExcept(Stage::STAGE_ENERGIZED);

        //TODO: Energized setup code
        Serial.println("Energized Stage");

    }
}


/** 
 * @brief  Contains the initial configuration steps for the driving stage
 * @note   
 * @retval None
 */
void StageManager::configureDriving(void)
{

    //check to make sure this hasn't been ran before for this stage
    if(isDrivingConfigured == false)
    {
        //set variable to "configured"
        resetAllStagesExcept(Stage::STAGE_DRIVING);

        //TODO: Driving setup code
        

    }
}


/** 
 * @brief  Contains the initial configuration steps for the launch stage
 * @note   
 * @retval None
 */
void StageManager::configureLaunch(void)
{

    //check to make sure this hasn't been ran before for this stage
    if(isLaunchConfigured == false)
    {
        //set variable to "configured"
        resetAllStagesExcept(Stage::STAGE_LAUNCH);

        //TODO: Launch setup code
        

    }
}


/** 
 * @brief  
 * @note   Entry condition: EVOS finishes subsystem testing
 *         Exit condition:  Driver requests Precharging
 * @param  &localEventFlags: 
 * @param  urgencyLevel: 
 * @retval 
 */
StageManager::Stage StageManager::processEventsStandby(uint32_t* localEventFlags, Priority urgencyLevel, uint8_t* taskFlags)
{
    Stage currentStage = Stage::STAGE_STANDBY;

    switch(urgencyLevel)
    {
        case PRIORITY_CRITICAL:

            if(*localEventFlags && EF_SHUTDOWN)
            {
                processShutdown();
                
                //clearing the EF so we don't trigger this again
                *localEventFlags &= ~EF_SHUTDOWN;
            }


            if(*localEventFlags && EF_IMD)
            {
                processImd();
                
                //clearing the EF so we don't trigger this again
                *localEventFlags &= ~EF_IMD;
            }

        break;

        
        case PRIORITY_HIGH:
        
            if(*localEventFlags && EF_CAN)
            {
                processCan();   
                
                //clearing the EF so we don't trigger this again
                *localEventFlags &= ~EF_CAN;
            }


            if(*localEventFlags && EF_UNITEK)
            {
                processUnitek();
                
                //clearing the EF so we don't trigger this again
                *localEventFlags &= ~EF_UNITEK;
            }


            if(*localEventFlags && EF_ORION)
            {
                processOrion();
                
                //clearing the EF so we don't trigger this again
                *localEventFlags &= ~EF_ORION;
            }
        
        break;


        case PRIORITY_MEDIUM:

             if(*localEventFlags && EF_COOLING)
            {
                processCooling();
                
                //clearing the EF so we don't trigger this again
                *localEventFlags &= ~EF_COOLING;
            }


            if(*localEventFlags && EF_BATLOG)
            {
                processBatlog();
                
                //clearing the EF so we don't trigger this again
                *localEventFlags &= ~EF_BATLOG;
            }


            if(*localEventFlags && EF_DASH)
            {
                processDash(taskFlags);

                //clearing the EF so we don't trigger this again
                *localEventFlags &= ~EF_DASH;
            }

        break;


        case PRIORITY_LOW:

            if(*localEventFlags && TIMER_F_GLCD)
            {
                processGlcd();
                
                //clearing the EF so we don't trigger this again
                *localEventFlags &= ~TIMER_F_GLCD;
            }


            if(*localEventFlags && TIMER_F_SDCARD)
            {
                processSdCard();
                
                //clearing the EF so we don't trigger this again
                *localEventFlags &= ~TIMER_F_SDCARD;
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
StageManager::Stage StageManager::processEventsPrecharge(uint32_t* localEventFlags, Priority urgencyLevel, uint8_t* taskFlags)
{
    Stage currentStage = Stage::STAGE_PRECHARGE;

    switch(urgencyLevel)
    {
        case PRIORITY_CRITICAL:
            //code here
            if(*localEventFlags && EF_SHUTDOWN)
            {
                processShutdown();
                
                //clearing the EF so we don't trigger this again
                *localEventFlags &= ~EF_SHUTDOWN;
            }


            if(*localEventFlags && EF_IMD)
            {
                processImd();
                
                //clearing the EF so we don't trigger this again
                *localEventFlags &= ~EF_IMD;
            }

        break;

        
        case PRIORITY_HIGH:
            //code here
            if(*localEventFlags && EF_CAN)
            {
                processCan();   
                
                //clearing the EF so we don't trigger this again
                *localEventFlags &= ~EF_CAN;
            }


            if(*localEventFlags && EF_UNITEK)
            {
                processUnitek();
                
                //clearing the EF so we don't trigger this again
                *localEventFlags &= ~EF_UNITEK;
            }


            if(*localEventFlags && EF_ORION)
            {
                processOrion();
                
                //clearing the EF so we don't trigger this again
                *localEventFlags &= ~EF_ORION;
            }
        
        break;


        case PRIORITY_MEDIUM:
            //code here

             if(*localEventFlags && EF_COOLING)
            {
                processCooling();
                
                //clearing the EF so we don't trigger this again
                *localEventFlags &= ~EF_COOLING;
            }


            if(*localEventFlags && EF_BATLOG)
            {
                processBatlog();
                
                //clearing the EF so we don't trigger this again
                *localEventFlags &= ~EF_BATLOG;
            }


            if(*localEventFlags && EF_DASH)
            {
                processDash(taskFlags);
                
                //clearing the EF so we don't trigger this again
                *localEventFlags &= ~EF_DASH;
            }

        break;


        case PRIORITY_LOW:
            //code here
            if(*localEventFlags && TIMER_F_SDCARD)
            {
                processSdCard();
                
                //clearing the EF so we don't trigger this again
                *localEventFlags &= ~TIMER_F_SDCARD;
            }


            if(*localEventFlags && TIMER_F_GLCD)
            {
                processGlcd();
                
                //clearing the EF so we don't trigger this again
                *localEventFlags &= ~TIMER_F_GLCD;
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
StageManager::Stage StageManager::processEventsEnergized(uint32_t* localEventFlags, Priority urgencyLevel, uint8_t* taskFlags)
{
    Stage currentStage = Stage::STAGE_ENERGIZED;

    switch(urgencyLevel)
    {
        case PRIORITY_CRITICAL:
            //code here
            if(*localEventFlags && EF_SHUTDOWN)
            {
                processShutdown();
                
                //clearing the EF so we don't trigger this again
                *localEventFlags &= ~EF_SHUTDOWN;
            }


            if(*localEventFlags && EF_IMD)
            {
                processImd();
                
                //clearing the EF so we don't trigger this again
                *localEventFlags &= ~EF_IMD;
            }

        break;

        
        case PRIORITY_HIGH:
            //code here
            if(*localEventFlags && EF_CAN)
            {
                processCan();   
                
                //clearing the EF so we don't trigger this again
                *localEventFlags &= ~EF_CAN;
            }


            if(*localEventFlags && EF_UNITEK)
            {
                processUnitek();
                
                //clearing the EF so we don't trigger this again
                *localEventFlags &= ~EF_UNITEK;
            }


            if(*localEventFlags && EF_ORION)
            {
                processOrion();
                
                //clearing the EF so we don't trigger this again
                *localEventFlags &= ~EF_ORION;
            }
        
        break;


        case PRIORITY_MEDIUM:
            //code here

             if(*localEventFlags && EF_COOLING)
            {
                processCooling();
                
                //clearing the EF so we don't trigger this again
                *localEventFlags &= ~EF_COOLING;
            }


            if(*localEventFlags && EF_BATLOG)
            {
                processBatlog();
                
                //clearing the EF so we don't trigger this again
                *localEventFlags &= ~EF_BATLOG;
            }


            if(*localEventFlags && EF_DASH)
            {
                processDash(taskFlags);
                
                //clearing the EF so we don't trigger this again
                *localEventFlags &= ~EF_DASH;
            }

        break;


        case PRIORITY_LOW:
            //code here
            if(*localEventFlags && TIMER_F_GLCD)
            {
                processGlcd();
                
                //clearing the EF so we don't trigger this again
                *localEventFlags &= ~TIMER_F_GLCD;
            }


            if(*localEventFlags && TIMER_F_SDCARD)
            {
                processSdCard();
                
                //clearing the EF so we don't trigger this again
                *localEventFlags &= ~TIMER_F_SDCARD;
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
StageManager::Stage StageManager::processEventsDriving(uint32_t* localEventFlags, Priority urgencyLevel, uint8_t* taskFlags)
{
    Stage currentStage = Stage::STAGE_STANDBY;

    switch(urgencyLevel)
    {
        case PRIORITY_CRITICAL:
            //code here
            if(*localEventFlags && EF_SHUTDOWN)
            {
                processShutdown();
                
                //clearing the EF so we don't trigger this again
                *localEventFlags &= ~EF_SHUTDOWN;
            }


            if(*localEventFlags && EF_IMD)
            {
                processImd();
                
                //clearing the EF so we don't trigger this again
                *localEventFlags &= ~EF_IMD;
            }

        break;

        
        case PRIORITY_HIGH:
            //code here
            if(*localEventFlags && EF_CAN)
            {
                processCan();   
                
                //clearing the EF so we don't trigger this again
                *localEventFlags &= ~EF_CAN;
            }


            if(*localEventFlags && EF_UNITEK)
            {
                processUnitek();
                
                //clearing the EF so we don't trigger this again
                *localEventFlags &= ~EF_UNITEK;
            }


            if(*localEventFlags && EF_ORION)
            {
                processOrion();
                
                //clearing the EF so we don't trigger this again
                *localEventFlags &= ~EF_ORION;
            }
        
        break;


        case PRIORITY_MEDIUM:
            //code here

             if(*localEventFlags && EF_COOLING)
            {
                processCooling();
                
                //clearing the EF so we don't trigger this again
                *localEventFlags &= ~EF_COOLING;
            }


            if(*localEventFlags && EF_BATLOG)
            {
                processBatlog();
                
                //clearing the EF so we don't trigger this again
                *localEventFlags &= ~EF_BATLOG;
            }


            if(*localEventFlags && EF_DASH)
            {
                processDash(taskFlags);
                
                //clearing the EF so we don't trigger this again
                *localEventFlags &= ~EF_DASH;
            }

        break;


        case PRIORITY_LOW:
            
            //
            if(*localEventFlags && TIMER_F_PEDAL)
            {
                processPedal();

                //clearing the Flag so we don't trigger this again
                *localEventFlags &= ~TIMER_F_PEDAL;
            }


            if(*localEventFlags && TIMER_F_GLCD)
            {
                processGlcd();
                
                //clearing the Flag so we don't trigger this again
                *localEventFlags &= ~TIMER_F_GLCD;
            }


            if(*localEventFlags && TIMER_F_SDCARD)
            {
                processSdCard();
                
                //clearing the Flag so we don't trigger this again
                *localEventFlags &= ~TIMER_F_SDCARD;
            }

        break;

    } //End switch

    return currentStage;
}