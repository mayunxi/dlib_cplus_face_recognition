#include <QCoreApplication>
#include <QDebug>
#include "opencv2/opencv.hpp"
#include <iostream>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/objdetect/objdetect.hpp>

#include <stfz_facematch.h>
#include "stfz_facedetect.h"
/****
 *参考 https://github.com/davisking/dlib
 *
 * ***/
void testDetect()
{
    //初始化检测器，里面已经加载了detector.dat，model数据写在了代码里
    frontal_face_detector detector = get_frontal_face_detector();
    std::vector<cv::Rect> rec_vec;
    cv::Mat src = cv::imread("test.jpg");
    bool result = detect_face(detector,src,rec_vec);
    if (result)
    {
        for (auto rec:rec_vec)
        {
            cv::rectangle(src, rec, cv::Scalar(0, 0, 255), 1, 1, 0);
        }
        cv::imwrite("C_Dlib_test.jpg",src);
    }

}
void testMatch()
{
    //初始化检测器，里面已经加载了detector.dat，model数据写在了代码里
    frontal_face_detector detector = get_frontal_face_detector();
     //特征值计算初始化
    string modelPath = "models/dlib_face_recognition_resnet_model_v1.dat";
    anet_type matcher;
    try
    {
        deserialize(modelPath) >> matcher;
    }
    catch (serialization_error &e)                      //serialization_error是一个类
    {
        cout << "can't find recogintion model filed" << endl;
    }
    //标记人脸特征
    shape_predictor sp;
    deserialize("models/shape_predictor_68_face_landmarks.dat") >> sp;

    string path = "test.jpg";
    cv::Mat src_img = cv::imread(path);
    stfz_feature feature;
    bool ret = compute_feature(detector,matcher,sp,src_img,feature);
    //cout << feature << endl;

    string path2 = "test1.jpg";
    cv::Mat src_img2 = cv::imread(path2);
    stfz_feature feature2;
    ret = compute_feature(detector,matcher,sp,src_img2,feature2);
    float score = compare_feature(feature2,feature);
    qDebug("score=%.1f%",score);
}
//余弦相似度
float getMold(const stfz_feature& vec){   //求向量的模长
       int n = vec.size();
       float sum = 0.0;
       for (int i = 0; i<n; ++i)
           sum += vec(i,0) * vec(i,0);
       return sqrt(sum);
   }

float getSimilarity(const stfz_feature& lhs, const stfz_feature& rhs){
   int n = lhs.size();
   assert(n == rhs.size());
   float tmp = 0.0;  //内积
   for (int i = 0; i<n; ++i)
       tmp += lhs(i,0) * rhs(i,0);
   return tmp / (getMold(lhs)*getMold(rhs));
}
int main()
{
    testDetect();
    testMatch();
}

