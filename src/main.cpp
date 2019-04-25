//
// Created by luyifan on 19-4-24.
//

#include "Map.h"
#include "helper.h"

int main(int argc, char** argv){
    //构造并加载地图
    Map map;
    if(!map.loadMapFile("../map/map.csv")){
        cerr<<"Loading failed!"<<endl;
        return 0;
    }

    //map.print();
    //功能测试
    //cout<<"s: "<<map.refLine().back().s()<<endl;
    double s = 140;double d = 6;
    cout<<"test sd: ("<<s<<" ,"<<d<<")"<<endl;
    Eigen::Vector2d xy = map.getXY(s, d);
    cout<<"transfrom to UTM: ("<<xy[0]<<", "<<xy[1]<<")"<<endl;
    Eigen::Vector2d sd = map.getSD(xy[0], xy[1], 0);
    cout<<"return to sd: ("<<sd[0]<<" ,"<<sd[1]<<")"<<endl;
    cout<<"-------"<<endl;

    s = 300;d = -3;
    cout<<"test sd: ("<<s<<" ,"<<d<<")"<<endl;
    xy = map.getXY(s, d);
    cout<<"transfrom to UTM: ("<<xy[0]<<", "<<xy[1]<<")"<<endl;
    sd = map.getSD(xy[0], xy[1], 0);
    cout<<"return to sd: ("<<sd[0]<<" ,"<<sd[1]<<")"<<endl;
    cout<<"-------"<<endl;

    s = 3000;d = 14;
    cout<<"test sd: ("<<s<<" ,"<<d<<")"<<endl;
    xy = map.getXY(s, d);
    cout<<"transfrom to UTM: ("<<xy[0]<<", "<<xy[1]<<")"<<endl;
    sd = map.getSD(xy[0], xy[1], 0);
    cout<<"return to sd: ("<<sd[0]<<" ,"<<sd[1]<<")"<<endl;
    cout<<"-------"<<endl;

    s = 300;d = -2;
    cout<<"test sd: ("<<s<<" ,"<<d<<")"<<endl;
    xy = map.getXY(s, d);
    cout<<"transfrom to UTM: ("<<xy[0]<<", "<<xy[1]<<")"<<endl;
    sd = map.getSD(xy[0], xy[1], 0);
    cout<<"return to sd: ("<<sd[0]<<" ,"<<sd[1]<<")"<<endl;
    cout<<"-------"<<endl;
}