#define N_LEDS 144

void off() {
  Serial.println("OFF ops");
  vTaskDelay(pdMS_TO_TICKS(2000));

  //vTaskDelete(NULL); No need of autodeletion because of buffer
}

void on() {
  Serial.println("ON ops");
  vTaskDelay(pdMS_TO_TICKS(10000));
}

void animations(void *pvParameters) {
  for (;;) {
    String data;
    if (xQueueReceive(dataQueue, &data, portMAX_DELAY)) {
      // Process the received data
      Serial.println("Received data: " + data);
    }

    if (data.startsWith("OFF")) {
      off();
      //Serial.println("I AM OFF");
      //digitalWrite(LED_PIN, LOW);
    } else if (data.startsWith("ON")) {
      on();
      //digitalWrite(LED_PIN, HIGH);
      //Serial.println("I AM AH?");
    } else {
      Serial.println("Waiting for queue...");
    }

    client.publish(topic_reply, "Buffer space:" + String((int)uxQueueSpacesAvailable(dataQueue)));
  }
}