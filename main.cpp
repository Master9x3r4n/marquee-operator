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
    std::vector<std::array<std::string, 7>> characters = initializeFont();

    bool isProgramRunning = true;
    std::string marqueeText = "CSOPESY";
    bool isMarqueeRunning = false;
    int refreshSpeed = 0;

    clear_screen();
    while (isProgramRunning)
    {
        printMarquee(characters, marqueeText);
        command_interface(isMarqueeRunning, marqueeText, refreshSpeed, isProgramRunning);
        clear_screen();
    }
}