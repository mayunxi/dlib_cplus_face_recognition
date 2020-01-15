#include "stfz_facedetect.h"

bool detect_face(frontal_face_detector &detector,string &path,std::vector<cv::Rect> &cv_rec_vec)
{
    matrix<rgb_pixel> src_img;
    load_image(src_img, path);
    std::vector<rectangle> dlib_rec_vec = detector(src_img);//检测人脸
    if (!dlib_rec_vec.empty())
    {
        for (auto rec:dlib_rec_vec)
        {
            cv::Rect box;
            box.x = rec.left();
            box.y = rec.top();
            box.width = rec.width();
            box.height = rec.height();
            cv_rec_vec.push_back(box);
        }
        return true;
    }
    else
    {
        return false;
    }
}
bool detect_face(frontal_face_detector &detector,cv::Mat &src_img,std::vector<cv::Rect> &cv_rec_vec)
{
    if (src_img.empty())
    {
        cout << "source image is null" << endl;
        return false;
    }
    matrix<rgb_pixel> des_img;
    dlib::assign_image(des_img, cv_image<rgb_pixel>(src_img));
    std::vector<rectangle> dlib_rec_vec = detector(des_img);//检测人脸
    if (!dlib_rec_vec.empty())
    {
        for (auto rec:dlib_rec_vec)
        {
            cv::Rect box;
            box.x = rec.left();
            box.y = rec.top();
            box.width = rec.width();
            box.height = rec.height();
            cv_rec_vec.push_back(box);
        }
        return true;
    }
    else
    {
        return false;
    }
}
