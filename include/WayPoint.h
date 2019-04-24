//
// Created by luyifan on 19-4-24.
//

#ifndef ALI_WAYPOINT_H
#define ALI_WAYPOINT_H

#include "Common.h"

class WayPoint{
public:
    WayPoint(double x, double y, double s, long long id);
    ~WayPoint();

    inline double x(){ return x_; }
    inline double y(){ return y_; }
    inline double s(){ return s_; }
    inline double id(){ return id_; }

    inline void setX(double x){ x_ = x;}
    inline void setY(double y){ y_ = y;}
    inline void setS(double s){ s_ = s;}

private:
    double x_;
    double y_;
    double s_;
    long long id_;
};

#endif //ALI_WAYPOINT_H
