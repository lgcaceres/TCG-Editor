#include <opencv2/core/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <string>

using namespace std;
using namespace cv;



int main(int argc, char** argv )
{
    if ( argc != 2 )
    {
        printf("usage: Convoluciones <Image_Path>\n");
        return -1;
    }

    Mat src, dst;
    src = imread( argv[1], 1 );

    if ( !src.data )
    {
        printf("No image data \n");
        return -1;
    }
    
    namedWindow("Original", WINDOW_AUTOSIZE );
    imshow("Original", src);
    
    Mat kernel = (Mat_<char>(3,3)<<0,0,0,-1,1,0,0,0,0);
    //Mat kernel = (Mat_<char>(3,3)<<-1,-1,-1,-1,9,-1,-1,-1,-1);
    int kernelSize = 3;
    //kernel = Mat::ones(kernelSize, kernelSize, CV_32F) / (float)(kernelSize * kernelSize);
    cout << "kernel: \n" << kernel << endl;
    
    filter2D(src, dst, -1, kernel, Point(-1, -1), 0, BORDER_DEFAULT);
    
    namedWindow("dst3", WINDOW_AUTOSIZE );
    imshow("dst3", dst);
    imwrite("dst3.jpg", dst);
    
    
    waitKey(0);

    return 0;
}