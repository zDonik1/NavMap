#include "io.h"

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

void printCharMap(const CharMap &l_char_map, const std::map<std::string, unsigned short> &l_colours, const std::map<std::string, CharData> &l_characters)
{
    for (size_t i = 0; i < l_char_map.back().size(); ++i) {
        for (size_t j = 0; j < l_char_map.size(); ++j) {
            char ch = l_char_map.at(j).at(l_char_map.back().size() - 1 - i);

            if (OS_Windows) {
                HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                CharData ch_data;
                if (ch == l_characters.at("ROAD").character) {
                    ch_data = l_characters.at("ROAD");
                }
                else if (ch == l_characters.at("PATH").character) {
                    ch_data = l_characters.at("PATH");
                }
                else if (ch == l_characters.at("DEFAULT").character) {
                    ch_data = l_characters.at("DEFAULT");
                }
                else if (ch >= 'A' && ch <= 'Z') {
                    ch_data = l_characters.at("NODE");
                }

                unsigned short colour;
                try {
                    colour = l_colours.at(ch_data.text_colour)
                            + l_colours.at(ch_data.bg_colour) * 16;
                }
                catch (...) {
                    std::cout << "Wrong characters entered in map file" << std::endl;
                }
                SetConsoleTextAttribute(hConsole, colour);
            }

            std::cout << ch << ' ';
        }

        std::cout << std::endl;
    }
}

void handleIO(const Map &l_map, const std::map<std::string, unsigned short> &l_colours, const std::map<std::string, CharData> &l_characters)
{
    while (true) {
        printCharMap(l_map.getCharMap(), l_colours, l_characters);
        std::cout << std::endl;

        if (OS_Windows) {
            HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
            SetConsoleTextAttribute(hConsole, l_colours.at("White"));
        }

        std::cout << "Enter starting and ending positions, or '~' to quit" << std::endl;
        char in_ch1;
        std::cin >> in_ch1;
        if (in_ch1 == '~') {
            break;
        }

        char in_ch2;
        std::cin >> in_ch2;
        std::cout << std::endl;

        printCharMap(l_map.getCharMapWithPath(in_ch1, in_ch2), l_colours, l_characters);
        std::cout << std::endl;

        if (OS_Windows) {
            system("pause");
            system("cls");
        }
    }
}

Colours loadColours()
{
    Colours colours;
    if (OS_Windows) {
        std::ifstream ifs_colour("config/colour_encoding.config");
        if (!ifs_colour.is_open()) {
            std::cout << "Couldn't load colour config" << std::endl;
        }

        unsigned short counter = 0;
        std::string line;
        while (std::getline(ifs_colour, line)) {
            std::stringstream sstream(line);
            std::string key;
            sstream >> key;
            colours[key] = counter;
            ++counter;
        }
    }

    return colours;
}

CharDataSet loadCharConfig()
{
    CharDataSet characters;

    std::ifstream ifs_char("config/character_encoding.config");
    if (!ifs_char.is_open()) {
        std::cout << "Couldn't load character config" << std::endl;
    }

    std::string line;
    while (std::getline(ifs_char, line)) {
        std::stringstream sstream(line);
        std::string key;
        char ch;
        std::string txt_colour;
        std::string bg_colour;
        sstream >> key >> ch >> txt_colour >> bg_colour;

        characters[key] = {ch, txt_colour, bg_colour};
    }

    return characters;
}

Map loadMap(const std::map<std::string, CharData> &l_characters)
{
    Map map;
    std::ifstream ifs("maps/map1.map");
    if (!ifs.is_open()) {
        std::cout << "Couldn't load map" << std::endl;
    }

    map.setCharMapEncoding(l_characters.at("ROAD").character,
                           l_characters.at("PATH").character,
                           l_characters.at("NODE").character);
    map.load(ifs);
    ifs.close();

    return map;
}
