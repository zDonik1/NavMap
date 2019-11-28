#include "map.h"


// --- Helper methods

auto Map::findNode(const Vector2 &l_node) const
{
    return std::find_if(m_nodes.begin(), m_nodes.end(),
                        [&l_node] (auto &vertex)
                        {
                            return vertex.pos == l_node;
                        });
}

auto Map::findNode(char l_char) const
{
    return std::find_if(m_nodes.cbegin(), m_nodes.cend(),
                        [&l_char] (auto &vertex)
                        {
                            return vertex.name == l_char;
                        });
}

auto Map::findNodeOrThrow(char l_char) const
{
    auto itr = findNode(l_char);
    if (itr == m_nodes.end()) {
        throw std::out_of_range("graph does not contain such node");
    }
    return itr;
}


bool Map::isOutOfBounds(const CharMap &l_char_map, const Vector2 &l_node) const
{
    if (l_node.x < 0 || l_node.x >= static_cast<int>(l_char_map.size())
        || l_node.y < 0 || l_node.y >= static_cast<int>(l_char_map.back().size()))
    {
        return true;
    }

    return false;
}

bool Map::isNode(const Vector2 &l_node) const
{
    return findNode(l_node) != m_nodes.end();
}

bool Map::isEndpointChar(char l_ch) const
{
    return l_ch >= 'A' && l_ch <= 'Z';
}


bool Map::loadCharMap(std::istream &stream)
{
    std::string line;
    while (std::getline(stream, line)) {
        // This is to trim trailing \r character
        line.erase(std::remove(line.begin(), line.end(), '\r'), line.end());

        if (!m_char_map.size()) {
            for (size_t i = 0; i < line.size(); ++i) {
                m_char_map.push_back(std::vector<char>());
            }
        }
        else if (line.size() != m_char_map.size()) {
            return false;
        }

        for (size_t i = 0; i < m_char_map.size(); ++i) {
            m_char_map.at(i).insert(m_char_map.at(i).begin(), line.at(i));
        }
    }

    return true;
}

void Map::loadEndpoints(const CharMap &l_char_map)
{
    for (size_t i = 0; i < l_char_map.back().size(); ++i) {
        for (size_t j = 0; j < l_char_map.size(); ++j) {
            if (l_char_map.at(j).at(i) == m_endp_char) {
                m_nodes.push_back(Vertex(static_cast<char>('A' + m_nodes.size()),
                                         {static_cast<int>(j), static_cast<int>(i)}));
            }
        }
    }
}

void Map::labelCharMap()
{
    for (auto &node : m_nodes) {
        if (node.name == '\0') {
            break;
        }

        m_char_map
            .at(static_cast<size_t>(node.pos.x))
            .at(static_cast<size_t>(node.pos.y))
            = node.name;
    }
}

std::vector<Vector2> Map::initDirections()
{
    std::vector<Vector2> directions(4);
    directions[0] = Vector2(0, 1);
    directions[1] = Vector2(1, 0);
    directions[2] = Vector2(0, -1);
    directions[3] = Vector2(-1, 0);
    return directions;
}

void Map::initBFSQueue(const std::vector<Vector2> &l_directions,
                       const CharMap &l_char_map,
                       Queue<PosDir> &l_bfs_queue)
{
    for (auto &dir : l_directions) {
        auto &first_node_pos = m_nodes.at(0).pos;
        if (l_char_map
                .at(static_cast<size_t>(first_node_pos.x + dir.x))
                .at(static_cast<size_t>(first_node_pos.y + dir.y))
            == m_road_char)
        {
            l_bfs_queue.push({m_nodes.at(0).pos, dir});
        }
    }
}

void Map::checkAdjacentRoad(std::vector<Vector2> &l_road_dirs, const PosDir &l_pos_dir,
                            const std::vector<Vector2> &l_directions,
                            const CharMap &l_char_map, Vector2 &l_runner)
{
    for (const auto &dir : l_directions) {
        Vector2 check_road = l_runner + dir;
        char check_char = l_char_map
                              .at(static_cast<size_t>(check_road.x))
                              .at(static_cast<size_t>(check_road.y));
        if (isOutOfBounds(l_char_map, check_road)
            || check_road == l_runner - l_pos_dir.second)
        {
            continue;
        }

        if (check_char == m_correct_road && !isNode(check_road)) {
            continue;
        }

        if (check_char == m_road_char
            || check_char == m_correct_road
            || isEndpointChar(check_char))
        {
            l_road_dirs.push_back(dir);
        }
    }
}

void Map::moveRunner(Vector2 &l_runner, const PosDir &l_pos_dir, Queue<PosDir> &l_bfs_queue,
                     CharMap &l_char_map, Roads &l_roads, const std::vector<Vector2> &l_directions)
{
    while (true) {
        std::vector<Vector2> road_dirs;
        checkAdjacentRoad(road_dirs, l_pos_dir, l_directions, l_char_map, l_runner);

        char &runner_char = l_char_map
                                .at(static_cast<size_t>(l_runner.x))
                                .at(static_cast<size_t>(l_runner.y));
        if (!isEndpointChar(runner_char)) {
            runner_char = m_correct_road;
        }

        if (road_dirs.size() == 1 && road_dirs.back() == l_pos_dir.second) {
            l_runner += l_pos_dir.second;
        }
        else {
            for (const auto &dir : road_dirs) {
                l_bfs_queue.push({l_runner, dir});
            }

            if (!isNode(l_runner)) {
                m_nodes.push_back(Vertex(l_runner));
            }

            l_roads.back().second = l_runner;
            break;
        }
    }
}

void Map::handleBFSQueue(Queue<PosDir> &l_bfs_queue, CharMap &l_char_map,
                         Roads &l_roads, const std::vector<Vector2> &l_directions)
{
    while (!l_bfs_queue.empty()) {
        auto pos_dir = l_bfs_queue.top();
        l_bfs_queue.pop();

        Vector2 runner = pos_dir.first + pos_dir.second;
        char temp_runner_char = l_char_map
                                    .at(static_cast<size_t>(runner.x))
                                    .at(static_cast<size_t>(runner.y));
        if (isOutOfBounds(l_char_map, runner)
            || temp_runner_char == m_correct_road)
        {
            continue;
        }

        l_roads.push_back({pos_dir.first, Vector2(0, 0)});

        moveRunner(runner, pos_dir, l_bfs_queue, l_char_map, l_roads, l_directions);
    }
}

Roads Map::loadRoads(const CharMap &l_char_map)
{
    CharMap ch_map_copy = l_char_map;
    std::vector<Vector2> directions = initDirections();

    loadEndpoints(ch_map_copy);
    labelCharMap();

    Roads roads;
    Queue<PosDir> bfs_queue;
    std::vector<Vector2> visited_nodes;

    initBFSQueue(directions, ch_map_copy, bfs_queue);
    handleBFSQueue(bfs_queue, ch_map_copy, roads, directions);

    return roads;
}

auto Map::insertNode(const Vector2 &l_node)
{
    auto itr = findNode(l_node);
    if (itr == m_nodes.end()) {
        m_nodes.push_back({l_node});
    }
    return itr;
}

void Map::loadGraph(Roads &l_roads)
{
    for (auto &road : l_roads) {
        auto first_itr = insertNode(road.first);
        auto second_itr = insertNode(road.second);

        Vector2 diff_vec = road.first - road.second;
        auto v1_index = static_cast<size_t>(std::distance(m_nodes.cbegin(), first_itr));
        auto v2_index = static_cast<size_t>(std::distance(m_nodes.cbegin(), second_itr));
        auto distance = std::abs(diff_vec.x == 0 ? diff_vec.y : diff_vec.x);
        m_graph.insertEdge(v1_index, v2_index, distance);
    }

    m_graph.finalize();
}


// --- Member functions

const CharMap &Map::getCharMap() const
{
    return m_char_map;
}

void Map::markCorrectRoad(int l_start, int l_finish, int l_x_y, bool l_is_x,
                          CharMap &l_char_map) const
{
    size_t i_begin = static_cast<size_t>(std::min(l_start, l_finish));
    size_t i_end = static_cast<size_t>(std::max(l_start, l_finish));
    for (size_t i = i_begin; i <= i_end; ++i) {
        char *ch = nullptr;
        if (l_is_x) {
            ch = &l_char_map.at(static_cast<size_t>(l_x_y)).at(i);
        }
        else {
            ch = &l_char_map.at(i).at(static_cast<size_t>(l_x_y));
        }
        if (*ch == m_road_char) {
            *ch = m_correct_road;
        }
    }
}

CharMap Map::getCharMapWithPath(char l_vert1, char l_vert2) const
{
    auto v1_itr = findNodeOrThrow(l_vert1);
    auto v2_itr = findNodeOrThrow(l_vert2);

    int v1_index = std::distance(m_nodes.begin(), v1_itr);
    int v2_index = std::distance(m_nodes.begin(), v2_itr);
    auto path = m_graph.getShortestPath(static_cast<size_t>(v1_index),
                                        static_cast<size_t>(v2_index));

    CharMap ch_map_copy = m_char_map;
    Vector2 first_pos = m_nodes.at(static_cast<size_t>(path.top())).pos;
    path.pop();
    Vector2 second_pos;
    while (!path.empty()) {
        second_pos = m_nodes.at(static_cast<size_t>(path.top())).pos;
        path.pop();

        if (first_pos.x - second_pos.x == 0) {
            markCorrectRoad(first_pos.y, second_pos.y, first_pos.x, true, ch_map_copy);
        }
        else if (first_pos.y - second_pos.y == 0) {
            markCorrectRoad(first_pos.x, second_pos.x, first_pos.y, false, ch_map_copy);
        }

        first_pos = second_pos;
    }

    return ch_map_copy;
}

void Map::setCharMapEncoding(char l_road_char, char l_correct_char, char l_endp_char)
{
    m_road_char = l_road_char;
    m_correct_road = l_correct_char;
    m_endp_char = l_endp_char;
}

bool Map::load(std::istream &stream)
{
    if (m_road_char == '\0' || m_correct_road == '\0' || m_endp_char == '\0') {
        return false;
    }

    if (!loadCharMap(stream)) {
        return false;
    }

    auto roads = loadRoads(m_char_map);
    loadGraph(roads);

    return true;
}
