// timer.c -- Initialises the PIT, and handles clock updates.
//            Written for JamesM's kernel development tutorials.

#include "timer.h"

uint32 tick = 0;
uint32 freq = 0;

static void timer_callback()
{
    tick++;
}

void waitTicks(uint32 dist) {
    uint32 final = tick + dist;
    while(tick < final);
    // Do nothing...
}

void waitSeconds(uint32 dist) {
    uint32 final = tick + dist * freq;
    while(tick < final);
    // Do nothing...
}

void init_timer(uint32 frequency)
{
    freq = frequency;
    // Firstly, register our timer callback.
    register_interrupt_handler(IRQ0, &timer_callback);

    // The value we send to the PIT is the value to divide it's input clock
    // (1193180 Hz) by, to get our required frequency. Important to note is
    // that the divisor must be small enough to fit into 16-bits.
    uint32 divisor = 1193180 / frequency;

    // Send the command byte.
    outportb(0x43, 0x36);

    // Divisor has to be sent byte-wise, so split here into upper/lower bytes.
    uint8 l = (uint8)(divisor & 0xFF);
    uint8 h = (uint8)( (divisor>>8) & 0xFF );

    // Send the frequency divisor.
    outportb(0x40, l);
    outportb(0x40, h);
}
