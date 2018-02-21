/**  A one line description of the class.
 *
 * main.cpp
 * Created 11-06-17 By: Smitty
 *
 * A longer description.
 */

// Unit Testing gaurd
#ifndef UNIT_TEST

#include <IntervalTimer.h>
#include "Manager/StageManager/StageManager.hpp"

//global variable that all the ISRs will flag for their respective event to run
// volatile uint16_t globalEventFlags = 0;
EventTask globalDevices = EventTask();


//Start of ISR declarations
void timerISR() {
    // globalEventFlags |= EF_TIMER;
    globalDevices.assertDeviceEventFlag(TIMER);
}



//---------------------------------------------------------------
// Begin main function
int main(void)
{
    Serial.begin(9600);
    while (!Serial) {
        ; // wait for serial port to connect
    }

    //initialize the local event flag variable
    // uint32_t localEventFlags = 0;
    EventTask localDevices = EventTask();

    //Creating the controller singletons
    //Copying each controller location in memory
    CanController* canC         = CanController::getInstance();
    UnitekController* unitekC   = UnitekController::getInstance();
    OrionController* orionC     = OrionController::getInstance();
    CoolingController* coolingC = CoolingController::getInstance();
    DashController* dashC       = DashController::getInstance();
    ImdController* imdC         = ImdController::getInstance();
    GlcdController* glcdC       = GlcdController::getInstance();
    PedalController* pedalC     = PedalController::getInstance();
    SdCardController* sdCardC   = SdCardController::getInstance();
    BatlogController* batlogC   = BatlogController::getInstance();

    //local instance of the Stage manager class
    StageManager localStage = StageManager();

    //The first step when running is bootup
    StageManager::Stage excecutingStage = StageManager::BOOTUP;

    // using the builtin LED as a status light (for now)
    pinMode(LED_BUILTIN, OUTPUT);
    digitalWriteFast(LED_BUILTIN, 1);


    //Bootup stage functions (anything var declared in an if/else falls out of scope afterward)
        //Calling init functions for each controller
        canC->init();
        unitekC->init();
        orionC->init();
        coolingC->init();
        dashC->init();
        pedalC->init();
        imdC->init();
        glcdC->init();
        sdCardC->init();
        batlogC->init();

        //Configure registers
            //Brownout configuration

        //timer configuration
            //DO NOT START TIMERS HERE
        IntervalTimer myTimer;

        //Dashboard
            //LCD (boot logo)

        if(/* check for ShutdownEF*/ 1 )
        {
            excecutingStage = StageManager::SELF_TEST;
        }
        else
        {
            excecutingStage = StageManager::SHUTDOWN;
        }


    if(excecutingStage == StageManager::SELF_TEST)
    {
        //Teensy SelfTest (internal functions)
        //SdCard check (read data, check if good)
        //Dash test (turn on all LEDS, user confirmation w/ encoder)
        


        if(/* check for ShutdownEF*/ 1 )
        {
            excecutingStage = StageManager::SUBSYSTEM_TEST;
        }
        else
        {
            excecutingStage = StageManager::SHUTDOWN;
        }
    }


    if(excecutingStage == StageManager::SUBSYSTEM_TEST)
    {
        
        //Unitek check if okay
        //Orion check if okay
        //Cooling check if working
        //GLV batlog level check
        
        //assuming everything is okay
            //Notification: All systens go. Ready to Precharge

        if(/* check for ShutdownEF*/ 1 )
        {
            excecutingStage = StageManager::STANDBY;
        }
        else
        {
            excecutingStage = StageManager::SHUTDOWN;
        }
    }


    //Start 1ms timer (1000 usec)
    myTimer.begin(timerISR, 1000);


    //---------------------------------------------------------------
    // Begin main program Super Loop
    while(excecutingStage != StageManager::SHUTDOWN)
    {
        if(excecutingStage == StageManager::STANDBY)
        {
            noInterrupts();
            //Volatile operation for transferring flags from ISRs to local main
            // localEventFlags |= globalEventFlags;
            // globalEventFlags = 0;
            localDevices.setAllDeviceEventFlag(globalDevices.getAllDeviceEventFlag());
            globalDevices.clearAllDeviceEventFlag();
            interrupts();

            
            //FIXME: Implement helper functions to avoid all these if()s 
            //       Such as: checkHighPriorityStandby(), checkNormalPriorityStandby(), etc
            //       HINT: implement priority event flag registers


            // if(localEventFlags && EF_SHUTDOWN)
            // {
            //     localStage.processShutdown();
                
            //     //clearing the EF so we don't trigger this again
            //     localEventFlags &= ~EF_SHUTDOWN;
            // }


            // if(localEventFlags && EF_IMD)
            // {
            //     localStage.processImd();
                
            //     //clearing the EF so we don't trigger this again
            //     localEventFlags &= ~EF_IMD;
            // }


            // //Timer EF check
            // if(localEventFlags && EF_TIMER)
            // {
            //     //bit shifting the timer Task Flags (TFs) to the upper half of the localEF var
            //     localEventFlags |= localStage.processTimers() << 16;
                
            //     //clearing the EF so we don't trigger this again
            //     localEventFlags &= ~EF_TIMER;
            // }


            //Timer EF check
            if(localDevices.getDeviceEventFlag(TIMER))
            {
                //bit shifting the timer Task Flags (TFs) to the upper half of the localEF var
                // localEventFlags |= localStage.processTimers() << 16;
                localStage.processTimers(&localDevices.getDeviceStatus());

                
                //clearing the EF so we don't trigger this again
                localDevices.clearDeviceEventFlag(TIMER);
            }


            // if(localEventFlags && EF_CAN)
            // {
            //     localStage.processCan();   
                
            //     //clearing the EF so we don't trigger this again
            //     localEventFlags &= ~EF_CAN;
            // }


            // if(localEventFlags && EF_UNITEK)
            // {
            //     localStage.processUnitek();
                
            //     //clearing the EF so we don't trigger this again
            //     localEventFlags &= ~EF_UNITEK;
            // }


            // if(localEventFlags && EF_ORION)
            // {
            //     localStage.processOrion();
                
            //     //clearing the EF so we don't trigger this again
            //     localEventFlags &= ~EF_ORION;
            // }


            // if(localEventFlags && EF_COOLING)
            // {
            //     localStage.processCooling();
                
            //     //clearing the EF so we don't trigger this again
            //     localEventFlags &= ~EF_COOLING;
            // }


            // if(localEventFlags && EF_BATLOG)
            // {
            //     localStage.processBatlog();
                
            //     //clearing the EF so we don't trigger this again
            //     localEventFlags &= ~EF_BATLOG;
            // }


            // if(localEventFlags && EF_DASH)
            // {
            //     localStage.processDash();
                
            //     //clearing the EF so we don't trigger this again
            //     localEventFlags &= ~EF_DASH;
            // }


            // if(localEventFlags && EF_GLCD)
            // {
            //     localStage.processGlcd();
                
            //     //clearing the EF so we don't trigger this again
            //     localEventFlags &= ~EF_GLCD;
            // }


            // if(localEventFlags && EF_SDCARD)
            // {
            //     localStage.processSdCard();
                
            //     //clearing the EF so we don't trigger this again
            //     localEventFlags &= ~EF_SDCARD;
            // }


            // //check for PrechargeEF
            // if(localEventFlags && EF_PRECHARGE)
            // {
            //     localStage.processPrecharge();
                
            //     //clearing the EF so we don't trigger this again
            //     localEventFlags &= ~EF_PRECHARGE;
            // }

        }   //End of Standby if()

        if(excecutingStage == StageManager::DRIVE)
        {
            noInterrupts();
            //Volatile operation for transferring flags from ISRs to local main
            // localEventFlags |= globalEventFlags;
            // globalEventFlags = 0;
            interrupts();
            
            //Driving stuff



        }   //end of super loop ------------------------------------------------------
    }

    //SHUTDOWN function
        //EXTREMELY CRITICAL FUNCTIONS, no looping here
        //close out SdCard logs
        //SCADA_OK signal to false


    return 0;
}

#endif
