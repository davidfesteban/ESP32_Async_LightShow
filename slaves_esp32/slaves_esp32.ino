#define LED_PIN 2
#define QUEUE_SIZE 4

#include "EspMQTTClient.h"
#include <Arduino.h>

const char* ssid = "Oftersheim";
const char* password = "NaiveTardis";
const char* mqtt_server = "91.121.93.94";  //test.mosquitto.org
const String device = "TOM";
const String topic_action = "slave/action/" + device;
const String topic_reply = "slave/reply/" + device;

TaskHandle_t taskHandle = NULL;
QueueHandle_t dataQueue = NULL;

EspMQTTClient client(
  ssid,
  password,
  mqtt_server,
  "TestClient3344kaWrt67",
  1883);

void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);

  createTask();
  dataQueue = xQueueCreate(QUEUE_SIZE, sizeof(String));
  setupAnimation();

  if (dataQueue == NULL) {
    Serial.println("Queue creation failed");
    return;
  }
}


void createTask() {
  xTaskCreate(
    animationCommander,        // Task function
    "Animation Commander LEDs",  // Name for debugging
    2048,              // Stack size (bytes)
    NULL,              // Parameter to pass
    1,                 // Task priority
    &taskHandle        // Task handle
  );
}

void deleteTask() {
  if (taskHandle != NULL) {
    vTaskDelete(taskHandle);
    taskHandle = NULL;  // Ensure the handle is cleared once the task is deleted.
  }
}

void emptyQueue() {
  String item;
  while (xQueueReceive(dataQueue, &item, (TickType_t)0) == pdTRUE) {
  }
}

void onConnectionEstablished() {

  client.subscribe(topic_action, [](const String& payload) {
    Serial.println(payload);

    if (payload.startsWith(".clean")) {
      deleteTask();
      emptyQueue();
      createTask();
    } else if (!xQueueSend(dataQueue, &payload, portMAX_DELAY)) {
      Serial.println("Failed to send data to queue");
    }

    client.publish(topic_reply, "Buffer space:" + String((int)uxQueueSpacesAvailable(dataQueue)));
  });

  client.publish(topic_reply, "Connected");
}

void loop() {
  client.loop();
}