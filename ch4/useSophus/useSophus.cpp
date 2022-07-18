//
// Created by mao on 22-7-18.
// useSophus
//
#include <iostream>
#include <cmath>
#include <Eigen/Core>
#include <Eigen/Geometry>
#include "sophus/se3.hpp"

using namespace std;
using namespace Eigen;

int main(){
    //沿Z轴旋转90度的旋转矩阵
    Matrix3d R = AngleAxisd(M_PI/2,Vector3d(0,0,1)).toRotationMatrix();
    //转换为四元数
    Quaterniond q(R);
    //构造SO3d
    Sophus::SO3d SO3_R(R);
    Sophus::SO3d SO3_q(q);
    //cout<<R<<endl;
    //cout<<SO3_R.matrix();

    //获取李代数so3 对数映射
    Vector3d so3 = SO3_R.log();
    cout<<so3<<endl;

    //hat 反对称矩阵
    //cout<<Sophus::SO3d::hat(so3);
    //vee 反对称矩阵到向量
    //cout<<Sophus::SO3d ::vee(Sophus::SO3d::hat(so3));

    //cout<<Sophus::SO3d ::hat(Sophus::SO3d::hat(so3));

    //增量扰动模型更新
    Vector3d update_so3(1e-4,0,0);
    Sophus::SO3d SO3_update = Sophus::SO3d::exp(update_so3)*SO3_R;

    //SE3
    Vector3d t(1,0,0);
    Sophus::SE3d SE3d_Rt(R,t);

    //typedef se3
    typedef Eigen::Matrix<double,6,1> Vector6d;
    Vector6d se3 = SE3d_Rt.log();
    //
    return 0;
}