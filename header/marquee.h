#include <climits>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <array>
#define HEIGHT 7
using namespace std;

void printMarquee(vector<array<string, 7>> characters, string text)
{
    string space = "      "; // contrary to the function below, this must be at start

    // Get ascii equivalents
    vector<int> ascii;
    for (size_t j = 0; j < text.length(); j ++)
    {   
        ascii.push_back(text[j]);
    }

    for (int j = 0; j < HEIGHT; j ++)
    {
        for (size_t k = 0; k < text.length(); k ++)
        {
            // 32 is starting off set for space char
            if (ascii[k] == 32)
                cout << space;
            else
                cout << characters[ascii[k] - 32][j]; 
        }
        cout << "\n";
    }
}

// While I originally made this function by hand with AI assistance, I regenerated the code to accomodate for the fixed widths
vector<array<string, HEIGHT>> initializeFont()
{
    ifstream inputFile("text/ascii_font.txt");
    vector<array<string, HEIGHT>> characters;

    if (!inputFile.is_open()) {
        cerr << "Error: Could not open ascii_font.txt" << endl;
        return characters;
    }

    int j = 0;
    array<string, HEIGHT> character;
    string currLine;

    while (getline(inputFile, currLine))
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
            for (const string& row : character)
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

            array<string, HEIGHT> trimmed;

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

            characters.push_back(trimmed);
            j = 0;
        }
    }

    inputFile.close();
    return characters;
}