#pragma once

#include <iostream>
#include <vector>

using namespace std;

class clsString
{

private:
    string _String;

public:

    clsString()
    {
        _String = "";
    }

    clsString(string String)
    {
        _String = String;
    }

    void SetString(string String)
    {
        _String = String;
    }

    string GetString()
    {
        return _String;
    }

    //If you call (Object.String = "??") it will call SetString method
    //If you call (Object.String) it will call GetString method
    _declspec(property(get = GetString, put = SetString)) string String;

    static short Length(string S1)
    {
        return S1.length();
    }

    short Length()
    {
        return String.length();
    }

    static short CountWords(string S1)
    {
        string Delim = " ";
        short Counter = 0;
        short Pos = 0;
        string sWord;

        while ((Pos = S1.find(Delim)) != std::string::npos)
        {
            sWord = S1.substr(0, Pos);

            if (sWord != "")
            {
                Counter++;
            }

            S1.erase(0, Pos + Delim.length());
        }

        if (S1 != "")
        {
            Counter++;
        }
        return Counter;
    }

    short CountWords()
    {
        return CountWords(_String);
    }

    static void PrintWordInEachString(string S1)
    {
        string delim = " ";
        cout << "\nYour Words Is :\n\n";
        short pos = 0;
        string sWord;

        while ((pos = S1.find(" ")) != std::string::npos)
        {
            sWord = S1.substr(0, pos);

            if (sWord != "")
            {
                cout << sWord << endl;
            }

            S1.erase(0, pos + delim.length());
        }

        if (S1 != "")
        {
            cout << S1 << endl;
        }

    }

    void PrintWordInEachString()
    {
        PrintWordInEachString(_String);
    }

    static string UpperAllString(string S1)
    {
        for (short i = 0; i < S1.length(); i++)
        {
            if (int(S1[i]) >= 97 && int(S1[i]) <= 122)
            {
                S1[i] = S1[i] - 32;
            }
        }

        return S1;
    }

    void UpperAllString()
    {
        _String = UpperAllString(_String);
    }

    static string LowerAllString(string S1)
    {
        for (short i = 0; i < S1.length(); i++)
        {
            if (int(S1[i]) >= 65 && int(S1[i]) <= 90)
            {
                S1[i] = S1[i] + 32;
            }
        }

        return S1;
    }

    void LowerAllString()
    {
        _String = LowerAllString(_String);
    }

    static char InvertCharacterCase(char Ch1)
    {
        return isupper(Ch1) ? tolower(Ch1) : toupper(Ch1);
    }

    static string InvertAllStringLettersCase(string S1)
    {
        for (int i = 0; i < S1.length(); i++)
        {
            S1[i] = InvertCharacterCase(S1[i]);
        }

        return S1;
    }

    void InvertAllStringLettersCase()
    {
        _String = InvertAllStringLettersCase(_String);
    }

    static string UpperFirstLetterOfEachWord(string S1)
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

    void UpperFirstLetterOfEachWord()
    {
        _String = UpperFirstLetterOfEachWord(_String);
    }

    static string LowerFirstLetterOfEachWord(string S1)
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

    void LowerFirstLetterOfEachWord()
    {
        _String = LowerFirstLetterOfEachWord(_String);
    }

    static void PrintFirstLetterOfEachWord(string S1)
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

    void PrintFirstLetterOfEachWord()
    {
        PrintFirstLetterOfEachWord(_String);
    }

    enum enWhatToCount { SmallLetters = 0, CapitalLetters = 1, All = 3 };

    static short CountLetters(string S1, enWhatToCount WhatToCount = enWhatToCount::All)
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

    short CountLetters()
    {
        return CountLetters(_String, enWhatToCount::All);
    }

    static short CountCapitalLetters(string S1)
    {
        int Counter = 0;
        for (int i = 0; i < S1.length(); i++)
        {
            if (isupper(S1[i]))
                Counter++;
        }
        return Counter;
    }

    short CountCapitalLetters()
    {
        return CountCapitalLetters(_String);
    }

    static short CountSmallLetters(string S1)
    {
        int Counter = 0;
        for (int i = 0; i < S1.length(); i++)
        {
            if (islower(S1[i]))
                Counter++;
        }
        return Counter;
    }

    short CountSmallLetters()
    {
        return CountSmallLetters(_String);
    }

    static short CountLetterInEachWord(string S1, char Letter, bool MatchCase = true)
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

    short CountLetterInEachWord(char Letter, bool MatchCase = true)
    {
        return CountLetterInEachWord(_String, Letter, MatchCase);
    }

    static bool IsVowel(char Letter)
    {
        Letter = tolower(Letter);

        return ((Letter == 'a') || (Letter == 'e') || (Letter == 'i') || (Letter == 'o') || (Letter == 'u'));
    }

    static short CountVowels(string S1)
    {
        short Counter = 0;

        for (int i = 0; i < S1.length(); i++)
        {
            if (IsVowel(S1[i]))
                Counter++;
        }
        return Counter;
    }

    short CountVowels()
    {
        return CountVowels(String);
    }

    static void PrintVowels(string S1)
    {
        for (int i = 0; i < S1.length(); i++)
        {
            if (IsVowel(S1[i]))
            {
                cout << S1[i] << "	";
            }
        }
    }

    void PrintVowels()
    {
        PrintVowels(_String);
    }

    static vector<string> SplitString(string S1, string Delim)
    {
        vector<string>vSplit;

        short pos = 0;
        string sWord;

        while ((pos = S1.find(Delim)) != std::string::npos)
        {
            sWord = S1.substr(0, pos);

            if (sWord != "")
            {
                vSplit.push_back(sWord);
            }

            S1.erase(0, pos + Delim.length());
        }

        if (S1 != "")
        {
            vSplit.push_back(S1);
        }
        return vSplit;
    }

    vector<string> SplitString(string Delim)
    {
        return SplitString(_String, Delim); //Send string value of object and Delim
    }

    static string JoinString(vector<string>vString, string Delim = " ")
    {
        string S1 = "";

        for (string& s : vString)
        {
            S1 = S1 + s + Delim;
        }

        return S1.substr(0, S1.length() - Delim.length());
    }

    static string JoinString(string arrString[], short length, string delim)
    {
        string S1 = "";

        for (int i = 0; i < length; i++)
        {
            S1 = S1 + arrString[i] + delim;
        }

        return S1.substr(0, S1.length() - delim.length());
    }

    static string ReverseWordsInString(string S1)
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

    void ReverseWordsInString()
    {
        _String = ReverseWordsInString(_String);
    }

    static string ReplaceWord(string S1, string WordToReplace, string ReplaceTo, bool MatchCase = true)
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

    void ReplaceWord(string WordToReplace, string ReplaceTo, bool MatchCase = true)
    {
        _String = ReplaceWord(_String, WordToReplace, ReplaceTo, MatchCase);
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

    void RemovePunctuations()
    {
        _String = RemovePunctuations(_String);
    }

    static string TrimLeft(string S1)
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

    void TrimLeft()
    {
        _String = TrimLeft(_String);
    }

    static string TrimRight(string S1)
    {
        //Start From the last index
        for (short i = S1.length() - 1; i >= 0; i--)
        {
            if (S1[i] != ' ') //If condition to check that each character is not a space character
            {
                //Return String Starting from the first index 0 to index i (the first character after spaces) + 1
                return S1.substr(0, i + 1);
            }
        }

        return ""; // لو السترينج كله مسافات بيرجع فاضي
    }

    void TrimRight()
    {
        _String = TrimRight(_String);
    }

    static string Trim(string S1)
    {
        return TrimLeft(TrimRight(S1));
    }

    void Trim()
    {
        _String = Trim(_String);
    }
};
