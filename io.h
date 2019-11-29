#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include "stack.h"
#include "map.h"


#ifdef __unix__

#define OS_Windows 0

#elif defined(_WIN32) || defined(WIN32)

#define OS_Windows 1
#include "windows.h"

#endif


struct CharData
{
    char character;
    std::string text_colour;
    std::string bg_colour;
};


// --- "using" types

using Colours = std::map<std::string, unsigned short>;
using CharDataSet = std::map<std::string, CharData>;


// --- Functions

void printPath(Stack<int> l_path);

void printCharMap(const CharMap &l_char_map,
                  const std::map<std::string, unsigned short> &l_colours,
                  const std::map<std::string, CharData> &l_characters);

void handleIO(const Map &l_map, const std::map<std::string, unsigned short> &l_colours,
              const std::map<std::string, CharData> &l_characters);

Colours loadColours();
CharDataSet loadCharConfig();
Map loadMap(const std::map<std::string, CharData> &l_characters);
