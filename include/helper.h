//
// Created by luyifan on 19-4-24.
//

#ifndef ALI_HELPER_H
#define ALI_HELPER_H

inline double dist2Pts(double x1, double y1, double x2, double y2) {
    return sqrt((x2-x1)*(x2-x1)+(y2-y1)*(y2-y1));
}

inline int getLevel(double range, double min_T){
    int n = 1;
    while(1){
        range /= 2;
        if(range <= min_T)
            return n;
        n++;
    }
}

#endif //ALI_HELPER_H
