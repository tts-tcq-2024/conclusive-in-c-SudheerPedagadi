#include "typewise-alert.h"
#include <stdio.h>

BreachType inferBreach(double value, double lowerLimit, double upperLimit) {
    if (value < lowerLimit) {
        return TOO_LOW;
    }
    if (value > upperLimit) {
        return TOO_HIGH;
    }
    return NORMAL;
}

BreachType classifyTemperatureBreach(CoolingType coolingType, double temperatureInC) {
    static const struct {
        int lowerLimit;
        int upperLimit;
    } coolingLimits[] = {
        {0, 35},  // PASSIVE_COOLING
        {0, 45},  // HI_ACTIVE_COOLING
        {0, 40}   // MED_ACTIVE_COOLING
    };
    
    return inferBreach(temperatureInC, coolingLimits[coolingType].lowerLimit, coolingLimits[coolingType].upperLimit);
}

void checkAndAlert(AlertTarget alertTarget, BatteryCharacter batteryChar, double temperatureInC) {
    BreachType breachType = classifyTemperatureBreach(batteryChar.coolingType, temperatureInC);
    
    if (alertTarget == TO_CONTROLLER) {
        sendToController(breachType);
    } else if (alertTarget == TO_EMAIL) {
        sendToEmail(breachType);
    }
}

void sendToController(BreachType breachType) {
    const unsigned short header = 0xfeed;
    printf("%x : %x\n", header, breachType);
}

void sendToEmail(BreachType breachType) {
    const char* recipient = "a.b@c.com";
    printf("To: %s\n", recipient);
    
    const char* emailMessage = NULL;

    if (breachType == TOO_LOW) {
        emailMessage = "the temperature is too low\n";
    } else if (breachType == TOO_HIGH) {
        emailMessage = "the temperature is too high\n";
    } else {
        emailMessage = "the temperature is normal\n";
    }
    
    printf("%s", emailMessage);
}
