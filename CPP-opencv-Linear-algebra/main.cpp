#include <opencv2/core/core.hpp>
//#include <opencv2/highgui/highgui.hpp>
//#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/ml/ml.hpp>

#include <iostream>
#include <cstdio>

#include <sys/timeb.h>
#if defined(WIN32)
    #define  TIMEB    _timeb
    #define  ftime    _ftime
    typedef __int64 TIME_T;
#else
    #define TIMEB timeb
    typedef long long TIME_T;
#endif

using namespace cv;
using namespace std;

void Pause()
{
    printf("Press Enter key to continue...");
    fgetc(stdin);
}
void addMatrix()
{
    float a[2][2] = {{1, 2},
                     {3, 4}};
    float b[2][2] = {{5, 6},
                     {7, 8}};

    Mat A = Mat(2, 2, CV_32FC1, a);
    Mat B = Mat(2, 2, CV_32FC1, b);
    Mat C;
    C = A + B;
    cout << "A =" << endl << " " << A << endl << endl;
    cout << "B =" << endl << " " << B << endl << endl;
    cout << "A+B =" << endl << " " << C << endl << endl;
}
void subMatrix()
{
    float a[2][2] = {{1, 2},
                     {3, 4}};
    float b[2][2] = {{5, 6},
                     {7, 8}};

    Mat A = Mat(2, 2, CV_32FC1, a);
    Mat B = Mat(2, 2, CV_32FC1, b);
    Mat C;
    C = A - B;
    cout << "A =" << endl << " " << A << endl << endl;
    cout << "B =" << endl << " " << B << endl << endl;
    cout << "A-B =" << endl << " " << C << endl << endl;
}

void matrixMultiplication(){
    float a[2][3] = {{ 3, 1, 2},
                     {-2, 0, 5}};
    float b[3][2] = {{-1, 3},
                     {0, 5},
                     {2,5}};

    Mat A = Mat(2, 3, CV_32FC1, a);
    Mat B = Mat(3, 2, CV_32FC1, b);
    cout << "A =" << endl << " " << A << endl << endl;
    cout << "B =" << endl << " " << B << endl << endl;

    Mat C;
    C = A * B;
    cout << "A * B=" << endl << " " << C << endl << endl;
    C = B * A;
    cout << "B * A=" << endl << " " << C << endl << endl;
}

void solveLinearEquation()
{
    // 3x + 2y = 7
    // -6x + 6y = 6
    float a[2][2] = {{ 3, 2},
                     {-6, 6}};

    float b[2][1] = { {7},
                      {6} };

    Mat A = Mat(2,2 ,CV_32FC1, a);
    Mat B = Mat(2,1, CV_32FC1, b);
    cout << "A =" << endl << " " << A << endl << endl;
    cout << "B =" << endl << " " << B << endl << endl;

    //X= B/A = A反矩陣*B
    Mat x = A.inv() * B;
    cout << "01.x=B/A" << endl << " " << x << endl;
    //-----------
    solve(A, B, x);//標準函數
    cout << "02.x=B/A" << endl << " " << x << endl;
}
void solveLinear_parabola()//拋物線(線性方程)求解
{
    cv::Point2f pt1, pt2, pt3; ///< 3 points for the parabola
    double a, b, c;            ///< Solved coefficients for the parabola equation

    //set here your 3 points for the parabola
    pt1 = cv::Point2f(1, 0);
    pt2 = cv::Point2f(0, 2);
    pt3 = cv::Point2f(3, 2);

    // OpenCV requires the linear system in the form Ax = B
    //
    // the linear system for 3points parabola is
    //
    // aX^2 + bX + c = Y ---> | a(pt1.x)^2 + b(pt1.x) + c(1) = pt1.y |
    //                        | a(pt2.x)^2 + b(pt2.x) + c(1) = pt2.y |
    //                        | a(pt3.x)^2 + b(pt3.x) + c(1) = pt3.y |
    // coefficients for the system are the 3 points
    // variables for the system are the parabola coefficient a,b,c
    //
    // Finally set the matrix for the linear system solver
    cv::Mat A = (cv::Mat_<float>(3, 3) <<
        std::pow(pt1.x, 2), pt1.x, 1,
        std::pow(pt2.x, 2), pt2.x, 1,
        std::pow(pt3.x, 2), pt3.x, 1);

    cv::Mat B = (cv::Mat_<float>(3, 1) <<
        pt1.y,
        pt2.y,
        pt3.y);

    // declare a vector for results
    cv::Mat abc;

    // solve the linear system
    cv::solve(A, B, abc);

    // printout the result
    cout << "Coefficients:\n " << abc << endl;
    a = abc.at<float>(0);
    b = abc.at<float>(1);
    c = abc.at<float>(2);
    cout << "Equation:\n y = " << a << "x^2 + " << b << "x + " << c << endl;
}
int main()
{
    addMatrix();
    cout << endl << "===================" << endl << endl;
    subMatrix();
    cout << endl << "===================" << endl << endl;
    matrixMultiplication();
    cout << endl << "===================" << endl << endl;
    solveLinearEquation();
    cout << endl << "===================" << endl << endl;
    solveLinear_parabola();//拋物線(線性方程)求解
    Pause();
    return 0;
}
