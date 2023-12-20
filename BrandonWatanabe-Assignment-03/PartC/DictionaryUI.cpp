#include <iostream>
#include <string>
#include <map>
#include <vector>
#include "DataLoader.h"
#include "Parser.h"
#include "Response.h"

using namespace std;

//###############################################################
// TODO: 
// 1. Fix !q
//###############################################################


int lineCount = 1;
bool running = true;
DataLoader dictionary;

void displayDicitonaryCount()
{
  int wordCound = 0;
  int definitionCount = 0;
  map <string, map<string, vector<string>>> dictionaryMap = dictionary.getDictionaryMap();
  for (map <string, map<string, vector<string>>>::const_iterator itr{ dictionaryMap.begin() }; itr != dictionaryMap.end(); itr++)
  {
    wordCound++;
    for (map <string, vector<string>>::const_iterator defItr{ itr->second.begin() }; defItr != itr->second.end(); defItr++)
    {
      for (string entry : defItr->second)
      {
        definitionCount++;
      }
    }
  }

  cout << "====== DICTIONARY 340 C++ ======\n" 
    << "------ Keywords: " << wordCound
    << "\n------ Definitions: " << definitionCount << "\n" << endl;
}

void displayPrintQueue(vector<string> printQueue)
{
  cout << "       |" << endl;
  for (string definition : printQueue)
  {
    cout << "       " << definition << endl;
  }
  cout << "       |" << endl;
}

void prompt()
{
  string command;
  cout << "Search [" << lineCount << "]: ";
  getline(cin, command);
  lineCount++;
  Parser parse(command, dictionary);
  vector<string> printQueue = parse.parseInput();
  if (!parse.isRunning())
  {
    running = false;
    return;
  }
  if (!printQueue.empty()) displayPrintQueue(printQueue);
  printQueue.clear();
}


int main()
{
  dictionary.loadData();
  cin.clear();
  displayDicitonaryCount();

  cout << "\n       |\n       PARAMETER HOW-TO, please enter:\n"
    << "       1. A search key -then 2. An optional part of speech -then\n"
    << "       3. An optional 'distinct' -then 4. An optional 'reverse'\n       |" << endl;

  while (running)
  {
    prompt();
  }
  cout << "-----THANK YOU-----" << endl;
  return 0;
}
