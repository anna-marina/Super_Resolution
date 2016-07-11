#include <iostream>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>

using namespace std;
using namespace cv;

RNG rng;

void Add_salt_pepper_Noise(Mat &srcArr, float pa, float pb )

    {
    int amount1=srcArr.rows*srcArr.cols*pa;
    int amount2=srcArr.rows*srcArr.cols*pb;
    for(int counter=0; counter<amount1; ++counter)
        srcArr.at<uchar>(rng.uniform( 0,srcArr.rows), rng.uniform(0, srcArr.cols)) = 0;
    for (int counter=0; counter<amount2; ++counter)
        srcArr.at<uchar>(rng.uniform(0,srcArr.rows), rng.uniform(0,srcArr.cols)) = 255;
}

void Add_gaussian_Noise(Mat &srcArr,double mean,double sigma)
{
    Mat NoiseArr = srcArr.clone();
    RNG rng;
    rng.fill(NoiseArr, RNG::NORMAL, mean,sigma);

    add(srcArr, NoiseArr, srcArr);
}


int main(int argc, char *argv[])
{
    Mat srcArr;

    if (argc<=1)
        srcArr = imread("Lenna.png");

    else if (argc>=2)
        srcArr = imread(argv[1]);

    cvtColor(srcArr,srcArr, CV_RGB2GRAY,1);
    imshow("The original Image", srcArr);

    float sigma = 2.0, mean = 3.0, pa = 0.1, pb = 0.05;

    char name[20];

    Mat scaled;

    cv::resize(srcArr, scaled, cv::Size(), 0.5, 0.5);

    for (int i = 0; i < 100; i++) {
        Mat srcArr1 = scaled.clone();
        Mat srcArr2 = scaled.clone();
        Mat dstArr;

        printf("%d\n", i);

        sprintf(name, "res/blurred%d.png", i);

        Add_salt_pepper_Noise(srcArr1, pa,pb);
        //imshow("Add salt and pepper noise to image ", srcArr1);
        //imwrite("salt&pepper noise image.tif",srcArr1);

        medianBlur(srcArr1, dstArr, 3);
        imshow ("The effect after median filter",dstArr);
        imwrite(name, dstArr);

        Add_gaussian_Noise(srcArr2, mean, sigma);
        //imshow("Add gaussian noise to image", srcArr2);
        //imwrite("salt&pepper noise image.tif",srcArr2);
        
    
        //waitKey(0);
    }
    return 0;
}
