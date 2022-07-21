#include <iostream>
#include "chrono"
using namespace std;

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

int main() {
    //读取图像
    string path = "/home/mao/slam/myslam14/ch5/imageBasics/ubuntu.png";
    cv::Mat image;
    image = cv::imread(path);
    if(image.data==nullptr)
    {
        cerr<<"不存在"<<endl;
        return 0;
    }
    //输出宽高通道数
    //cout<<image.cols<<image.rows<<image.channels()<<endl;

    //view
   // cv::imshow("image",image);
   // cv::waitKey(0);

    //遍历 使用chrono记时
   // chrono::steady_clock::time_point t1 = chrono::steady_clock::now();
/*
    for(size_t y =0;y<image.rows;y++)
    {

        unsigned char *row_ptr = image.ptr<unsigned char>(y);
        for(size_t x =0;x<image.cols;x++)
        {
            unsigned char *data_ptr = &row_ptr[x*image.channels()];
            for(int c =0;c<image.channels();c++)
                unsigned char data = data_ptr[c];
        }
    }

    chrono::steady_clock::time_point t2 = chrono::steady_clock::now();
    chrono::duration<double> time_used = chrono::duration_cast < chrono::duration < double >> (t2 - t1);
    cout << "遍历图像用时：" << time_used.count() << " 秒。" << endl;
*/
//test
    unsigned char *row_ptr = image.ptr<unsigned char>(2);  // row_ptr是第y行的头指针
    for (size_t x = 0; x < image.cols; x++) {
        // 访问位于 x,y 处的像素
        unsigned char *data_ptr = &row_ptr[x * image.channels()]; // data_ptr 指向待访问的像素数据
        // 输出该像素的每个通道,如果是灰度图就只有一个通道
        for (int c = 0; c != image.channels(); c++) {
            cout<<data_ptr[c]<<endl; // data为I(x,y)第c个通道的值
        }
    }






    return 0;
}
