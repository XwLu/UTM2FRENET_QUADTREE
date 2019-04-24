#ifndef __QUADTREE_H__
#define __QUADTREE_H__

#include <vector>
#include "WayPoint.h"

using namespace std;

class Quadtree;
class WayPoint;

class Quadtree {
public:
    Quadtree(float x, float y, float width, float height, int level, int maxLevel);
    ~Quadtree();

    void            AddObject(WayPoint *object);
    vector<WayPoint*> GetObjectsAt(float x, float y);
    void            Clear();

private:
    float           x;
    float           y;
    float           width;
    float           height;
    int             level;
    int             maxLevel;
    vector<WayPoint*> objects;

    Quadtree *      parent;
    Quadtree *      NW;
    Quadtree *      NE;
    Quadtree *      SW;
    Quadtree *      SE;

    bool            contains(Quadtree *child, WayPoint *object);
};

#endif
