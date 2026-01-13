# Optical Communications on an STM32

This repository contains code for implementing optical communications on an STM32 microcontroller. The code is written in C for the STM32F446RE microcontroller. 

## Overview

It utilizes a completely bare-metal approach to implement a custom communications protocol. This was done to optimize performance and reduce code complexity, as well as to provide a deeper understanding of the underlying hardware and software architecture.

### Bare-Metal Approach

For this project, I wrote bare-metal code to directly control the microcontroller's peripherals, such as the GPIO pins and timers. Everything is done by accessing the registers directly, without any abstractions of any kind. 

In order to do this, I had to write the startup code manually, in C (A future improvement will be to do so in Assembly, as is traditional for startup code). I also had to write the linker file manually, as is traditional for bare-metal projects. 

You can look at the header file STM32F446RE.h in the 'include' directory of either the Receiver or Transmitter project.

### Protocol Details

This protocol is based on the manchester line encoding scheme. Manchester encoding is a form of differential encoding that is used to transmit digital data over a single wire. It is a self-clocking scheme, meaning that the receiver can determine the bit rate by counting the number of transitions in the signal. This allows for consistent timing and easy clock recovery. 

I designed the protocol such that it uses a start byte, followed by a sequence of data bytes of arbitrary number, followed by a checksum byte of some sort (CRC-8 used), and an end byte. If the checksum is incorrect, the receiver will discard the packet and wait for the next one.


## Possible improvements (In order of difficulty/complexity)

1. Rewrite the startup code in Assembly.
2. Make the protocol actually usable by implementing ordered, error checked delivery similar to the TCP protocol, allowed for transmission of large files.
3. Rewrite everything in Rust.
4. Rewrite everything in Assembly.
