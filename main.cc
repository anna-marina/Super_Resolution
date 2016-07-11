#include <opencv2/opencv.hpp>
#include <opencv2/superres.hpp>
#include <stdio.h>

using namespace cv;
using namespace cv::superres;

const 
    int k = 100;

class InterFrameSource : public superres::FrameSource
{
    std::vector<cv::Mat> frames;
    std::vector<cv::Mat>::iterator iter;

    public:
    InterFrameSource() {
        char name[20];
        for (int i = 0; i < k; i++) {
            sprintf(name, "res/blurred%d.png", i);
            frames.push_back(imread(name));
        }
        reset();
    }

    virtual void nextFrame(OutputArray _frame) {
        if (iter == frames.end()) return;

        iter->copyTo(_frame);
        ++iter;
    }

    virtual void reset() {
        iter = frames.begin();
    }
};



int main()
{
    InterFrameSource fsource;
    
    
    Ptr<SuperResolution> superResolution = createSuperResolution_BTVL1();
    superResolution->setInput(&fsource);
    superResolution->setScale(2);
    superResolution->setTemporalAreaRadius(2);
    superResolution->setIterations(100);

    Mat frame;

    for (int i = 0; i < k; i++) {
        superResolution->nextFrame(frame);
        printf("%d\n", i);
        imshow("Super Resolution", frame);
        imwrite("res/result.png", frame);
        waitKey(0);
    }
}
