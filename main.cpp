#include <iostream>
#include <fstream>
#include "stack.h"
#include "map.h"

#ifdef __unix__

#define OS_Windows 0

#elif defined(_WIN32) || defined(WIN32)

#define OS_Windows 1

#endif


void clearScreen()
{
    if (OS_Windows) {
        system("cls");
    }
    else {
        std::cout << "\033[2J\033[1;1H";
    }
}

void printPath(Stack<int> l_path)
{
    if (l_path.empty()) {
        return;
    }

    std::cout << l_path.top();
    l_path.pop();
    while (!l_path.empty()) {
        std::cout << "->" << l_path.top();
        l_path.pop();
    }
    std::cout << std::endl;
}

void printCharMap(const CharMap &l_char_map)
{
    for (size_t i = 0; i < l_char_map.back().size(); ++i) {
        for (size_t j = 0; j < l_char_map.size(); ++j) {
            std::cout << l_char_map.at(j).at(l_char_map.back().size() - 1 - i);
        }

        std::cout << std::endl;
    }
}

void handleIO(const Map &map)
{
    while (true) {
        system("cls");
        printCharMap(map.getCharMap());
        std::cout << std::endl;

        std::cout << "Enter starting and ending positions, or '~' to quit" << std::endl;
        char in_ch1;
        std::cin >> in_ch1;
        if (in_ch1 == '~') {
            break;
        }

        char in_ch2;
        std::cin >> in_ch2;
        std::cout << std::endl;

        printCharMap(map.getCharMapWithPath(in_ch1, in_ch2));
        std::cout << std::endl;

        clearScreen();
    }
}

int main()
{
    Map map;
    std::ifstream ifs("maps/map1.map");
    if (!ifs.is_open()) {
        std::cout << "Couldn't load map" << std::endl;
    }

    map.setCharMapEncoding('x', '@', 'O');
    map.load(ifs);
    ifs.close();

    handleIO(map);

    return 0;
}
