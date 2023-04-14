#include <unity.h>
#include <Arduino.h>
#include "../src/firebase.h"
#include "../src/wifi.h"

void setUp(void) {
    // set up any resources or variables needed for the tests
    WifiConnect();
    FireStoreConnect();  
}

void tearDown(void) {
    // clean up any resources or variables used in the tests
}

void test_getDocument() {
    TEST_ASSERT_EQUAL_INT(5, getDocument());
}

void setup() {
    UNITY_BEGIN();

    RUN_TEST(test_getDocument);

    UNITY_END();
}

void loop() {
}