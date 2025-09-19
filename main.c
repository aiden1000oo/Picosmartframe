#include "pico/stdlib.h"
#include "display_utils.h"
#include <stdio.h>

void wait_until_next_minute() {
    // Placeholder: wait 60 seconds; replace with RTC logic if needed
    sleep_ms(60000);
}

int main() {
    stdio_init_all();

    while (true) {
        char time_str[6];
        snprintf(time_str, sizeof(time_str), "12:34"); // Replace with RTC for real time

        compose_display(display_buffer, time_str);

        // Optional: send display_buffer to USB MSC or directly to screen

        wait_until_next_minute();
    }
}
