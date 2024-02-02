#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <chrono>
#include <iomanip>

using namespace std;

bool isMisspelled(const string& word, const unordered_map<string, bool>& dictionary)
{
    return dictionary.find(word) == dictionary.end();
}

int main()
{
    unordered_map<string, bool> dictionary;

    ifstream dictionaryFile("dictionary.txt");
    string dictWord;

    while (dictionaryFile >> dictWord)
    {
        dictionary[dictWord] = true;
    }

    dictionaryFile.close();

    ifstream inputFile("ENGPANISH.txt");
    string inputText;

    if (inputFile)
    {
        string line;
        while (getline(inputFile, line))
        {
            inputText += line + " ";
        }

        inputFile.close();

        string word;

        auto start = chrono::high_resolution_clock::now(); // Start the timer

        // Iterate over each character in the input text
        for (const char& c : inputText)
        {
            if (isalpha(c))
            {
                // Append alphabetic characters to the word
                word += tolower(c);
            }
            else
            {
                if (!word.empty())
                {
                    // Check if the word is misspelled
                    if (isMisspelled(word, dictionary))
                    {
                        cout << "Misspelled word: " << word << endl;
                    }

                    // Reset the word for the next iteration
                    word.clear();
                }
            }
        }

        // Check if there is a word at the end of the input text
        if (!word.empty())
        {
            if (isMisspelled(word, dictionary))
            {
                cout << "Misspelled word: " << word << endl;
            }
        }

        auto end = chrono::high_resolution_clock::now(); // Stop the timer
        auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);
        cout << "Time taken: " << fixed << setprecision(4) << duration.count() / 1000.0 << " seconds" << endl;
    }
    else
    {
        cerr << "Failed to open the input file." << endl;
        return 1;
    }

    return 0;
}
