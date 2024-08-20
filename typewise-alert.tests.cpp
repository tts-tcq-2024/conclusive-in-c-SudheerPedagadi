#include <gtest/gtest.h>
#include "typewise-alert.h"

TEST(TypeWiseAlertTestSuite, InfersBreachAccordingToLimits) {
    EXPECT_EQ(inferBreach(12, 20, 30), TOO_LOW);
    EXPECT_EQ(inferBreach(25, 20, 30), NORMAL);
    EXPECT_EQ(inferBreach(35, 20, 30), TOO_HIGH);
}

TEST(TypeWiseAlertTestSuite, ClassifiesTemperatureBreachCorrectly) {
    EXPECT_EQ(classifyTemperatureBreach(PASSIVE_COOLING, 36), TOO_HIGH);
    EXPECT_EQ(classifyTemperatureBreach(HI_ACTIVE_COOLING, 46), TOO_HIGH);
    EXPECT_EQ(classifyTemperatureBreach(MED_ACTIVE_COOLING, 39), NORMAL);
    EXPECT_EQ(classifyTemperatureBreach(PASSIVE_COOLING, 20), NORMAL);
}

TEST(TypeWiseAlertTestSuite, SendsAlertToController) {
    BatteryCharacter batteryChar = {PASSIVE_COOLING, "BrandX"};
    checkAndAlert(TO_CONTROLLER, batteryChar, 36);
    // Check stdout or other means to ensure the alert was sent to the controller
}

TEST(TypeWiseAlertTestSuite, SendsAlertToEmail) {
    BatteryCharacter batteryChar = {HI_ACTIVE_COOLING, "BrandY"};
    checkAndAlert(TO_EMAIL, batteryChar, 46);
    // Check stdout or other means to ensure the alert was sent via email
}
