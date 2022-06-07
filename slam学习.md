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
//#include<> 不需要
void print();//主要；
```

 .cpp文件中

```c++
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

使用库先在cmakelist中include directory



