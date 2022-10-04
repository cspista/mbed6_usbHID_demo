/*
 * USBHID example from the Mbed Os documentation
 * Link: https://os.mbed.com/docs/mbed-os/v6.15/apis/usbhid.html
 *
 * The program simply sends back and forth reports of 8 random bytes 
 * Steps to reproduce the project:
 * - Start form an empty Mbed Os project 
 * - Add the mbed_app.json file
 * - Copy the content of this file into the main.cpp file
 * - Change the order of parameters when calling the constructor of USBHID in main.cpp,
 *   i. e. write: USBHID HID(true, 8, 8, 0x1234, 0x0006, 0x0001); 
 *
 * This program requires an application on the PC side as well.
 * Please, find the USBHID.py Python example application  at the link above 
 * (the pywinusb Python module should be installaed as well)
 * 
 * Tested by Keil Studio 1.50 and mebed-os 6.16.0
 */
#include <stdio.h>
#include "mbed.h"
#include "USBHID.h"
// Declare a USBHID device
USBHID HID(true, 8, 8, 0x1234, 0x0006, 0x0001);

HID_REPORT output_report = {
    .length = 8,
    .data = {0}
};
HID_REPORT input_report = {
    .length = 0,
    .data = {0}
};

DigitalOut led_out(LED1);

int main(void)
{
    while (1) {

        // Fill the report
        for (int i = 0; i < output_report.length; i++) {
            output_report.data[i] = rand() & UINT8_MAX;
        }

        // Send the report
        HID.send(&output_report);

        // Try to read a msg
        if (HID.read_nb(&input_report)) {
            led_out = !led_out;
            for (int i = 0; i < input_report.length; i++) {
                printf("%d ", input_report.data[i]);
            }
            printf("\r\n");
        }
    }
}

