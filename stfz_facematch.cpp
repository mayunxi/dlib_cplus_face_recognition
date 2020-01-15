#include <stfz_facematch.h>

bool DetectMax(matrix<rgb_pixel> &img,frontal_face_detector &detector,rectangle &rec)
{
    cv::Rect R;


    std::vector<rectangle> dets = detector(img);//检测人脸

    //查找最大脸
    if (dets.size() != 0)
    {
        int Max = 0;
        int area = 0;
        for (unsigned long t = 0; t < dets.size(); ++t)
        {
            if (area < dets[t].width()*dets[t].height())
            {
                area = dets[t].width()*dets[t].height();
                Max = t;
            }
        }
        rec = dets[Max];
        R.x = dets[Max].left();
        R.y = dets[Max].top();
        R.width = dets[Max].width();
        R.height = dets[Max].height();
        //cout<<"("<<R.x<<","<<R.y<<","<<R.width<<","<<R.height<<")"<<endl;
    }
    else
    {
        return false;
    }
    return true;
}
bool compute_feature(frontal_face_detector &detector,anet_type &net,shape_predictor &sp,cv::Mat src_img,stfz_feature &feature)
{
    if (src_img.empty())
    {
        cout << "source image is null" << endl;
        return false;
    }
    matrix<rgb_pixel> des_img;
    dlib::assign_image(des_img, cv_image<rgb_pixel>(src_img));

    //detect the face from mat
    std::vector<rectangle> dlib_rec_vec = detector(des_img);
    if (dlib_rec_vec.empty())
    {
        cout << "no face is detected" << endl;
        return false;
    }
    //marking feature points of face
    auto shape = sp(des_img, dlib_rec_vec[0]);

    std::vector<matrix<rgb_pixel>> faces;
    matrix<rgb_pixel> face_chip;
    extract_image_chip(des_img, get_face_chip_details(shape,150,0.25), face_chip);
    faces.push_back(move(face_chip));

    std::vector<matrix<float, 0, 1>> face_descriptors = net(faces);   //特征值
    feature = face_descriptors[0];
    return true;
}
float compare_feature(stfz_feature &feature1,stfz_feature &feature2)
{
    if ((feature1.size() == 0) || (feature2.size() == 0))
    {
        cout << "feature is null" << endl;
        return 0;
    }
    float f = length(feature2 - feature1);
    cout << "f:" << f << endl;
    float score = (1.0 / (1.0 + f)) * 100;
    return score;
}
