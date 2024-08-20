#include "typewise-alert.h"
#include <stdio.h>

// Define limits in a static array for better modularity
typedef struct {
    int lowerLimit;
    int upperLimit;
} CoolingLimits;

static const CoolingLimits coolingLimits[] = {
    {0, 35},  // PASSIVE_COOLING
    {0, 45},  // HI_ACTIVE_COOLING
    {0, 40}   // MED_ACTIVE_COOLING
};

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
    CoolingLimits limits = coolingLimits[coolingType];
    return inferBreach(temperatureInC, limits.lowerLimit, limits.upperLimit);
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
    const char* recepient = "a.b@c.com";
    printf("To: %s\n", recepient);
    switch (breachType) {
        case TOO_LOW:
            printf("Hi, the temperature is too low\n");
            break;
        case TOO_HIGH:
            printf("Hi, the temperature is too high\n");
            break;
        case NORMAL:
            printf("Hi, the temperature is normal\n");
            break;
    }
}
