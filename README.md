# UTM <----> FRENET

## 功能介绍
- Class Map
  - getXY:输入sd，获取xy
  - getSD:输入x,y,theta，获取sd

## 思路介绍
- 读入地图中的x,y，针对每对x,y，累计s值，并一起存入map类。
- getXY和getSD是一些搜索 + 简单的几何变换
- 搜索的过程实现了两种方案，一种基于暴力搜索，一种基于四叉树的搜索。提交给您的代码是基于四叉树搜索的，在nextWP函数中可以选择使用暴力或者四叉树。

## 优化方向
- 目前只针对(x，y)最近点的搜索实现了四叉树的方法，针对s的搜索，也可以使用二叉树。考虑到实现原理基本一致，且难度比四叉树小，暂时没有实现（主要是今天还要给导师交付一个项目，时间有点匆忙）。

## 编译运行
```
  cd ${PRoJECT_FILE}
  cd build
  cmake ..
  make -j8
  ./ali
```

## 测试
- main函数中有多个测试案例。
- 人为定义sd转换为对应的(x,y)之后，利用得到的(x,y)转换回去(s,d)，看是否与定义的sd相等。

## 文件介绍
├── build：在这里编译运行
├── CMakeLists.txt
├── include
│   ├── Common.h：常用头文件引用
│   ├── helper.h：简单的辅助函数
│   ├── Map.h：Map类的头文件
│   ├── QuadTree
│   │   └── Quadtree.h：四叉树的头文件
│   └── WayPoint.h：路点类的头文件
├── map
│   └── map.csv：地图，存储了一堆xy坐标
├── README.md
└── src
    ├── main.cpp：主函数
    ├── Map.cpp：Map类实现
    ├── QuadTree
    │   └── Quadtree.cpp：四叉树实现
    └── WayPoint.cpp：路点类实现

