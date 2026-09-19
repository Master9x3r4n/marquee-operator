#ifndef MARQUEE_H
#define MARQUEE_H

#include <array>
#include <atomic>
#include <mutex>
#include <string>
#include <thread>
#include <vector>

constexpr int HEIGHT = 7;
constexpr int COMMAND_ROW = HEIGHT + 2;

class Marquee
{
private:
    std::vector<std::array<std::string, HEIGHT>> marqueeChars;
    std::array<std::string, HEIGHT> marqueeText;
    std::string inputText;

    std::atomic<int> refreshSpeed;
    std::atomic<bool> running;
    std::atomic<bool> quit;

    std::mutex textMutex;
    std::thread worker;

public:
    Marquee(std::string txt = "csopesy", int rspd = 80);

    Marquee(const Marquee&) = delete;
    Marquee& operator=(const Marquee&) = delete;

    ~Marquee();

    void setText(std::string txt);
    std::string getText();
    void setSpeed(int spd);
    int getSpeed();
    bool isRunning();
    void setRunning(bool run);
    void startAnimation(int screenW = 120);
    void shutdown();
    bool initializeFont();

private:
    void animationLoop(int screenW);
    void generateMarqueeText();
};

#endif