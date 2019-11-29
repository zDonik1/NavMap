#include "io.h"

int main()
{
    auto colours = loadColours();
    auto characters = loadCharConfig();
    auto map = loadMap(characters);

    handleIO(map, colours, characters);

    return 0;
}
