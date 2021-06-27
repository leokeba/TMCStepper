
#include <Arduino.h>
extern "C" {
    #include <unity.h>
}
#include <TMCStepper.h>
#include <SoftwareSerial.h>

constexpr uint8_t DirPin = 61;
constexpr uint8_t StepPin = 60;
constexpr uint8_t EnablePin = 56;
constexpr uint8_t RxPin = 64;
constexpr uint8_t TxPin = 64;

TMC_HAL::SWSerial swSerial{RxPin, TxPin};
TMC2209Stepper driver{swSerial, 0.11, 0};

void TestCommunication() {
    auto version = driver.version();
    TEST_ASSERT_EQUAL_HEX8_MESSAGE(0x21, version, "Communication error");
}

void TestVersion() {
    auto version = driver.version();
    TEST_ASSERT_EQUAL_UINT8(0x21, version);
}

void TestDirPinIsHigh() {
    digitalWrite(DirPin, HIGH);
    TEST_ASSERT_TRUE(driver.dir());
}

void TestDirPinIsLow() {
    digitalWrite(DirPin, LOW);
    TEST_ASSERT_FALSE(driver.dir());
}

void TestStepPinIsHigh() {
    digitalWrite(StepPin, HIGH);
    TEST_ASSERT_TRUE(driver.step());
}

void TestStepPinIsLow() {
    digitalWrite(StepPin, LOW);
    TEST_ASSERT_FALSE(driver.step());
}

void TestEnablePinIsHigh() {
    digitalWrite(EnablePin, HIGH);
    TEST_ASSERT_TRUE(driver.enn());
}

void TestEnablePinIsLow() {
    digitalWrite(EnablePin, LOW);
    TEST_ASSERT_FALSE(driver.enn());
}

void setup() {
    delay(2000);

    pinMode(EnablePin, OUTPUT);
    pinMode(DirPin, OUTPUT);
    pinMode(StepPin, OUTPUT);

    swSerial.begin(115200);
    driver.begin();

    UNITY_BEGIN();

    RUN_TEST(TestCommunication);
    RUN_TEST(TestVersion);
    RUN_TEST(TestDirPinIsHigh);
    RUN_TEST(TestDirPinIsLow);
    RUN_TEST(TestStepPinIsHigh);
    RUN_TEST(TestStepPinIsLow);
    RUN_TEST(TestEnablePinIsHigh);
    RUN_TEST(TestEnablePinIsLow);

    UNITY_END();
}

void loop() {}
