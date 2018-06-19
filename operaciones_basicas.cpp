#include "cabecera.h"
//combinacion de imagenes
Mat image1;
Mat image2;


//sumar
//restar
//producto
//division
//mezcla de imagenes



int main(int argc, char const *argv[])
{
    string im1 = "/home/luis/Escritorio/Editor/labs/images/2.bmp";
    string im2 = "/home/luis/Escritorio/Editor/labs/images/objeto_seg.bmp";

    image1 = imread(im1.c_str());
    image2 = imread(im2.c_str());

    Mat dst;
    add(image1, image2, dst, noArray(), -1);
    namedWindow("suma", WINDOW_AUTOSIZE );
    imshow("suma", dst);
    imwrite("suma.bmp", dst);
    
    subtract(image1, image2, dst, noArray(), -1);
    namedWindow("resta", WINDOW_AUTOSIZE );
    imshow("resta", dst);
    imwrite("resta.bmp", dst);
    
    multiply(image1, image2, dst, 1.0f, -1);
    namedWindow("multiplicacion", WINDOW_AUTOSIZE );
    imshow("multiplicacion", dst);
    imwrite("multiplicacion.bmp", dst);
    
    divide(image1, image2, dst, 1.0f, -1);
    namedWindow("division", WINDOW_AUTOSIZE );
    imshow("division", dst);
    imwrite("division.bmp", dst);
    waitKey(0);
    cout<<"\nExito\n";
    return 0;
}

/*
g++ -ggdb main.cpp -o m `pkg-config --cflags --libs opencv`
./m
*/


