#ifndef STFZ_FACEDETECT_H
#define STFZ_FACEDETECT_H
#include <dlib/image_processing/frontal_face_detector.h>
#include <dlib/image_processing/render_face_detections.h>
#include <dlib/opencv.h>
#include <dlib/dnn.h>
#include <dlib/gui_widgets.h>
#include <dlib/clustering.h>
#include <dlib/string.h>
#include <dlib/image_io.h>

#include <iostream>

using namespace dlib;
using namespace std;

/*
 * 参数：detector人脸检测句柄，path/src_img：图片路径/图片的Mat，cv_rec_vec：检测到人脸的位置向量
 * 返回：true检测到人脸，false无人脸
*/
extern bool detect_face(frontal_face_detector &detector,string &path,std::vector<cv::Rect> &cv_rec_vec);
extern bool detect_face(frontal_face_detector &detector,cv::Mat &src_img,std::vector<cv::Rect> &cv_rec_vec);
#endif // STFZ_FACEDETECT_H
