#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>

using namespace std;

void view_help() {
    cout << "help - displays the commands and its description\n";
    cout << "start_marquee - starts the marquee \"animation\"\n";
    cout << "stop_marquee - stops the marquee \"animation\"\n";
    cout << "set_text <text> - accepts a text input and displays it as a marquee\n";
    cout << "set_speed <speed> - sets the marquee animation refresh in milliseconds\n";
    cout << "exit - terminate the console\n";
}

void set_text(string& marqueeText, vector<string> args) {
    if (args.size() < 2)
        cout << "Invalid arguments. Usage: set_text <text>. Use \"help\" for more information\n";
    else
        marqueeText = args[1];
}

void set_speed(int& refreshSpeed, vector<string> args) {
    if (args.size() < 2)
        cout << "Invalid arguments. Usage: set_speed <text>. Use \"help\" for more information\n";
    else
        refreshSpeed = stoi(args[1]);
}