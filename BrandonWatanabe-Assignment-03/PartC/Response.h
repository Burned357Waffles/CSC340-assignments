#include <iostream>
#include <string>
#include <vector> 
#include <algorithm>
#include <map>
#include "DataLoader.h"
#pragma once

using namespace std;

class Response
{
public:

  Response(vector<string> arguments, DataLoader dictionary)
  {
    string arg1 = "";
    try
    {
      arg1 = arguments[0];
      transform(arg1.begin(), arg1.end(), arg1.begin(), ::tolower);
    }
    catch (...) // if arguments is empty
    {
      error = true;
      return;
    }

    // set word
    map <string, map<string, vector<string>>> dictionaryMap = dictionary.getDictionaryMap();
    for (map <string, map<string, vector<string>>>::const_iterator itr{ dictionaryMap.begin() }; itr != dictionaryMap.end(); itr++)
    {
      if (arg1 == itr->first)
      {
        word = itr->first;
        break;
      }
    }

    if (arguments.size() <= 1) return;

    if (arguments.size() == 2)
    {
      argTwoChecker(arguments);
    }

    if (arguments.size() == 3)
    {
      argTwoChecker(arguments);
      argThreeChecker(arguments);
    }
    if (arguments.size() == 4)
    {
      argTwoChecker(arguments);
      argThreeChecker(arguments);
      argFourChcecker(arguments);
    }
  }

  string getWord() { return word; }

  string getPartOfSpeech() { return partOfSpeech; }

  bool isDistinct() { return distinct; }

  bool isReverse() { return reverse; }

  bool isError() { return error; }


private:

  const vector<string> partsOfSpeechVector = { "adjective", "adverb", "conjunction", "interjection", "noun",
    "pronoun", "preposition", "verb" };
  string word = "";
  string partOfSpeech = "";
  bool distinct = false;
  bool reverse = false;
  bool error = false;
  bool argError = false;

  void argTwoChecker(vector<string> arguments)
  {
    string entry = arguments[1];
    transform(entry.begin(), entry.end(), entry.begin(), ::tolower);

    for (string speech : partsOfSpeechVector) // check if part of spech
    {
      if (entry == speech)
      {
        partOfSpeech = entry;
        return;
      }
    }

    if (entry == "distinct")
    {
      distinct = true; // check for distinct
      return;
    }
    else if (entry == "reverse")
    {
      reverse = true; // check for reverse
      return;
    }
    else argError = true;

    if (partOfSpeech.empty() || !distinct || !reverse || argError) cout << "       |\n";

    if (partOfSpeech.empty()) // if entry is not part of speech
    {
      cout << "       <The entered 2nd parameter: '" << entry << "' is NOT a part of speech.>" << endl; // if argument is not part of speech
    }

    if (!distinct)
    {
      cout << "       <The entered 2nd parameter: '" << entry << "' is NOT distinct.>" << endl;
    }

    if (!reverse)
    {
      cout << "       <The entered 2nd parameter: '" << entry << "' is NOT reverse.>" << endl;
    }

    if (argError)
    {
      cout << "       <The entered 2nd parameter: '" << entry << "' was disregarded.>\n"
        << "       <The 2nd parameter should be a part of speech or 'distinct' or 'reverse'.>" << endl;
    }

    if (partOfSpeech.empty() || !distinct || !reverse) cout << "       |\n";
  }

  void argThreeChecker(vector<string> arguments)
  {
    string entry = arguments[2];
    transform(entry.begin(), entry.end(), entry.begin(), ::tolower);
    if (entry == "distinct")
    {
      distinct = true; // check for distinct
      return;
    }
    else if (entry == "reverse")
    {
      reverse = true; // check for reverse
      return;
    }
    else argError = true;

    if (!distinct || !reverse || argError) cout << "       |\n";

    if (!distinct)
    {
      cout << "       <The entered 3rd parameter: '" << entry << "' is NOT distinct.>" << endl;
    }

    if (!reverse)
    {
      cout << "       <The entered 3rd parameter: '" << entry << "' is NOT reverse.>" << endl;
    }

    if (argError)
    {
      cout << "       <The entered 3rd parameter: '" << entry << "' was disregarded.>\n"
        << "       <The 3rd parameter should be 'distinct' or 'reverse'.>" << endl;
    }
    if (!distinct || !reverse || argError) cout << "       |\n";
  }

  void argFourChcecker(vector<string> arguments)
  {
    string entry = arguments[3];
    transform(entry.begin(), entry.end(), entry.begin(), ::tolower);
    if (entry == "reverse")
    {
      reverse = true; // check for reverse
      return;
    }
    else argError = true;
    if (!reverse || argError) cout << "       |\n";

    if (!reverse)
    {
      cout << "       <The entered 4th parameter: '" << entry << "' is NOT reverse.>" << endl;
    }

    if (argError)
    {
      cout << "       <The entered 4th parameter: '" << entry << "' was disregarded.>\n"
        << "       <The 4th parameter should be 'reverse'.>" << endl;
    }
    if (!reverse || argError) cout << "       |\n";
  }
};