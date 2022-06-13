//
// Created by mao on 22-6-13.
//
//欧氏变换
//已知两机器人位姿，同一点的坐标转换
//T(q,t)表示位姿,p1表示在机器人1下的坐标
#include "iostream"
#include "vector"
#include "algorithm"
#include "Eigen/Core"
#include "Eigen/Geometry"

using namespace std;
using namespace Eigen;

int main(){
    //输入已知数据
    Quaterniond q1(0.35, 0.2, 0.3, 0.1), q2(-0.5, 0.4, -0.1, 0.2);
    //归一化
    q1.normalize();
    q2.normalize();
    Vector3d t1(0.3, 0.1, 0.1), t2(-0.1, 0.5, 0.3);
    Vector3d p1(0.5, 0, 0.2);
    //转换为欧式变换
    Isometry3d T1(q1),T2(q2);
    T1.pretranslate(t1);
    T2.pretranslate(t2);

    Vector3d p2 = T2 * T1.inverse() * p1;
    cout<<p2<<endl;


    return 0;
}


