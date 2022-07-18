# slam14讲

## ch2 

### cmkae学习

##### 安装cmake

```shell
#安装cmake 找不到cmake
export PATH=/home/mao/cmake/bin:$PATH
```



```cmake
cmake_minimum_required(VERSION 3.22)
#创建
project(hello_slam)

set(CMAKE_BUILD_TYPE "Debug")

#创建应用 应用名 应用文件
add_executable(hello_slam main.cpp)

#添加库 库名 库文件 .cpp
add_library(hello libhelloslam.cpp)
#添加共享库
add_library(hello_shared SHARED libhelloslam.cpp)


#       应用名 库名
#target_link_libraries(hello_slam hello)

target_link_libraries(hello_slam hello_shared)
```

.h文件中 

```c++
// .h
//#include<> 不需要
void print();//主要；
```

 .cpp文件中

```c++
// .cpp
#include<iostream>
using namespace std;
```

main.cpp

```c++
#include".h"//" "
```



## ch3三维空间刚体运动

### 3.1旋转矩阵

#### 3.1.1点，向量，坐标系

##### 内积

$a \cdot b=a^Tb=\sum_{i=1}^3a_ib_i$

##### 外积

#### 3.1.2欧氏变换

* 旋转矩阵

​		$SO(n)$特殊正交群，R~12~表示坐标系2变换到坐标系1的旋转矩阵。

* 平移矩阵

​		t~12~表示2到1的向量。实际表示1到2原点间的向量。注意t~12~和t~21~之间并不是简单负号的关系。

#### 3.1.3齐次坐标

 增加一维。左上为旋转矩阵R,右上为平移矩阵t，左下0,右下为1,记为SE(n)。

### 3.2Eigen

##### 换源

```shell
#备份
sudo cp /etc/apt/sources.list /etc/apt/sources.list.bak

sudo vim /etc/apt/sources.list
#全部删除命令 ggdG
# 默认注释了源码镜像以提高 apt update 速度，如有需要可自行取消注释
deb https://mirrors.tuna.tsinghua.edu.cn/ubuntu/ jammy main restricted universe multiverse
# deb-src https://mirrors.tuna.tsinghua.edu.cn/ubuntu/ jammy main restricted universe multiverse
deb https://mirrors.tuna.tsinghua.edu.cn/ubuntu/ jammy-updates main restricted universe multiverse
# deb-src https://mirrors.tuna.tsinghua.edu.cn/ubuntu/ jammy-updates main restricted universe multiverse
deb https://mirrors.tuna.tsinghua.edu.cn/ubuntu/ jammy-backports main restricted universe multiverse
# deb-src https://mirrors.tuna.tsinghua.edu.cn/ubuntu/ jammy-backports main restricted universe multiverse
deb https://mirrors.tuna.tsinghua.edu.cn/ubuntu/ jammy-security main restricted universe multiverse
# deb-src https://mirrors.tuna.tsinghua.edu.cn/ubuntu/ jammy-security main restricted universe multiverse

# 更新镜像源
sudo apt-get update
# 更新软件
sudo apt-get upgrade  
```



安装Eigen

```shell
sudo apt-get install libeigen3-dev
```

使用库先在cmakelist中include directory

```cmake
# 添加Eigen头文件
include_directories( "/usr/include/eigen3" )
```

```c++
Matrix<float , 2, 3>matrix_23;//定义一个2*3矩阵，数据类型为float
Matrix3d matrix_33;//定义一个3*3矩阵 数据类型为double
Vector3d v_3d;//定义一个3维向量
```

### 3.3旋转向量和欧拉角

#### 3.3.1旋转向量

使用一个向量表示旋转，旋转轴，旋转角。使用旋转向量和平移向量表示变换矩阵。

旋转矩阵R和旋转向量n关系。

```c++
AngleAxisd rotation_vector(M_PI,Vector_3d(1,1,1));//定义一个旋转向量
Matrix3d rotation_matrix = rotation_vector.toRotationMatrix();//转换为旋转矩阵
```

#### 3.3.2欧拉角

ZYX旋转。[r,p,y]，roll ,pitch,yaw。

万向锁问题。用三个代数表示旋转都具有奇异性。

```c++
Vector3d euler_angle = rotation_matrix.eulerAngles(2,1,0);//按照zyx顺序转换为欧拉角

Isometry3d T;//定义一个欧式变换矩阵
T.rotate(rotation_vector);
T.pretranslate(Vector3d(1,2,3));;//定义其旋转向量和平移向量
```



### 3.4四元数

```c++
Quaterniond q = Quaterniond(rotation_vector);//定义一个四元数并用旋转向量转换
```



### 实践

#### 显示运动轨迹

##### 安装依赖

```shell
sudo apt-get install libglew-dev
```

##### 安装pangolin

```shell
git clone https://github.com/stevenlovegrove/Pangolin.git
cd Pangolin
mkdir build
cd build
cmake ..
make
sudo make install
ldconfig
```

`trajectory_file`依次储存了`time`,`Vector(tx,ty,tz)`,`Q(qx,qy,qz,qw)`。

使用一个`Vector`储存它们。

```c++
vector<Isometry3d, Eigen::aligned_allocator<Isometry3d>> poses;
```

使用函数`DrawTrajectory`绘制图像

```c++
void DrawTrajectory(vector<Isometry3d, Eigen::aligned_allocator<Isometry3d>> poses)
{
    pangolin::CreateWindowAndBind("Trajectory Viewer",1024,7768);
    //启用或禁用OpenGL功能[https://docs.microsoft.com/en-us/windows/win32/opengl/glenable],[https://docs.microsoft.com/zh-cn/windows/win32/opengl/glblendfunc]
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
	//Define Projection and initial ModelView matrix
    pangolin::OpenGlRenderState s_cam(
            pangolin::ProjectionMatrix(1024, 768, 500, 500, 512, 389, 0.1, 1000),
            pangolin::ModelViewLookAt(0, -0.1, -1.8, 0, 0, 0, 0.0, -1.0, 0.0)
    );
    
    pangolin::View &d_cam = pangolin::CreateDisplay()
            .SetBounds(0.0, 1.0, 0.0, 1.0, -1024.0f / 768.0f)
            .SetHandler(new pangolin::Handler3D(s_cam));

    while (pangolin::ShouldQuit() == false) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        d_cam.Activate(s_cam);
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        glLineWidth(2);
        for (size_t i = 0; i < poses.size(); i++) {
            // 画每个位姿的三个坐标轴
            Vector3d Ow = poses[i].translation();
            Vector3d Xw = poses[i] * (0.1 * Vector3d(1, 0, 0));
            Vector3d Yw = poses[i] * (0.1 * Vector3d(0, 1, 0));
            Vector3d Zw = poses[i] * (0.1 * Vector3d(0, 0, 1));
            glBegin(GL_LINES);
            glColor3f(1.0, 0.0, 0.0);
            glVertex3d(Ow[0], Ow[1], Ow[2]);
            glVertex3d(Xw[0], Xw[1], Xw[2]);
            glColor3f(0.0, 1.0, 0.0);
            glVertex3d(Ow[0], Ow[1], Ow[2]);
            glVertex3d(Yw[0], Yw[1], Yw[2]);
            glColor3f(0.0, 0.0, 1.0);
            glVertex3d(Ow[0], Ow[1], Ow[2]);
            glVertex3d(Zw[0], Zw[1], Zw[2]);
            glEnd();
        }
        // 画出连线
        for (size_t i = 0; i < poses.size(); i++) {
            glColor3f(0.0, 0.0, 0.0);
            //直线
            glBegin(GL_LINES);
            auto p1 = poses[i], p2 = poses[i + 1];
            //两点一线
            glVertex3d(p1.translation()[0], p1.translation()[1], p1.translation()[2]);
            glVertex3d(p2.translation()[0], p2.translation()[1], p2.translation()[2]);
            glEnd();
        }
        pangolin::FinishFrame();
        usleep(5000);   // sleep 5 ms
    }
}
```

## ch4李群李代数

### 群

群是一种集合加上一种运算的代数结构，包括封闭性，结合律，幺元和逆。

### 李群

具有连续性质的群。一个刚体能够连续的空间运动，$SO(3),SE(3)$都是李群。

### 李代数

与李群对应的一种结构，位于向量空间。事实上是李群单位元处的正切空间。记为$so(3),se(3)$。

考虑旋转矩阵$R$，$R(t)R(t)^T=I$，两侧求导

$\Rightarrow \dot R(t)R(t)^T+R(t)\dot R(t)^T=0 $

$\Rightarrow \dot R(t)R(t)^T=-(\dot R(t) R(t)^T)^T$

$\dot R(t)R(t)^T$为一个反对称矩阵。记

$\dot R(t)R(t)^T=\phi(t)^{\wedge}$

$\Rightarrow \dot R(t)=\phi(t)^{\wedge}R(t)$

考虑单位元附近，有$t_0=0,R(0)=I$

$R(t)\approx R(t_0)+\dot R(t_0)(t-t_0)=I+\phi(t_0)^{\wedge}(t)$

### 实践

```c++
//SO3
Matrix3d R;
Quaterniond q(R);
Sophus::SO3d SO3_R(R);  // Sophus::SO3d可以直接从旋转矩阵构造
Sophus::SO3d SO3_q(q);  // 也可以通过四元数构造
// 使用对数映射获得它的李代数
Vector3d so3 = SO3_R.log();

// hat 为向量到反对称矩阵
cout << "so3 hat=\n" << Sophus::SO3d::hat(so3) << endl;
// 相对的，vee为反对称到向量
cout << "so3 hat vee= " << Sophus::SO3d::vee(Sophus::SO3d::hat(so3)).transpose() << endl;

// 增量扰动模型的更新
Vector3d update_so3; //假设更新量为这么多
Sophus::SO3d SO3_updated = Sophus::SO3d::exp(update_so3) * SO3_R;

//SE3
Vector3d t;
Sophus::SE3d SE3_Rt(R, t);           // 从R,t构造SE(3)
Sophus::SE3d SE3_qt(q, t);            // 从q,t构造SE(3)
```

```c++
//计算rmse
double rmse = 0;
for (size_t i = 0; i < estimated.size(); i++) {
  Sophus::SE3d p1 = estimated[i], p2 = groundtruth[i];
  double error = (p2.inverse() * p1).log().norm();
  rmse += error * error;
}
rmse = rmse / double(estimated.size());
rmse = sqrt(rmse);
cout << "RMSE = " << rmse << endl;
```











