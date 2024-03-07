# Dancing Club Lighting Control System

## Introduction

This repository contains the code for a lighting control system designed for a dancing club environment, showcasing a synchronized light show inspired by microcontroller-driven LED displays. Our goal is to replicate the mesmerizing effects seen in examples like these:

- [Dancing LEDs Example 1](https://www.youtube.com/watch?v=HvrCyIZb5q8)
- [Dancing LEDs Example 2](https://www.youtube.com/watch?v=-Rot9uaVO8s)

The project serves as a Proof of Concept (PoC) to demonstrate advanced lighting control using a network of microcontrollers (ESP32 WROOM 32) as slaves with a Raspberry Pi acting as the master controller.

## Dependencies

The project relies on the following libraries, which need to be installed with the Arduino IDE:

- **EspMQTTClient** by Patric Lapointe: Facilitates communication between ESP32 devices and the MQTT broker on the Raspberry Pi.
- **FreeRTOS** by Richard Barry: Used for multitasking and managing concurrent processes on the ESP32.
- **PubSubClient** by Nick O'Leary: Utilized for MQTT messaging, particularly during testing and rollout phases.

## Project Context and Innovations

The initiative to develop this lighting control system comes from a desire to combine technology with art in a dance club setting. The system aims to control a vast array of LED lights in synchronization with music and dance performances, creating an immersive experience.

### Challenges and Solutions

Transitioning from high-level programming concepts typically employed in Java development, this project presented an opportunity to tackle hardware limitations head-on. The ESP32 WROOM 32 microcontroller, with its limited heap and stack memory, posed a significant challenge.

Our initial approach, heavily reliant on object-oriented principles such as extensive use of models, entities, Data Transfer Objects (DTOs), and constant serialization/deserialization, was quickly reevaluated in favor of a more hardware-efficient strategy.

To effectively manage the constraints and achieve our ambitious goals, we introduced several innovative solutions:

- **Queues and Asynchronous Operations**: We leveraged FreeRTOS queues to manage data flow and asynchronous reading from MQTT, alongside asynchronous execution of light animations. This approach significantly improved the efficiency of data handling and task scheduling.
- **Command Pattern**: We adopted the command pattern to encapsulate all requests in objects, allowing for parameterization of clients with queues, requests, and operations. This pattern provided a flexible and scalable way to extend the system's functionality and manage complex sequences of LED animations.

Given the project's goal of managing approximately 10 million values to control the lighting (considering 10 dancers, RGB LEDs, up to 1000 LEDs per dancer, a 20 ms refresh rate, and a 5-second buffer), these innovations were crucial in optimizing memory usage and processing power to achieve smooth and synchronized light effects.

## Conclusion

This PoC stands as a testament to the creative potential of integrating modern microcontroller technology with the performing arts. It highlights not only the technical challenges encountered when working within the constraints of embedded systems but also the innovative solutions that emerge from such endeavors.






