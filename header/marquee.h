#include <algorithm>
#include <array>
#include <atomic>
#include <chrono>
#include <climits>
#include <fstream>
#include <iostream>
#include <mutex>
#include <string>
#include <thread>
#include <utility>
#include <vector>

constexpr int HEIGHT = 7;
constexpr int COMMAND_ROW = HEIGHT + 2;

class Marquee
{
private:
    std::vector<std::array<std::string, HEIGHT>> marqueeChars;
    std::array<std::string, HEIGHT> marqueeText;
    std::string inputText;
    
    // use atomic for thread safe operations
    std::atomic<int> refreshSpeed;
    std::atomic<bool> running;
    std::atomic<bool> quit;
    
    std::mutex textMutex; //protect shared data from being accessed by multiple threads at a time, in this case for a text
    std::thread worker; //thread the marquee belongs to

public:
    // Constructor
    Marquee(std::string txt = "csopesy", int rspd = 80)
    : inputText(std::move(txt)), refreshSpeed(rspd), running(false), quit(false) {}

    // Make Marquee object a singleton (single instance cannot be copied)
    Marquee(const Marquee&) = delete;
    Marquee& operator = (const Marquee&) = delete;

    ~Marquee()
    {
        shutdown();
    }


    void setText(std::string txt)
    {
        // locks textMutex from being accessed by multiple threads (like locking a toilet stall, its in use so prevent race condition)
        std::lock_guard<std::mutex> lock(textMutex);

        // content that only 1 thread accesses at a time
        inputText = txt;
        generateMarqueeText();

        //automatically gets unlocked when lock is out of scope
    }

    std::string getText()
    {
        std::lock_guard<std::mutex> lock(textMutex);
        return inputText;
    }

    void setSpeed(int spd)
    {
        refreshSpeed = std::max(1, spd);
    }

    int getSpeed()
    {
        return refreshSpeed;
    }

    bool isRunning()
    {
        return running;
    }

    void setRunning(bool run)
    {
        running = run;
    }

    // void printMarquee()
    // {
    //     for (int j = 0; j < HEIGHT; j ++)
    //         std::cout << marqueeText[j] << "\n"; 

    // }

    void startAnimation(int screenW = 120)
    {
        if (worker.joinable()) // if active thread, then no anim
            return;

        // init for worker, make it an active thread for the animation loop
        quit = false;
        worker = std::thread(&Marquee::animationLoop, this, screenW);
        
    }

    void shutdown()
    {
        quit = true;
        if (worker.joinable()) // block thread
            worker.join();
    }
    
    // While I originally made this function by hand with AI assistance, I regenerated the code to accomodate for the fixed widths
    bool initializeFont()
    {
        std::ifstream inputFile("text/ascii_font.txt");
        marqueeChars.clear();
    
        if (!inputFile.is_open()) {
            std::cerr << "Error: Could not open ascii_font.txt" << std::endl;
            return false;
        }
    
        int j = 0;
        std::array<std::string, HEIGHT> character;
        std::string currLine;
    
        while (std::getline(inputFile, currLine))
        {
            // Guard against short/long lines: pad or truncate so all rows match
            // (optional but safer — remove if your file is guaranteed uniform)
            character[j] = currLine;
            j++;
    
            if (j == HEIGHT)
            {
                // Find bounding box of non-space columns across all rows
                int left  = INT_MAX;
                int right = -1;
                for (const std::string& row : character)
                {
                    for (int c = 0; c < (int)row.size(); ++c)
                    {
                        if (row[c] != ' ')
                        {
                            left  = std::min(left, c);
                            right = std::max(right, c);
                        }
                    }
                }
    
                std::array<std::string, HEIGHT> trimmed;
    
                if (right < left)
                {
                    // All-space glyph (the space character). Give it a fixed width.
                    for (int r = 0; r < HEIGHT; ++r)
                        trimmed[r] = "      ";   // 5 cols wide, adjust to taste
                }
                else
                {
                    int width = right - left + 1;
                    for (int r = 0; r < HEIGHT; ++r)
                        trimmed[r] = character[r].substr(left, width);
                }
    
                marqueeChars.push_back(trimmed);
                j = 0;
            }
        }
    
        inputFile.close();
        {
            std::lock_guard<std::mutex> lock(textMutex);
            generateMarqueeText();
        }
        return true;
    }

private:
    // Runs on the worker thread until shutdown().
    void animationLoop(int screenW)
    {
        int pos = 0;
        while (!quit)
        {
            // frame builds the output string
            std::string frame = "\x1b" "7"; // save cursor position

            {
                // lock this thread from being used
                std::lock_guard<std::mutex> lock(textMutex);

                // Get overall max width of full text ascii art
                std::size_t artWidth = 0;
                for (const auto& line : marqueeText)
                    artWidth = std::max(artWidth, line.size());

                for (int j = 0; j < HEIGHT; ++j)
                {
                    std::string row(screenW, ' ');
                    const std::string& line = marqueeText[j]; // get curr line/row

                    // Go through each col and determine loopy overflow + width math
                    for (std::size_t i = 0; i < line.size(); ++i)
                    {
                        int x = pos + static_cast<int>(i);
                        if (x >= 0 && x < screenW) row[x] = line[i];
                    }

                    // build: Absolute move to (row+1, col 1), then the row contents
                    frame += "\x1b[" + std::to_string(j + 1) + ";1H" + row;
                }

                if (running)
                {
                    // re-enter to right loopy
                    if (--pos + static_cast<int>(artWidth) < 0)
                        pos = screenW;
                } 
                else 
                {
                    pos = 0; //back to start
                }
            }

            // build: restore cursor pos
            frame += "\x1b" "8";

            // build output string: save cursor pos -> move to next row -> loop
            std::cout << frame << std::flush;

            // simulate refresh speed by sleeping the thread
            int delay = running ? refreshSpeed.load() : 50;   // static text still refreshes on set_text
            std::this_thread::sleep_for(std::chrono::milliseconds(delay)); // delay

        }
    }

    void generateMarqueeText() 
    {
        int spaceOffset = 32; // 32 is starting off set for space char
        marqueeText.fill("");
        for (int k = 0; k < HEIGHT; k ++)
        {
            for (size_t j = 0; j < inputText.length(); j++)
            {
                //Get current character
                int ascii = static_cast<int>(inputText[j]) - spaceOffset; 
                if (ascii < 0 || ascii >= (int)marqueeChars.size()) ascii = 0; 

                marqueeText[k] += marqueeChars[ascii][k];
            }
        }
    }
    
};