#include <iostream>
#include <string>
#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;


// void on_mouse(int event, int x, int y, int flags, void* param) {
//     if (event == cv::EVENT_LBUTTONDOWN) {
//         std::cout << "x: " << x << ", y: " << y << std::endl;
//     }
// }
int main()
{
    Mat src=imread("assets/src.jpg");//读取
    
    Mat grey,dst1,dst2,dst3,dst4,dst5,res,edges,x,image;//定义
    
    Mat element = getStructuringElement(MORPH_RECT, Size(30,30));//定义结构元素
    
    grey=imread("assets/src.jpg",0);//得到灰度图
    /*namedWindow("contours", WINDOW_NORMAL);//定义窗口*/
    // namedWindow("src", WINDOW_NORMAL);//定义窗口
    
    threshold(grey, dst1, 210, 255, THRESH_BINARY);//二值化
    // namedWindow("src1", WINDOW_NORMAL);
    // imshow("src1", dst1);
    medianBlur(dst1, dst2, 13);//中值滤波
    // namedWindow("src2", WINDOW_NORMAL);
    // imshow("src2", dst2);
    
    morphologyEx(dst2, dst4, MORPH_CLOSE, element,Point(-1,-1),4);//开运算
    // namedWindow("src3", WINDOW_NORMAL);
    // imshow("src3", dst4);

    Canny(dst4, edges, 50, 150);//边缘检测
    vector<vector<Point>> contours;
	vector<Vec4i> hierachy;
    findContours(dst4, contours, hierachy, RETR_TREE , CHAIN_APPROX_SIMPLE);

    vector<vector<Point>> contours1;
	vector<Vec4i> hierachy1;
    findContours(dst4, contours1, hierachy1, RETR_EXTERNAL , CHAIN_APPROX_SIMPLE);
    
    // vector<Point> contour;
    
    // for (int i = 0; i < contours.size(); i++)
    // {
    //     contour.insert(contour.end(), contours[i].begin(), contours[i].end());
    // }
    Point2f srcPoints[4];
    vector<Point> approxPoints;
    vector<Point> hull;
    for(int i = 0; i < contours.size(); i++) {
        
        approxPolyDP(contours[i], approxPoints,0.01*arcLength(contours[i], true), true);
        convexHull(approxPoints,hull,false,true);
        cout << "approxPoints.size():" << approxPoints.size() << endl;
        for (int i=0;i<hull.size();i++)
        {
            srcPoints[i].x=hull[i].x;
            srcPoints[i].y=hull[i].y;
        }

        //手写的类凸包检测
        // int max1,min1=approxPoints[0].x+approxPoints[0].y;
        // int max2,min2=approxPoints[0].x-approxPoints[0].y;
        // for (const auto& point : approxPoints) 
        // {
        //     max1=max1>point.x+point.y?max1:point.x+point.y;  
        //     min1=min1<point.x+point.y?min1:point.x+point.y; 
        //     max2=max2>point.x-point.y?max2:point.x-point.y;  
        //     min2=min2<point.x-point.y?min2:point.x-point.y;     
        // }   
        // for (const auto& point : approxPoints)
        // {
        //     if(point.x+point.y==max1)
        //     {
        //         srcPoints[3].x=point.x;
        //         srcPoints[3].y=point.y;
        //         cout    << "x: " << point.x << ", y: " << point.y << endl;
        //         circle(src, point, 5, Scalar(0, 0, 255), 2);
        //     }
        //     if(point.x+point.y==min1)
        //     {
        //         srcPoints[2].x=point.x;
        //         srcPoints[2].y=point.y;
        //         cout    << "x: " << point.x << ", y: " << point.y << endl;
        //         circle(src, point, 5, Scalar(0, 255, 0), 2);
        //     }
        //     if(point.x-point.y==max2)
        //     {
        //         srcPoints[1].x=point.x;
        //         srcPoints[1].y=point.y;
        //         cout    << "x: " << point.x << ", y: " << point.y << endl;
        //         circle(src, point, 5, Scalar(0, 0, 255), 2);
        //     }
        //     if(point.x-point.y==min2)
        //     {
        //         srcPoints[0].x=point.x;
        //         srcPoints[0].y=point.y;
        //         cout    << "x: " << point.x << ", y: " << point.y << endl;
        //         circle(src, point, 5, Scalar(0, 255, 0), 2);
        //     }
        // }
        // break;
    }

    
    // // std::cout << "Approximated Polygon Points:" << std::endl;
    
    // // drawContours(src, contours, -1, (0, 255, 255), 2);
    // // drawContours(src, contours1, -1, (0, 255, 255), 2);
    // imshow("src", src);
    // // namedWindow("Result", WINDOW_NORMAL);
    
    // //透视变换 
     
    // Point2f srcPoints[] = {Point2f(959.22, 1109.86), Point2f(1750.67, 1204.62), Point2f(2205.84, 2476.82), Point2f(1206.39, 2536.06)};
    Point2f dstPoints[] = {Point2f(900, 0), Point2f(900, 1700), Point2f(0, 1700), Point2f(0, 0)};
    Mat perspectiveMat = getPerspectiveTransform(srcPoints, dstPoints);
    warpPerspective(src, res, perspectiveMat, Size(900, 1700));
    namedWindow("Result", WINDOW_NORMAL);
    imshow("Result", res);
    waitKey(0);
    
    /*
    cv::namedWindow("image",WINDOW_NORMAL);
    cv::setMouseCallback("image", on_mouse);
    cv::imshow("image", src);
    cv::waitKey(0);
    cv::destroyAllWindows();
    /*
    x: 959, y: 1109
    x: 1206, y: 2536
    x: 2205, y: 2476
    x: 1750, y: 1204*/

    
    waitKey(0);
}
