//
// Created by luyifan on 19-4-24.
//

#include "Map.h"
#include <fstream>
#include "helper.h"

using namespace std;

Map::Map():qt4xy_(nullptr) {

}

Map::~Map() {
    free(qt4xy_);
    delete(qt4xy_);
}

bool Map::loadMapFile(string map_file) {
    double s = MY_INF;
    double last_x = MY_INF, last_y = MY_INF;
    std::ifstream in_map_(map_file.c_str(), std::ifstream::in);
    string line;
    //地图的左下和右上角
    double minX = MY_INF;
    double minY = MY_INF;
    double maxX = -MY_INF;
    double maxY = -MY_INF;
    long long id = 0;
    //逐行获取地图内容
    while (getline(in_map_, line)) {
        std::istringstream iss(line);
        double x;
        double y;
        iss >> x;
        iss >> y;

        if(s == MY_INF)
            s = 0;
        else
            s += dist2Pts(last_x, last_y, x, y);
        reference_line_.emplace_back(WayPoint(x, y, s, id));
        id++;
        last_x = x;
        last_y = y;

        minX = (minX < x)?minX : x;
        minY = (minY < y)?minY : y;
        maxX = (maxX > x)?maxX : x;
        maxY = (maxY > y)?maxY : y;
    }
    if(reference_line_.empty()){
        cerr<<"No data in map file!"<<endl;
        return false;
    }
    //留出一定的裕度，然而超过这个裕度，四叉树就搜索不到了，一般来说检索地图的时候也不会检索距离reference line很远的点
    minX -= 100;
    minY -= 100;
    maxX += 100;
    maxY += 100;

    //根据地图的左下和右上角自适应调整四叉树层数
    double width = maxX - minX;
    double height = maxY - minY;
    int level = getLevel(min(width, height), 100);
    //level = 2;
    //构建四叉树
    qt4xy_ = new Quadtree(minX, minY, width, height, 1, level);
    for(auto& pt : reference_line_){
        qt4xy_->AddObject(&pt);
    }

    return true;
}

Eigen::Vector2d Map::getXY(double s, double d) {
    if(s > reference_line_.back().s()){
        cerr<<"s is out of range!"<<endl;
        return Eigen::Vector2d(0, 0);
    }

    int pre_id = -1;
    vector<WayPoint>::iterator it = reference_line_.begin();
    while(s > (it++)->s() && it != reference_line_.end()){
        ++pre_id;
    }
    int next_id = pre_id+1;
    double yaw = atan2((reference_line_[next_id].y() - reference_line_[pre_id].y()),
                       (reference_line_[next_id].x() - reference_line_[pre_id].x()));
    double part_s = s - reference_line_[pre_id].s();
    double part_x = reference_line_[pre_id].x() + part_s * cos(yaw);
    double part_y = reference_line_[pre_id].y() + part_s * sin(yaw);

    yaw = yaw - MY_PI * 0.5;
    double x = part_x + d * cos(yaw);
    double y = part_y + d * sin(yaw);
    return Eigen::Vector2d(x, y);
}

Eigen::Vector2d Map::getSD(double x, double y, double theta) {
    int next_id = nextWP(x, y, theta);
    if(next_id < 0){
        cerr<<"x,y invalid!"<<endl;
        return Eigen::Vector2d(0, 0); //xy落在范围外，无效数据。
    }
    int pre_id = next_id - 1;
    //前一个点和后一个点的连线L1
    double fb_x = reference_line_[next_id].x() - reference_line_[pre_id].x();
    double fb_y = reference_line_[next_id].y() - reference_line_[pre_id].y();
    //(x, y)和前一个点的连线L2
    double fx_x = x - reference_line_[pre_id].x();
    double fy_y = y - reference_line_[pre_id].y();
    //把L2投影到L1
    double norm = (fx_x*fb_x+fy_y*fb_y)/(fb_x*fb_x+fb_y*fb_y);
    double proj_x = norm*fb_x;
    double proj_y = norm*fb_y;
    //投影的垂线就是d的模
    double d = dist2Pts(fx_x, fy_y, proj_x, proj_y);
    //d的正负判断

    double tmp = (reference_line_[pre_id].y() - reference_line_[next_id].y()) * x +
            (reference_line_[next_id].x() - reference_line_[pre_id].x()) * y +
            reference_line_[pre_id].x()*reference_line_[next_id].y() -
            reference_line_[next_id].x() * reference_line_[pre_id].y();
    if(tmp > 0)
        d = -d;

    double s = reference_line_[pre_id].s();
    s += dist2Pts(0, 0, proj_x, proj_y);
    return Eigen::Vector2d(s, d);
}

void Map::print() {
    for(auto pt: reference_line_){
        cout<<"x: "<<pt.x()<<" y: "<<pt.y()<<" s: "<<pt.s()<<endl;
    }
}

int Map::findClosestWP(double x, double y) {
    double min_dist = MY_INF;
    int id = 0;
    for(int i = 0; i < reference_line_.size(); ++i){
        double ref_x = reference_line_[i].x();
        double ref_y = reference_line_[i].y();
        double dist = dist2Pts(x, y, ref_x, ref_y);
        if(dist < min_dist){
            min_dist = dist;
            id = i;
        }
    }
    return id;
}

int Map::findClosestWPQT(double x, double y) {
    vector<WayPoint*> pts = qt4xy_->GetObjectsAt(x, y);
    if(pts.empty()){
        cerr<<"x, y are too far away from the reference line( >=30m )"<<endl;
        return -1;
    }
    else{
        //cout<<"pts: "<<pts.size()<<endl;
        sort(pts.begin(), pts.end(),
             [x, y](WayPoint* a, WayPoint* b)
             { return dist2Pts(a->x(), a->y(), x, y) < dist2Pts(b->x(), b->y(), x, y);});
    }
    return pts.front()->id();
}

int Map::nextWP(double x, double y, double theta) {
    int closest_id = findClosestWPQT(x, y);
    //cout<<"QT based search: "<<closest_id<<endl;
    //closest_id = findClosestWP(x, y);
    //cout<<"Brute-force search: "<<closest_id<<endl;
    //cout<<"distance: "<<dist2Pts(reference_line_[closest_id].x(), reference_line_[closest_id].y(), x, y)<<endl;
    if(closest_id < 0){
        return -1;
    }
    double ref_x = reference_line_[closest_id].x();
    double ref_y = reference_line_[closest_id].y();

    double yaw = atan2((ref_y - y), (ref_x - x));

    double angle = fabs(theta - yaw);
    angle = std::min(2*MY_PI - angle, angle);

    if(angle > MY_PI*0.5){
        closest_id++;
        if(closest_id == reference_line_.size()){
            cerr<<"(x,y) is located behind the last way point."<<endl;
            closest_id = -1;
        }
        else if(closest_id == 0){
            cerr<<"(x, y) is located in front of the first way point."<<endl;
            closest_id = -1;
        }
    }
    return closest_id;
}
