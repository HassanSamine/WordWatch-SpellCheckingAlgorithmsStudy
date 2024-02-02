#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <chrono>

using namespace std;

class TrieNode
{
public:
    bool isEndOfWord;
    unordered_map<char, TrieNode*> children;

    TrieNode() : isEndOfWord(false) {}

    ~TrieNode()
    {
        for (auto& pair : children)
        {
            delete pair.second;
        }
    }
};

class Trie
{
private:
    TrieNode* root;

public:
    Trie()
    {
        root = new TrieNode();
    }

    ~Trie()
    {
        delete root;
    }

    void insert(const string& word)
    {
        TrieNode* current = root;
        for (char c : word)
        {
            if (current->children.find(c) == current->children.end())
            {
                current->children[c] = new TrieNode();
            }
            current = current->children[c];
        }
        current->isEndOfWord = true;
    }

    bool search(const string& word)
    {
        TrieNode* current = root;
        for (char c : word)
        {
            if (current->children.find(c) == current->children.end())
            {
                return false;
            }
            current = current->children[c];
        }
        return current->isEndOfWord;
    }
};

bool isMisspelled(const string& word, Trie& dictionary)
{
    return !dictionary.search(word);
}

int main()
{
    Trie dictionary;

    ifstream dictionaryFile("dictionary.txt");
    string word;

    while (dictionaryFile >> word) //inserting each word from dictionarry in the trie using insert 
    {
        dictionary.insert(word);
    }

    dictionaryFile.close();

    ifstream inputFile("engpanish.txt");
    string inputText;

    if (inputFile)
    {
        inputText.assign((istreambuf_iterator<char>(inputFile)), istreambuf_iterator<char>()); //verifying if the file is opened and reading the file 
        inputFile.close();

        string currentWord;

        auto start = chrono::high_resolution_clock::now();

        for (const char& c : inputText)
        {
            if (isalpha(c))
            {
                currentWord += tolower(c); //append the characters to lower cases
            }
            else if (!currentWord.empty())
            {
                if (isMisspelled(currentWord, dictionary))
                {
                    cout << "Misspelled word: " << currentWord << endl;
                }
                currentWord.clear();
            }
        }

        auto end = chrono::high_resolution_clock::now();
        double elapsedTime = chrono::duration<double>(end - start).count();

        cout << "Elapsed Time: " << elapsedTime << " seconds" << endl;
    }
    else
    {
        cout << "Failed to open input file." << endl;
    }

    return 0;
}
