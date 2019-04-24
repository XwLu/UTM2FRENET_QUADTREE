//
// Created by luyifan on 19-4-24.
//

#include "Map.h"
#include "helper.h"

int main(int argc, char** argv){
    Map map;
    Eigen::Vector4d pts;
    if(!map.loadMapFile("../map/map.csv", pts)){
        cerr<<"Loading failed!"<<endl;
        return 0;
    }

    double origin_x = pts[0];
    double origin_y = pts[1];
    double width = pts[2] - pts[0];
    double height = pts[3] - pts[1];
    int level = getLevel(min(width, height), 30);

    Quadtree* qt = new Quadtree(origin_x-1, origin_y-1, width+2, height+2, 1, level);
    map.setQT(qt);
    map.addWPs();

    //map.print();
    cout<<"s: "<<map.refLine().back().s()<<endl;
    Eigen::Vector2d xy = map.getXY(140, 6);
    //cout<<"x: "<<xy[0]<<" y: "<<xy[1]<<endl;
    Eigen::Vector2d sd = map.getSD(927.1323, 1134.897, MY_PI*0.5);
    cout<<"s: "<<sd[0]<<" d: "<<sd[1]<<endl;
}