#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <array>
#include <thread>

#include "header/marquee.h"
#include "header/text.h"
#include "header/commands.h"

int main() 
{
    bool isProgramRunning = true;
    Marquee marquee = Marquee("CSOPESY");
    
    if (!marquee.initializeFont()) return 1;

    // clear screen and allocate console area for marquee and console
    std::cout << "\x1b[2J\x1b[H"
          << "\x1b[" << COMMAND_ROW << "r"
          << "\x1b[" << COMMAND_ROW << ";1H";
            
    // TODO: run marquee animation
    marquee.startAnimation();
    while (isProgramRunning) commandInterface(isProgramRunning, marquee);

    // release allocated area then clear screen
    std::cout << "\x1b[r\x1b[2J\x1b[H";

    return 0;
}