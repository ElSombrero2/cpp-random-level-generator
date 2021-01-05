#ifndef __MAP_H__
#define __MAP_H__

#define LEFT 1
#define MIDDLE 2
#define RIGHT 3
#define COINC 5
#define VOID 0

#include <vector>

using namespace std;

typedef struct Neighbour{
    int id;
    int chance;
}Neighbour;

class Node{
public:
    Node(int id,int start,int end,int sc,int ec,int mc,vector<Neighbour> n)
    {
        this->id=id;
        this->start_depth=start;
        this->end_depth=end;
        start_chance=sc;
        end_chance=ec;
        middle_chance=mc;
        neighbours=n;
    }
    int id;
    int start_depth;
    int end_depth;
    vector<Neighbour> neighbours;
    int start_chance;
    int end_chance;
    int middle_chance;
};

int* generateMap(vector<Node>&,int,int);

#endif