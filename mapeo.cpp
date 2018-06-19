#include <opencv2/core/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <string>


using namespace std;
using namespace cv;

int main(int argc, char* argv[])
{

    // Input Quadilateral or Image plane coordinates
    Point2f inputQuad[4]; 
    // Output Quadilateral or World plane coordinates
    Point2f outputQuad[4];
         
    // Lambda Matrix
    Mat lambda( 2, 4, CV_32FC1 );
    //Input and Output Image;
    Mat input, output;
     
    //Load the image
    input = imread( "lena24b.bmp", 1 );
    // Set the lambda matrix the same type and size as input
    lambda = Mat::zeros( input.rows, input.cols, input.type() );
 
    // The 4 points that select quadilateral on the input , from top-left in clockwise order
    // These four pts are the sides of the rect box used as input 
    inputQuad[0] = Point2f( -90,-60 );
    inputQuad[1] = Point2f( input.cols+200,-150);
    inputQuad[2] = Point2f( input.cols+100,input.rows+50);
    inputQuad[3] = Point2f( -50,input.rows+50  );  
    // The 4 points where the mapping is to be done , from top-left in clockwise order
    outputQuad[0] = Point2f( 0,0 );
    outputQuad[1] = Point2f( input.cols-1,0);
    outputQuad[2] = Point2f( input.cols-1,input.rows-1);
    outputQuad[3] = Point2f( 0,input.rows-1  );
 
    // Get the Perspective Transform Matrix i.e. lambda 
    lambda = getPerspectiveTransform( inputQuad, outputQuad );
    // Apply the Perspective Transform just found to the src image
    warpPerspective(input,output,lambda,output.size() );
 
    //Display input and output
    imshow("Input",input);
    imshow("Output",output);
 

    /*
    cv::Mat src = cv::imread(argv[1], 1);

    // After some magical procedure, these are points detect that represent 
    // the corners of the paper in the picture: 
    // [408, 69] [72, 2186] [1584, 2426] [1912, 291]
    vector<Point> not_a_rect_shape;
    not_a_rect_shape.push_back(Point(408, 69));
    not_a_rect_shape.push_back(Point(1912, 291));
    not_a_rect_shape.push_back(Point(72, 2186));
    not_a_rect_shape.push_back(Point(1584, 2426));

    // For debugging purposes, draw green lines connecting those points 
    // and save it on disk
    const Point* point = &not_a_rect_shape[0];
    int n = (int)not_a_rect_shape.size();
    Mat draw = src.clone();
    polylines(draw, &point, &n, 1, true, Scalar(0, 255, 0), 3, CV_AA);
    imwrite("draw.jpg", draw);

    // Assemble a rotated rectangle out of that info
    RotatedRect box = minAreaRect(cv::Mat(not_a_rect_shape));
    std::cout << "Rotated box set to (" << box.boundingRect().x << "," << box.boundingRect().y << ") " << box.size.width << "x" << box.size.height << std::endl;

    // Does the order of the points matter? I assume they do NOT.
    // But if it does, is there an easy way to identify and order 
    // them as topLeft, topRight, bottomRight, bottomLeft?
    cv::Point2f src_vertices[4];
    src_vertices[0] = not_a_rect_shape[0];
    src_vertices[1] = not_a_rect_shape[1];
    src_vertices[2] = not_a_rect_shape[2];
    src_vertices[3] = not_a_rect_shape[3];

    Point2f dst_vertices[4];
    dst_vertices[0] = Point(0, 0);
    dst_vertices[1] = Point(box.boundingRect().width-1, 0); // Bug was: had mistakenly switched these 2 parameters
    dst_vertices[2] = Point(0, box.boundingRect().height-1);
    dst_vertices[3] = Point(box.boundingRect().width-1, box.boundingRect().height-1);

    Mat warpMatrix = getPerspectiveTransform(src_vertices, dst_vertices);

    cv::Mat rotated;
    warpPerspective(src, rotated, warpMatrix, rotated.size(), INTER_LINEAR, BORDER_CONSTANT);

    imwrite("rotated.jpg", rotated);
    */

   
    waitKey();

    return 0;
}