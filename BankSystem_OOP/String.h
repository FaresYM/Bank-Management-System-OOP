#pragma once

#include <iostream>
#include <vector>

using namespace std;

namespace MyStringLib
{

    short CountWords(string Text)
    {
        string delim = " ";
        short Counter = 0;
        short pos = 0;
        string sWord;

        while ((pos = Text.find(" ")) != std::string::npos)
        {
            sWord = Text.substr(0, pos);

            if (sWord != "")
            {
                Counter++;
            }

            Text.erase(0, pos + delim.length());
        }

        if (Text != "")
        {
            Counter++;
        }
        return Counter;
    }

    void PrintWordInEachString(string Text)
    {
        string delim = " ";
        cout << "\nYour Words Is :\n\n";
        short pos = 0;
        string sWord;

        while ((pos = Text.find(" ")) != std::string::npos)
        {
            sWord = Text.substr(0, pos);

            if (sWord != "")
            {
                cout << sWord << endl;
            }

            Text.erase(0, pos + delim.length());
        }

        if (Text != "")
        {
            cout << Text << endl;
        }

    }

    bool IsVowel(char Letter)
    {
        Letter = tolower(Letter);

        return ((Letter == 'a') || (Letter == 'e') || (Letter == 'i') || (Letter == 'o') || (Letter == 'u'));
    }

    void PrintVowels(string S)
    {
        for (int i = 0; i < S.length(); i++)
        {
            if (IsVowel(S[i]))
            {
                cout << S[i] << "	";
            }
        }
    }

    short CountVowels(string Text)
    {
        short Counter = 0;

        for (int i = 0; i < Text.length(); i++)
        {
            if (IsVowel(Text[i]))
                Counter++;
        }
        return Counter;
    }

    short CountLetterInEachWord(string S1, char Letter, bool MatchCase = true)
    {
        short Counter = 0;

        for (short i = 0; i < S1.length(); i++)
        {
            if (MatchCase)
            {
                if (S1[i] == Letter)
                {
                    Counter++;
                }
            }
            else
            {
                if (tolower(S1[i]) == tolower(Letter))
                {
                    Counter++;
                }
            }
        }
        return Counter;
    }

    enum enWhatToCount { SmallLetters = 0, CapitalLetters = 1, All = 3 };
    short CountLetters(string S1, enWhatToCount WhatToCount = enWhatToCount::All)
    {
        short Counter = 0;

        if (WhatToCount == enWhatToCount::All)
        {
            return S1.length();
        }

        for (short i = 0; i < S1.length(); i++)
        {
            if (WhatToCount == enWhatToCount::CapitalLetters && isupper(S1[i]))
                Counter++;

            if (WhatToCount == enWhatToCount::SmallLetters && islower(S1[i]))
                Counter++;
        }

        return Counter;
    }

    int CountSmallLetters(string S1)
    {
        int Counter = 0;
        for (int i = 0; i < S1.length(); i++)
        {
            if (islower(S1[i]))
                Counter++;
        }
        return Counter;
    }

    int CountCapitalLetters(string S1)
    {
        int Counter = 0;
        for (int i = 0; i < S1.length(); i++)
        {
            if (isupper(S1[i]))
                Counter++;
        }
        return Counter;
    }

    char ReadChar(string Message)
    {
        char Char;

        cout << Message << endl;
        cin >> Char;

        return Char;
    }

    char InvertCharacterCase(char S1)
    {
        return isupper(S1) ? tolower(S1) : toupper(S1);
    }

    string InvertAllStringLettersCase(string S1)
    {
        for (int i = 0; i < S1.length(); i++)
        {
            S1[i] = InvertCharacterCase(S1[i]);
        }

        return S1;
    }

    string ReadString(string Message)
    {
        cout << Message << endl;
        string String;
        getline(cin, String);

        return String;
    }

    string LowerAllString(string S1)
    {
        for (int i = 0; i < S1.length(); i++)
        {
            S1[i] = tolower(S1[i]);
        }
        return S1;
    }

    string UpperAllString(string S1)
    {
        for (int i = 0; i < S1.length(); i++)
        {
            S1[i] = toupper(S1[i]);
        }
        return S1;
    }

    string LowerFirstLetterOfEachWord(string S1)
    {
        bool IsFirstLetter = true;

        for (int i = 0; i < S1.length(); i++)
        {
            if (S1[i] != ' ' && IsFirstLetter)
            {
                S1[i] = tolower(S1[i]);
            }

            IsFirstLetter = (S1[i] == ' ' ? true : false);
        }
        return S1;
    }

    string UpperFirstLetterOfEachWord(string S1)
    {
        bool IsFirstLetter = true;

        for (int i = 0; i < S1.length(); i++)
        {
            if (S1[i] != ' ' && IsFirstLetter)
            {
                S1[i] = toupper(S1[i]);
            }

            IsFirstLetter = (S1[i] == ' ' ? true : false);
        }
        return S1;
    }

    void PrintFirstLetterOfEachWord(string S1)
    {
        bool IsFirstLetter = true;

        for (int i = 0; i < S1.length(); i++)
        {
            if (S1[i] != ' ' && IsFirstLetter)
            {
                cout << S1[i] << endl;
            }

            IsFirstLetter = (S1[i] == ' ' ? true : false);
        }
    }

    vector<string> SplitString(string Text, string delim)
    {
        vector<string>vSplit;

        short pos = 0;
        string sWord;

        while ((pos = Text.find(delim)) != std::string::npos)
        {
            sWord = Text.substr(0, pos);

            if (sWord != "")
            {
                vSplit.push_back(sWord);
            }

            Text.erase(0, pos + delim.length());
        }

        if (Text != "")
        {
            vSplit.push_back(Text);
        }
        return vSplit;
    }

    string JoinString(vector<string>vSplit, string delim)
    {
        string S1 = "";
        for (string& s : vSplit)
        {
            S1 = S1 + s + delim;
        }

        return S1.substr(0, S1.length() - delim.length());
    }

    string JoinString(string arr[], short length, string delim)
    {
        string S1 = "";

        for (int i = 0; i < length; i++)
        {
            S1 = S1 + arr[i] + delim;
        }

        return S1.substr(0, S1.length() - delim.length());
    }

    string ReplaceWord(string S1, string WordToReplace, string ReplaceTo)
    {
        short pos = S1.find(WordToReplace);

        while (pos != std::string::npos)
        {
            S1 = S1.replace(pos, WordToReplace.length(), ReplaceTo);
            pos = S1.find(WordToReplace);
        }
        return S1;
    }

    string ReplaceWord_MatchCase(string S1, string WordToReplace, string ReplaceTo, bool MatchCase = true)
    {
        vector<string>vString;

        vString = SplitString(S1, " ");

        for (string& Word : vString)
        {
            if (MatchCase)
            {
                if (Word == WordToReplace)
                {
                    Word = ReplaceTo;
                }
            }
            else
            {
                if (LowerAllString(Word) == LowerAllString(WordToReplace))
                {
                    Word = ReplaceTo;
                }
            }
        }

        return JoinString(vString, " ");
    }

    string ReverseWordsInString(string S1)
    {
        vector<string>vString;

        vString = SplitString(S1, " ");

        string S2 = "";

        vector<string>::iterator iter = vString.end();

        while (iter != vString.begin())
        {
            iter--;

            S2 = S2 + *iter + " ";
        }

        return S2.substr(0, S2.length() - 1);
    }

    string RemovePunctuations(string S1)
    {
        string S2 = "";

        for (int i = 0; i < S1.length(); i++)
        {
            if (!ispunct(S1[i]))
            {
                S2 += S1[i];
            }
        }

        return S2;
    }

    string TrimLeft(string S1)
    {
        for (int i = 0; i < S1.length(); i++)
        {
            if (S1[i] != ' ')
            {
                return S1.substr(i, S1.length() - i);
            }
        }
        return "";
    }

    string TrimRight(string S1)
    {
        for (int i = S1.length() - 1; i >= 0; i--)
        {
            if (S1[i] != ' ')
            {
                return S1.substr(0, i + 1);
            }
        }
        return "";
    }

    string Trim(string S1)
    {
        return TrimLeft(TrimRight(S1));
    }

    void PrintAllFromAAAtoZZZ()
    {
        cout << "\n";  // Print an empty line for formatting.
        string word = "";  // Initialize an empty string to build each three-letter combination.

        // Outer loop: Iterates over ASCII values for uppercase letters (65 'A' to 90 'Z') for the first letter.
        for (int i = 65; i <= 90; i++)
        {
            // Middle loop: Iterates over ASCII values for uppercase letters for the second letter.
            for (int j = 65; j <= 90; j++)
            {
                // Inner loop: Iterates over ASCII values for uppercase letters for the third letter.
                for (int k = 65; k <= 90; k++)
                {
                    // Append the current letter for the first position.
                    word.append(1, char(i));
                    // Append the current letter for the second position.
                    word.append(1, char(j));
                    // Append the current letter for the third position.
                    word.append(1, char(k));

                    // Output the constructed three-letter word.
                    cout << word << endl;
                    // Reset the word string to empty for the next combination.
                    word = "";
                }
            }
            // After completing combinations for the current first letter, print a separator line.
            cout << "\n____________________________\n";
        }
    }

    bool GuessPassword(string OriginalPassword)
    {
        string word = "";  // Variable to build each password guess.
        int Counter = 0;   // Counter to keep track of the number of trials.

        cout << "\n";  // Print an empty line for formatting.

        // Three nested loops to generate all combinations of three uppercase letters.
        for (int i = 65; i <= 90; i++)         // Loop for the first letter (ASCII codes for A-Z).
        {
            for (int j = 65; j <= 90; j++)     // Loop for the second letter.
            {
                for (int k = 65; k <= 90; k++) // Loop for the third letter.
                {
                    // Build the password guess by concatenating three characters.
                    word = word + char(i);
                    word = word + char(j);
                    word = word + char(k);

                    Counter++;  // Increment the trial counter.

                    // Print the current trial number and the guessed word.
                    cout << "Trial [" << Counter << "] : " << word << endl;

                    // Check if the guessed word matches the original password.
                    if (word == OriginalPassword)
                    {
                        cout << "\nPassword is " << word << "\n";
                        cout << "Found after " << Counter << " Trial(s)\n";

                        return true;  // Return true indicating the password was found.
                    }

                    // Reset the word variable for the next guess.
                    word = "";
                }
            }
        }

        return false;  // If no match was found (should not happen for valid 3-letter passwords), return false.
    }

    string EncryptText(string Text, short EncryptionKey)
    {
        // Loop through each character of the text.
        // Note: Using "<= Text.length()" iterates one extra time (accessing the null terminator), 
        // which may be unintended. Ideally, use "< Text.length()".
        for (int i = 0; i <= Text.length(); i++)
        {
            // Convert the current character to its integer ASCII value,
            // add the encryption key, cast it back to char, and assign it back.
            Text[i] = char((int)Text[i] + EncryptionKey);
        }
        return Text; // Return the encrypted text.
    }

    string DecryptText(string Text, short EncryptionKey)
    {
        // Loop through each character of the text.
        // Note: Using "<= Text.length()" will process one extra character (the null terminator).
        for (int i = 0; i <= Text.length(); i++)
        {
            // Convert the current character to its ASCII integer value,
            // subtract the encryption key, cast back to char, and assign it back.
            Text[i] = char((int)Text[i] - EncryptionKey);
        }
        return Text; // Return the decrypted text.
    }

}
