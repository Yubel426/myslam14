#include <iostream>
#include "cmath"
using namespace std;

#include "Eigen/Core"
#include "Eigen/Geometry"
using namespace Eigen;
//Geometry 几何
int main() {
    Matrix3d rotation_matrix = Matrix3d::Identity();
    //旋转向量 AngleAxisd axisd 轴 z轴 45度
    AngleAxisd rotation_vector(M_PI/4 , Vector3d(0,0,1));
    //精度控制
    cout.precision(3);
    // vector.matrix() 旋转向量转换为旋转矩阵
    //cout<<rotation_vector.matrix()<<endl;
    // 赋值 转换
    rotation_matrix = rotation_vector.toRotationMatrix();
    Vector3d v(1,0,0);
    //旋转变换
    Vector3d v_rotation = rotation_matrix * v;
    //v_rotation = rotation_vector * v;
    //cout<<v_rotation<<endl;

    //欧拉角变换 zyx顺序
    Vector3d euler_angle = rotation_matrix.eulerAngles(2,1,0);
    //cout<<euler_angle;
    //欧氏变换矩阵
    Isometry3d T = Isometry3d ::Identity();
    T.rotate(rotation_vector);
    T.pretranslate(Vector3d(1,3,4));
    //cout<<T.matrix();
    //变换
    Vector3d v_transform = T * v;
    //cout<<v_transform;

    //四元数
    //将vector赋值给q
    Quaterniond q =Quaterniond(rotation_vector);
    //q = Quaterniond (rotation_matrix);
    //.coeffs 三虚部 实部 顺序
    //cout<<q.coeffs();

    //变换
    v_rotation = q * v;
    return 0;

}
