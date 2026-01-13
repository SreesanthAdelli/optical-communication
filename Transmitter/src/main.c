#include "GPIO.h"
#include "utilities.h"
#include "data.h"
#include "transmit.h"
#include "timer.h"
#include "clock.h"
#include <stdint.h>
#include <stdbool.h>
#define LASER_PIN               6
#define LED_PIN                 5
#define SONG_SIZE               21
#define PACKET_SIZE             4
#define START_BYTE             0xFF
#define END_BYTE               0b10101010


// We are going to transmit a song, represented as an array of 8-bit values. Each value corresponds to a note, 
// where the 8 bits represents the frequency, where the value of the byte is multiplied by 20. This gives us a range of 0 - 5100 Hz.

const uint8_t song[] = {
    10, 20, 30, 40, 50, 60, 70, 80, 90, 100,
    100, 90, 80, 70, 60, 50, 40, 30, 20, 10,
    0
};

int main(void) {

    // Enable GPIOA clock
    initializeGPIOA();

    // Configure PA6 as output (Laser control)
    setPinDigitalOutput(LASER_PIN);
    setPinDigitalOutput(LED_PIN);

    // Start the clock
    systemClock_20MHz();

    // Start the timer
    startTimer();

    uint8_t buffer[1];
    uint8_t packet[PACKET_SIZE];
    uint8_t song_index = 0;

    while(1) {
        initBuffer(song[song_index], buffer, 1);
        song_index = (song_index + 1) % SONG_SIZE;
        createPacket(START_BYTE, buffer, END_BYTE, packet);               // Start byte: 0xFF, End byte: 0x00
        transmitPacket(packet, PACKET_SIZE);
    }

    return 0; // Never reached
}
