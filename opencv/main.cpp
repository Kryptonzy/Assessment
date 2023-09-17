#include <iostream>
#include <string>
#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;


void on_mouse(int event, int x, int y, int flags, void* param) {
    if (event == cv::EVENT_LBUTTONDOWN) {
        std::cout << "x: " << x << ", y: " << y << std::endl;
    }
}
int main()
{
    Mat src=imread("assets/src.jpg");//读取
    /*  失败的尝试
    Mat grey,dst1,dst2,dst3,dst4,dst5,res,edges,x,image;//定义
    
    Mat element = getStructuringElement(MORPH_RECT, Size(30,30));//定义结构元素
    
    grey=imread("src.jpg",0);//得到灰度图
    namedWindow("contours", WINDOW_NORMAL);//定义窗口
    namedWindow("src", WINDOW_NORMAL);//定义窗口
    
    threshold(grey, dst1, 210, 255, THRESH_BINARY);//二值化
    medianBlur(dst1, dst2, 11);//中值滤波

    morphologyEx(dst2, dst4, MORPH_CLOSE, element,Point(-1,-1),5);//开运算

    Canny(dst4, edges, 50, 150);//边缘检测
    vector<vector<Point>> contours;
    
	vector<Vec4i> hierachy;

    findContours(dst4, contours, hierachy, RETR_TREE , CHAIN_APPROX_SIMPLE);
    vector<Point> contour;
    
    for (int i = 0; i < contours.size(); i++)
    {
        contour.insert(contour.end(), contours[i].begin(), contours[i].end());
    }
    
    vector<Point> approxPoints;
    approxPolyDP(contours[0], approxPoints, 1, true);
    
    std::cout << "Approximated Polygon Points:" << std::endl;
    for (const auto& point : approxPoints) {
        std::cout << "(" << point.x << ", " << point.y << ")" << std::endl;
    }
    */
    namedWindow("Result", WINDOW_NORMAL);
    Mat res;
    //透视变换 

    Point2f srcPoints[] = {Point2f(959.22, 1109.86), Point2f(1750.67, 1204.62), Point2f(2205.84, 2476.82), Point2f(1206.39, 2536.06)};
    Point2f dstPoints[] = {Point2f(0, 0), Point2f(900, 0), Point2f(900, 1700), Point2f(0, 1700)};
    Mat perspectiveMat = getPerspectiveTransform(srcPoints, dstPoints);
    warpPerspective(src, res, perspectiveMat, Size(900, 1700));
    imshow("Result", res);

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

    //imshow("src", dst4);
    waitKey(0);
}
