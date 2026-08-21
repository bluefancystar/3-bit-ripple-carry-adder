# 3-bit-ripple-carry-adder
A physical design of a 3-bit ripple carry adder on a prototyping board. It performs unsigned binary addition and outputs in both binary and hexadecimal via LEDs and a single seven-segment display respectively.

This process is done by utilizing IC chips with logic gates prepackaged inside of them. The decoding is done through an ESP32 microcontroller that is programmed to read the voltage of the LED binary output and perform a simple algorithm to display the hexadecimal value of the binary output on the single seven-segment display.
