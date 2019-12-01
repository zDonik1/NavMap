# NavMap
This is a demo application to implement dijkstra's algorithm in graphs, as IUT DS project assignment - 2nd course.

### Explanation

Circular single linked list is used to implement stack, queue, and adjacency list graph. Implemented using tail pointer for quick access and insertion to end with time complexity O(1).

Queue is used in modified BFS algorithm for running through all the roads.

Stack is used to reverse the order in which dijkstra's algorithm return the path.

Dynamic array (also known as std::vector in c++ STL) is used to store character map and the vertices inside the graph. Since it is dynamic, preliminary knowledge of the size of the map and number of vertices inside the map is not required.

Weighted non-directional graph is used to represent the map and relationship between each vertex, marking the road. Also facilitaties usage of dijkstra's algorithm on the graph.

### Specifics

A map file, which stores a character map, is loaded into the application and all the roads are read and loaded into a graph. The dijkstra's algorithm finds shortest path between two nodes and is simply output in the form of a character map.

Each line inside the character map should consist of equal number of characters. Any spaces inside the character map are ignored. There are 3 types of characters that can be used - road, endpoints, and filler. The characters that cannot be used in the character map are spaces as any of 3 character types and capital English letters as road or filler characters.

Each character can also have a background and text colour. There are 16 colours that are defined inside the colour_encoding.config:
* Black
* Blue
* Sky_Blue
* Red
* Violet
* Gold
* Light_Gray
* Gray
* Light_Blue
* Light_Green
* Cyan
* Light_Red
* Purple
* Light_Yellow
* White

### Usage

The necessary resource files are given in the examples folder and should be placed in the compiled build folder with the NavMap.exe file

### Example

This example shows usage of the application:  

The user is asked for 2 letters - starting and ending nodes. The letters should be written in capital English letters.

![User prompt](/images/UserPrompt.PNG)

After entering the endpoints such as K and G, we get the shortest path between those endpoints.

![Resulting_path](/images/ResultingPath.PNG)

### Author

Doniyorbek Tokhirov < tokhirovdoniyor@gmail.com >

### Credits

Nodirbek Shopayziev  
Mukambar Karimova  
Dmitriy Liyuriy
