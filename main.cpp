#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <array>
#include <thread>

#include "helpers/headers/marquee.h"
#include "helpers/headers/text.h"
#include "helpers/headers/commands.h"

int main() 
{
    bool isProgramRunning = true;
    Marquee marquee = Marquee("CSOPESY");
    
    if (!marquee.initializeFont()) return 1;

    // clear screen and allocate console area for marquee and console
    std::cout << "\x1b[2J\x1b[H"
          << "\x1b[" << COMMAND_ROW << "r"
          << "\x1b[" << COMMAND_ROW << ";1H";
            
    // main marquee + thing
    marquee.startAnimation();
    displayDefault();
    while (isProgramRunning) 
        commandInterface(isProgramRunning, marquee);

    // release allocated area then clear screen
    std::cout << "\x1b[r\x1b[2J\x1b[H";
    std::cout << "Terminating...\n";

    return 0;
}