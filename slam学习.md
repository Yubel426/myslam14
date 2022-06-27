#slam14讲

## ch2 

### cmkae学习

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

* 内积
* 外积 反对称符号

####3.1.2欧氏变换

* 旋转矩阵

​		SO(n)特殊正交群，R~12~表示坐标系2变换到坐标系1的旋转矩阵。

* 平移矩阵

​		t~12~表示2到1的向量。实际表示1到2原点间的向量。注意t~12~和t~21~之间并不是简单负号的关系。

#### 3.1.3齐次坐标

 增加一维。左上为旋转矩阵R,右上为平移矩阵t，左下0,右下为1,记为SE(n)。

### 3.2Eigen

换源

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



### 3.3旋转向量和欧拉角

#### 3.3.1旋转向量

使用一个向量表示旋转，旋转轴，旋转角。使用旋转向量和平移向量表示变换矩阵。

旋转矩阵R和旋转向量n关系。

#### 3.3.2欧拉角

ZYX旋转。[r,p,y]，roll ,pitch,yaw。

万向锁问题。用三个代数表示旋转都具有奇异性。

### 3.4四元数

### 实践

#### 显示运动轨迹

#####安装pangolin

安装依赖

```shell
sudo apt-get install libglew-dev
```

安装pangolin

```shell
git clone https://github.com/stevenlovegrove/Pangolin.git
mkdir build
cd build
cmake ..
make
sudo make install
ldconfig
```









