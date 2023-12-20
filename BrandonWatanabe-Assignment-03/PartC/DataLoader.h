#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <map>
#include <vector>
#pragma once

using namespace std;

class DataLoader
{
public:
  map <string, map<string, vector<string>>> getDictionaryMap()
  {
    return dictionaryMap;
  }

  void loadData()
  {
    cout << "! Opening data file... C:\\Users\\MickeyMouse\\AbsolutePath\\DB\\Data.CS.SFSU.txt\n"
      << "<!>ERROR<!> ===> File could not be opened.\n"
      << "<!>ERROR<!> ===> Provided file path: C:\\Users\\MickeyMouse\\AbsolutePath\\DB\\Data.CS.SFSU.txt" << endl;
    bool validFile = false;
    while (!validFile)
    {
      string filePath;
      cout << "\n<!>Enter the CORRECT data file path: ";
      getline(cin, filePath);

      //filePath.erase(remove_if(filePath.begin(), filePath.end(), ::isspace), filePath.end());

      string extention = ".txt";
      if (filePath.find(extention) != std::string::npos)
      {
        validFile = true;
        fillDicitonary(filePath);
      }
      else cout << "\n<!>ERROR<!> ===> File could not be opened.\n"
        << "<!>ERROR<!> ===> Provided file path: " << filePath << endl;
    }
  }

private:
  map <string, map<string, vector<string>>> dictionaryMap;

  void fillDicitonary(string filePath)
  {
    fstream ioFile;
    cout << "! Opening data file... " << filePath << endl;

    ioFile.open(filePath, ios::in);

    cout << "! Loading Data..." << endl;
    string delimiter = "|";
    string posDelimiter = " -=>> ";
    size_t position = 0;
    string line, word, token, definition;

    while (getline(ioFile, line))
    {
      if ((position = line.find(delimiter)) != string::npos) // get word from file
      {
        word = line.substr(0, position);
        line.erase(0, position + delimiter.length());
      }

      vector<string> tempVector;
      map <string, vector<string>> definitionMap;

      while ((position = line.find(".")) != string::npos)
      {
        token = line.substr(0, position);
        tempVector.push_back(token); // add pos and def to vector
        line.erase(0, position + 2);
      }

      for (string entry : tempVector)
      {
        if ((position = entry.find(posDelimiter)) != string::npos)
        {
          token = entry.substr(0, position); // get pos
          entry.erase(0, position + posDelimiter.length()); // entry = definition

          if (definitionMap.count(token)) // if pos already in definiitonMap
          {
            auto itr = definitionMap.find(token);
            itr->second.push_back(entry);
          }

          else
          {
            vector<string> definitionVector;
            definitionVector.push_back(entry);
            definitionMap.emplace(token, definitionVector);
          }
        }
      }

      dictionaryMap.emplace(word, definitionMap); // fill in dictionaryMap

    }

    cout << "! Loading Completed..." << endl;
    cout << "! Closing data file... " << filePath << endl;
    ioFile.close();
  }
};