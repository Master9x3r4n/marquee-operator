#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <array>
#include <thread>

#include "header/marquee.h"
#include "header/text.h"
#include "header/commands.h"

#define HEIGHT 7

int main() 
{
    bool isProgramRunning = true;
    bool isMarqueeRunning = false;
    std::string marqueeInput = "HELLO WORLD!";
    std::vector<std::array<std::string, HEIGHT>> marqueeContainer;
    Marquee marquee = Marquee(marqueeInput);
    
    isProgramRunning = marquee.initializeFont();

    marquee.printMarquee();
    std::cout << "Developer:\n" << "Claro, Stephen Jakobb G.\n\n"; 
    while (isProgramRunning)
    {
        commandInterface(isProgramRunning, isMarqueeRunning, marquee);
    }

    return 0;
}