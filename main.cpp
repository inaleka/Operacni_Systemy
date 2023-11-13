/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"
#include "cstring"
#include "string"

#define dots 100ms
#define dashes 500ms
#define pause 1000ms

using std::string;
DigitalOut led(LED1);

string letterToMorse(char in_letter){
    string out_string;
    switch (in_letter){
        case 'a': out_string = ".-"; break;
        case 'b': out_string = "-..."; break;
        case 'c': out_string = "-.-."; break;
        case 'd': out_string = "-.."; break;
        case 'e': out_string = "."; break;
        case 'f': out_string = "..-."; break;
        case 'g': out_string = "--."; break;
        case 'h': out_string = "...."; break;
        case 'i': out_string = ".."; break;
        case 'j': out_string = ".---"; break;
        case 'k': out_string = "-.-"; break;
        case 'l': out_string = ".-.."; break;
        case 'm': out_string = "--"; break;
        case 'n': out_string = "-."; break;
        case 'o': out_string = "---"; break;
        case 'p': out_string = ".--."; break;
        case 'q': out_string = "--.-"; break;
        case 'r': out_string = ".-."; break;
        case 's': out_string = "..."; break;
        case 't': out_string = "-"; break;
        case 'u': out_string = "..-"; break;
        case 'v': out_string = "...-"; break;
        case 'w': out_string = ".--"; break;
        case 'x': out_string = "-..-"; break;
        case 'y': out_string = "-.--"; break;
        case 'z': out_string = "--.."; break;
        default: out_string = ""; break;
    }
    return out_string;
}

void processMorseCode(std::string& morseCode) {
    for (char c : morseCode) {
        if(c == '.'){
            led = 0; 
            ThisThread::sleep_for(dots);
        }else if(c == '-'){
            led = 0; 
            ThisThread::sleep_for(dashes);
        }else{
            break;
        }
        led = 1;
        ThisThread::sleep_for(pause);
    }
}

int main()
{
    while (1) {
        std::string name = "sos";
        std::string morseCode = "";
        for (char letter : name) {
            morseCode = morseCode + letterToMorse(letter);
        }
        processMorseCode(morseCode);
    }
}