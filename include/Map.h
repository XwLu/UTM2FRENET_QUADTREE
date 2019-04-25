//
// Created by luyifan on 19-4-24.
//

#ifndef ALI_MAP_H
#define ALI_MAP_H

#include "Common.h"
#include "WayPoint.h"
#include "Quadtree.h"

class Map{
public:
    Map();
    ~Map();

    bool loadMapFile(string path);
    inline vector<WayPoint> refLine(){ return reference_line_;}

    Eigen::Vector2d getSD(double x, double y, double theta);
    Eigen::Vector2d getXY(double s, double d);

    int findClosestWP(double x, double y);
    int findClosestWPQT(double x, double y);
    int nextWP(double x, double y, double theta);
    void print();

private:
    vector<WayPoint> reference_line_;
    Quadtree* qt4xy_;
};

#endif //ALI_MAP_H
