#include <iostream>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include "Response.h"
#include "DataLoader.h"

using namespace std;

class Parser
{
public:
  
  Parser(string input, DataLoader dictionary)
  {
    this->input = input;
    this->dictionary = dictionary;
  }

  vector<string> parseInput()
  {
    vector<string> printQueue;
    if (input == "" || input == "!help")
    {
      helpPrompt();
      return printQueue;
    }

    else if (input == "!q")
    {
      running = false;
      return printQueue;
    }
    vector<string> inputVector;
    inputVector = splitString(input, inputVector);
    
    if (inputVector.size() > 4)
    {
      helpPrompt();
      return printQueue;
    }

    Response response(inputVector, dictionary);

    if (response.isError())
    {
      helpPrompt();
      return printQueue;
    }

    if (response.getWord().empty())
    {
      cout << "|\n <NOT FOUND> To be considered for the next release. Thank you.\n|" << endl;
      helpPrompt();
      return printQueue;
    }

    map <string, vector<string>> definitionMap = dictionary.getDictionaryMap().at(response.getWord());
    for (map <string, vector<string>>::const_iterator defItr { definitionMap.begin() }; defItr != definitionMap.end(); defItr++)
      {
        // first = pos
        // second = defVector
        if (!response.getPartOfSpeech().empty())
        {
          if (response.getPartOfSpeech() == defItr->first)
          {
            for (string definition : defItr->second)
            {
              stringstream ss;
              string capsWord = response.getWord();
              capsWord[0] = toupper(capsWord[0]);
              ss << capsWord << " " << "[" << defItr->first << "] : " << definition << ".";
              string combined = ss.str();
              printQueue.push_back(combined);
            }
          }
        }

        else
        {
          for (string definition : defItr->second)
          {
            stringstream ss;
            string capsWord = response.getWord();
            capsWord[0] = toupper(capsWord[0]);
            ss << capsWord << " " << "[" << defItr->first << "] : " << definition << ".";
            string combined = ss.str();
            printQueue.push_back(combined);
          }
        }
      }

      sort(printQueue.begin(), printQueue.end());

      if (response.isDistinct()) removeDuplicates(printQueue);
      if (response.isReverse()) reverseQueue(printQueue);

      if (printQueue.empty())
      {
        cout << "|\n <NOT FOUND> To be considered for the next release. Thank you.\n|" << endl;
        helpPrompt();
        return printQueue;
      }
      return printQueue;
    }

  

  bool isRunning() { return running; }

private:
  
  bool running = true;
  string input;
  DataLoader dictionary;

  vector<string> splitString(string input, vector<string> &inputVector)
  {
    string temp = "";
    for (unsigned i = 0; i < input.length(); i++)
    {
      if (input[i] == ' ')
      {
        inputVector.push_back(temp);
        temp = "";
      }
      else temp.push_back(input[i]);
    }
    inputVector.push_back(temp);
    return inputVector;
  }

  void helpPrompt()
  {
    cout << "\n       |\n       PARAMETER HOW-TO, please enter:\n"
      << "       1. A search key -then 2. An optional part of speech -then\n"
      << "       3. An optional 'distinct' -then 4. An optional 'reverse'\n       |" << endl;
  }

  void removeDuplicates(vector<string> &printQueue) 
  {
    auto last = unique(printQueue.begin(), printQueue.end());
    printQueue.erase(last, printQueue.end());
    return;
  }

  void reverseQueue(vector<string> &printQueue)
  {
    reverse(printQueue.begin(), printQueue.end());
    return;
  }
};