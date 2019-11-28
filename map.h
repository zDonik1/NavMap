#pragma once

#include <istream>
#include <algorithm>
#include "adjlistnondirgraph.h"
#include "queue.h"
#include "vector2.h"


// --- "using" types

using CharMap = std::vector<std::vector<char>>;
using Road = std::pair<Vector2, Vector2>;
using Roads = std::vector<Road>;
using PosDir = std::pair<Vector2, Vector2>;


class Map
{
private:

    // --- Classes

    struct Vertex
    {
        char name;
        Vector2 pos;

        Vertex()
        {
        }

        Vertex(Vector2 l_pos)
            : name('\0')
            , pos(l_pos)
        {
        }

        Vertex(char l_name, Vector2 l_pos)
            : name(l_name)
            , pos(l_pos)
        {
        }
    };


    // --- Member variables

    AdjListNonDirGraph m_graph;
    CharMap m_char_map;
    std::vector<Vertex> m_nodes;

    char m_road_char = '\0';
    char m_correct_road = '\0';
    char m_endp_char = '\0';


    // --- Helper methods

    auto findNode(const Vector2 &l_pos) const;
    auto findNode(char l_char) const;
    auto findNodeOrThrow(char l_char) const;

    bool isOutOfBounds(const CharMap &l_char_map, const Vector2 &l_node) const;
    bool isNode(const Vector2 &l_node) const;
    bool isEndpointChar(char l_ch) const;

    bool loadCharMap(std::istream &stream);
    void loadEndpoints(const CharMap &l_char_map);
    void labelCharMap();

    std::vector<Vector2> initDirections();

    void initBFSQueue(const std::vector<Vector2> &l_directions,
                      const CharMap &l_char_map,
                      Queue<PosDir> &l_bfs_queue);

    void handleBFSQueue(Queue<PosDir> &l_bfs_queue, CharMap &l_char_map,
                        Roads &l_roads, const std::vector<Vector2> &l_directions);

    void moveRunner(Vector2 &l_runner, const PosDir &l_pos_dir, Queue<PosDir> &l_bfs_queue,
                    CharMap &l_char_map, Roads &l_roads, const std::vector<Vector2> &l_directions);

    void checkAdjacentRoad(std::vector<Vector2> &l_road_dirs, const PosDir &l_pos_dir,
                           const std::vector<Vector2> &l_directions,
                           const CharMap &l_char_map, Vector2 &l_runner);

    Roads loadRoads(const CharMap &l_char_map);
    auto insertNode(const Vector2 &l_node);
    void loadGraph(Roads &l_roads);

    void markCorrectRoad(int l_start, int l_finish, int l_x_y, bool l_is_x,
                         CharMap &l_char_map) const;


public:

    // --- Member functions

    const CharMap &getCharMap() const;
    CharMap getCharMapWithPath(char l_vert1, char l_vert2) const;

    void setCharMapEncoding(char l_road_char, char l_correct_char,
                            char l_endp_char);

    bool load(std::istream &stream);
};
