#include "GPIO.h"
#include "utilities.h"
#include <stdint.h>
#define PACKET_SIZE 4
#define START_BYTE 0xFF
#define FREQ_SCALE 20


#define LED 4
#define PA6 6

typedef struct {
    uint8_t buffer[256];
    uint16_t head;
    uint16_t tail;
    uint16_t size;
} CircularBuffer;

CircularBuffer rx_buffer;


int main(void) {
    // --- 1. Initialize system ---
    systemInit();           // GPIOs, timers, clocks
    pwmInit();              // Hardware PWM for speaker/LED
    circularBufferInit(&rx_buffer);

    // --- 2. Main polling loop ---
    while (1) {

        // Step A: Decode incoming Manchester bits into bytes
        uint8_t decoded_byte;
        while (manchesterDecodeByte(&decoded_byte)) {
            pushToCircularBuffer(&rx_buffer, decoded_byte);
        }

        // Step B: Parse packets from circular buffer
        uint8_t packet[PACKET_SIZE];
        while (circularBufferHasBytes(&rx_buffer, PACKET_SIZE)) {

            if (!peekCircularBuffer(&rx_buffer, 0) == START_BYTE) {
                discardByte(&rx_buffer);    // skip invalid start
                continue;
            }

            for (int i = 0; i < PACKET_SIZE; i++) {
                packet[i] = popCircularBuffer(&rx_buffer);
            }

            if (!checkCRC(packet, PACKET_SIZE)) {
                continue; // invalid packet → hold last frequency
            }

            // Step C: Update PWM frequency
            uint8_t freq_byte = packet[2];
            setPWMFrequency(freq_byte * FREQ_SCALE);
        }

        // PWM continues running at last frequency until next valid packet
    }

    return 0; // Never reached
}
