
#ifndef CABECERA
#define CABECERA
// Zona de código
#include <opencv2/core/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <string>

using namespace std;
using namespace cv;


void histograma(Mat& src){
    //Mat src;
    //src = imread( archivo.c_str(), 1 );

    if ( !src.data )
    {
        printf("No image data \n");
        return ;
    }
    
    vector<Mat> bgr_planes;
    split(src, bgr_planes);
    
    int histSize = 256;
    float range[] = {0, 256};
    const float* histRange = {range};
    
    bool uniform = true, accumulate = false;
    Mat b_hist, g_hist, r_hist;
    
    // Calculamos histogramas
    // imagen, nimages, channels, mask, hist, dims, size, ranges...
    calcHist(&bgr_planes[0], 1, 0, Mat(), b_hist, 1, &histSize, &histRange, uniform, accumulate);
    calcHist(&bgr_planes[1], 1, 0, Mat(), g_hist, 1, &histSize, &histRange, uniform, accumulate);
    calcHist(&bgr_planes[2], 1, 0, Mat(), r_hist, 1, &histSize, &histRange, uniform, accumulate);
    
    int hist_w = 512;
    int hist_h = 400;
    Mat histImg(hist_h, hist_w, CV_8UC3, Scalar(255, 255, 255));
    
    // normalizar
    normalize(b_hist, b_hist, 0, histImg.rows, NORM_MINMAX, -1, Mat());
    normalize(g_hist, g_hist, 0, histImg.rows, NORM_MINMAX, -1, Mat());
    normalize(r_hist, r_hist, 0, histImg.rows, NORM_MINMAX, -1, Mat());
    
    int step = cvRound((double)hist_w / histSize);
    
    for (int i = 1; i < histSize; i++)
    {
        line(histImg, Point(step * (i -1), hist_h - cvRound(b_hist.at<float>(i - 1))),
                    Point(step * i, hist_h - cvRound(b_hist.at<float>(i))),
                    Scalar(255, 0, 0), 2, 8, 0);
        line(histImg, Point(step * (i -1), hist_h - cvRound(g_hist.at<float>(i - 1))),
                    Point(step * i, hist_h - cvRound(g_hist.at<float>(i))),
                    Scalar(0, 255, 0), 2, 8, 0);
        line(histImg, Point(step * (i -1), hist_h - cvRound(r_hist.at<float>(i - 1))),
                    Point(step * i, hist_h - cvRound(r_hist.at<float>(i))),
                    Scalar(0, 0, 255), 2, 8, 0);
    }

    namedWindow("Original", WINDOW_AUTOSIZE );
    imshow("Original", src);
    
    namedWindow("Histograma", WINDOW_AUTOSIZE );
    imshow("Histograma", histImg);
    
    imwrite("histograma.png", histImg);

    waitKey(0);
}
void operacionAritmetica(Mat& imagen , int val,  char ope){
     if ( !imagen.data )
    {
        printf("No image data \n");
        return ;
    }
    int f = imagen.rows;
    int c = imagen.cols;
    cout<<"\nfila: "<<f<<"\ncol: "<<c<<endl;
    Vec3b* imgrow;
    if(ope =='+'){
        for(int i = 0; i< f; i++){
            imgrow= imagen.ptr<Vec3b>(i);
            for(int j = 0; j < c ; j++){
                imgrow[j][0] = (imgrow[j][0] + val);
                imgrow[j][1] = (imgrow[j][1] + val);
                imgrow[j][2] = (imgrow[j][2] + val);
            
            }
        }
    }
    else if(ope =='-'){
        for(int i = 0; i< f; i++){
            imgrow= imagen.ptr<Vec3b>(i);
            for(int j = 0; j < c ; j++){
                imgrow[j][0] = abs(imgrow[j][0] - val);
                imgrow[j][1] = abs(imgrow[j][1] - val);
                imgrow[j][2] = abs(imgrow[j][2] - val);
            }
        }
    }
    else if(ope =='*'){
        for(int i = 0; i< f; i++){
            imgrow= imagen.ptr<Vec3b>(i);
            for(int j = 0; j < c ; j++){
                imgrow[j][0] = (imgrow[j][0] * val);
                imgrow[j][1] = (imgrow[j][1] * val);
                imgrow[j][2] = (imgrow[j][2] * val);
            }
        }
    }
    else{
        cout<<"\nOperacion no definida\n";
        return;
    }
    cout<<"terminado";
    //namedWindow("OperacionAritmetica", WINDOW_AUTOSIZE );
    imshow("Operacion", imagen);
    waitKey(0);

}

























#endif
