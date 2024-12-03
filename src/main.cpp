#include <Arduino.h>
#include "secrets/wifi.h"
#include "wifi_connect.h"
#include <WiFiClientSecure.h>
#include "ca_cert.h"
#include <ESP32Servo.h>
#include "secrets/mqtt.h"
#include <PubSubClient.h>
#include "MQTT.h"
#include <Ticker.h> 

#define WATER_SENSOR_PIN 36U
#define RGB_LED_RED 23U
#define RGB_LED_GREEN 22U
#define RGB_LED_BLUE 21U
#define SERVO_PIN 13U

#define MAX_VALUE 2500.0

const char *water_status_topic = "esp32/water_status";
const char *water_status1_topic = "esp32/water_status1";
const char *servo_control_topic = "esp32/servo_control";

WiFiClientSecure tlsClient;
PubSubClient mqttClient(tlsClient);

Servo servo;

Ticker waterLevelTicker;
int waterLevel = 0;

void setRGBColor(uint8_t red, uint8_t green, uint8_t blue) {
    analogWrite(RGB_LED_RED, red);
    analogWrite(RGB_LED_GREEN, green);
    analogWrite(RGB_LED_BLUE, blue);
}

void checkWaterLevel() {
    int waterLevel = analogRead(WATER_SENSOR_PIN);
    int valueWL = (int)((float)waterLevel / MAX_VALUE * 100);

    String status;
    if (waterLevel >= 1800) {
        setRGBColor(255, 0, 255); // Green
        status = "Safe";
    } else if (waterLevel > 1200 && waterLevel <= 1800) {
        setRGBColor(0, 0, 255); // Yellow
        status = "Warning";
    } else {
        setRGBColor(0, 255, 255); // Red
        status = "Danger";
    }

    mqttClient.publish(water_status_topic, String(valueWL).c_str(), false);
    mqttClient.publish(water_status1_topic, String(waterLevel).c_str(), false);

    Serial.print("Water Level: ");
    Serial.println(waterLevel);
    Serial.print("LED Status: ");
    Serial.println(status);
    Serial.print(valueWL);
    Serial.println("%");
}


void mqttCallback(char *topic, uint8_t *payload, unsigned int length) {
    char message[length + 1];
    memcpy(message, payload, length);
    message[length] = '\0';

    if (strcmp(topic, servo_control_topic) == 0) {
        if (strcmp(message, "Permission") == 0) {
            servo.write(180); 
            Serial.println("Servo: Permission granted, rotating to 90 degrees");
        } else if (strcmp(message, "Stop") == 0) {
            servo.write(0); 
            Serial.println("Servo: Stopped, returning to 0 degrees");
        }
    }
}

void setup() {
    Serial.begin(115200);
    analogSetAttenuation(ADC_11db);

    setup_wifi(WiFiSecrets::ssid, WiFiSecrets::pass);
    tlsClient.setCACert(ca_cert);

    mqttClient.setServer(HiveMQ::broker, HiveMQ::port);
    mqttClient.setCallback(mqttCallback);

    pinMode(WATER_SENSOR_PIN, INPUT);
    pinMode(RGB_LED_RED, OUTPUT);
    pinMode(RGB_LED_GREEN, OUTPUT);
    pinMode(RGB_LED_BLUE, OUTPUT);

    servo.attach(SERVO_PIN);

    setRGBColor(0, 0, 0);

    waterLevelTicker.attach(1.0, checkWaterLevel);
}

void loop() {
    MQTT::reconnect(mqttClient, WiFi.macAddress().c_str(), HiveMQ::username, HiveMQ::password, servo_control_topic);
    mqttClient.loop();
}
