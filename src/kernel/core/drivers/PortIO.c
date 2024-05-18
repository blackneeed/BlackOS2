// Created by Blackneeed

#include <stdint.h>

void outportb(uint16_t port, uint8_t val) {
    __asm__ volatile ("outb %0, %1" : : "a"(val), "Nd"(port));
}

uint8_t inportb(uint16_t port) {
    uint8_t read;
    __asm__ volatile ("inb %1, %0" : "=a"(read) : "Nd"(port));
    return read;
}