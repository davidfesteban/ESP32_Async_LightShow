#define N_LEDS 144
#define LED_STRIP_PIN 15
#define NUMPIXELS 60

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>
#endif

Adafruit_NeoPixel pixels(NUMPIXELS, LED_STRIP_PIN, NEO_GRB + NEO_KHZ800);

void setupAnimation() {
  
#if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
  clock_prescale_set(clock_div_1);
#endif

  pixels.begin();
}

void off() {
  Serial.println("OFF ops");
  vTaskDelay(pdMS_TO_TICKS(2000));

  //vTaskDelete(NULL); No need of autodeletion because of buffer
}

void on() {
  Serial.println("ON ops");
  vTaskDelay(pdMS_TO_TICKS(1000));
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
      pixels.clear();
      pixels.show();
      //Serial.println("I AM OFF");
      //digitalWrite(LED_PIN, LOW);
    } else if (data.startsWith("ON")) {
      on();

      for (int i = 0; i < NUMPIXELS; i++) {

        pixels.setPixelColor(i, pixels.Color(0, 150, 0));
        pixels.show();
        delay(500);
      }
      //digitalWrite(LED_PIN, HIGH);
      Serial.println("ON");
    } else {
      Serial.println("Waiting for queue...");
    }

    client.publish(topic_reply, "Buffer space:" + String((int)uxQueueSpacesAvailable(dataQueue)));
  }
}