// Copyright (c) 2020 PaddlePaddle Authors. All Rights Reserved.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include <include/paddleocr.h>
using namespace std;
namespace PaddleOCR {
    bool use_gpu=false;
    bool use_tensorrt=false;
    int32_t gpu_id=0;
    int32_t gpu_mem=4000;
    int32_t cpu_threads= 10;
    bool enable_mkldnn= false;
    string precision= "fp32";
    bool benchmark= false;
    string output= "./output/";
    string image_dir= "";
    string type= "ocr";
    // detection related
    string det_model_dir= "D:/Cwork/AIAuxiliary/source/ch_PP-OCRv3_det_infer";
    string limit_type= "max";
    int32_t limit_side_len= 960;
    double det_db_thresh= 0.3;
    double det_db_box_thresh= 0.6;
    double det_db_unclip_ratio= 1.5;
    bool use_dilation= false;
    string det_db_score_mode= "slow";
    bool visualize= true;
    // recognition related
    string rec_model_dir= "D:/Cwork/AIAuxiliary/source/ch_PP-OCRv3_rec_infer";
    int32_t rec_batch_num= 6;
    string rec_char_dict_path= "D:/Cwork/AIAuxiliary/source/ppocr_keys_v1.txt";
    int32_t rec_img_h= 48;
    int32_t rec_img_w=320;
   
    // ocr forward related
    bool det=true;
    bool rec=true;

PPOCR::PPOCR() {
  if (true) {
    this->detector_ = new DBDetector(
        det_model_dir, use_gpu, gpu_id, gpu_mem,
        cpu_threads, enable_mkldnn, limit_type,
        limit_side_len, det_db_thresh, det_db_box_thresh,
        det_db_unclip_ratio, det_db_score_mode, use_dilation,
        use_tensorrt, precision);
  }
  if (true) {
    this->recognizer_ = new CRNNRecognizer(
        rec_model_dir, use_gpu, gpu_id, gpu_mem,
        cpu_threads, enable_mkldnn, rec_char_dict_path,
        use_tensorrt, precision, rec_batch_num,
        rec_img_h, rec_img_w);
  }
};

std::vector<std::vector<OCRPredictResult>>
PPOCR::ocr(std::vector<cv::Mat> img_list, bool det, bool rec, bool cls) {
  std::vector<std::vector<OCRPredictResult>> ocr_results;

  if (!det) {
    std::vector<OCRPredictResult> ocr_result;
    ocr_result.resize(img_list.size());
    if (rec) {
      this->rec(img_list, ocr_result);
    }
    for (int i = 0; i < ocr_result.size(); ++i) {
      std::vector<OCRPredictResult> ocr_result_tmp;
      ocr_result_tmp.push_back(ocr_result[i]);
      ocr_results.push_back(ocr_result_tmp);
    }
  } else {
    for (int i = 0; i < img_list.size(); ++i) {
      std::vector<OCRPredictResult> ocr_result =
          this->ocr(img_list[i], true, rec, cls);
      ocr_results.push_back(ocr_result);
    }
  }
  return ocr_results;
}

std::vector<OCRPredictResult> PPOCR::ocr(cv::Mat img, bool det, bool rec,
                                         bool cls) {

  std::vector<OCRPredictResult> ocr_result;
  // det
  this->det(img, ocr_result);
  // crop image
  std::vector<cv::Mat> img_list;
  for (int j = 0; j < ocr_result.size(); j++) {
    cv::Mat crop_img;
    crop_img = Utility::GetRotateCropImage(img, ocr_result[j].box);
    img_list.push_back(crop_img);
  }
  // rec
  if (rec) {
    this->rec(img_list, ocr_result);
  }
  return ocr_result;
}

void PPOCR::det(cv::Mat img, std::vector<OCRPredictResult> &ocr_results) {
  std::vector<std::vector<std::vector<int>>> boxes;
  std::vector<double> det_times;

  this->detector_->Run(img, boxes, det_times);

  for (int i = 0; i < boxes.size(); i++) {
    OCRPredictResult res;
    res.box = boxes[i];
    ocr_results.push_back(res);
  }
  // sort boex from top to bottom, from left to right
  Utility::sorted_boxes(ocr_results);
  this->time_info_det[0] += det_times[0];
  this->time_info_det[1] += det_times[1];
  this->time_info_det[2] += det_times[2];
}

void PPOCR::rec(std::vector<cv::Mat> img_list,
                std::vector<OCRPredictResult> &ocr_results) {
  std::vector<std::string> rec_texts(img_list.size(), "");
  std::vector<float> rec_text_scores(img_list.size(), 0);
  std::vector<double> rec_times;
  this->recognizer_->Run(img_list, rec_texts, rec_text_scores, rec_times);
  // output rec results
  for (int i = 0; i < rec_texts.size(); i++) {
    ocr_results[i].text = rec_texts[i];
    ocr_results[i].score = rec_text_scores[i];
  }
  this->time_info_rec[0] += rec_times[0];
  this->time_info_rec[1] += rec_times[1];
  this->time_info_rec[2] += rec_times[2];
}

void PPOCR::reset_timer() {
  this->time_info_det = {0, 0, 0};
  this->time_info_rec = {0, 0, 0};
  this->time_info_cls = {0, 0, 0};
}

PPOCR::~PPOCR() {
  if (this->detector_ != nullptr) {
    delete this->detector_;
  }
  if (this->recognizer_ != nullptr) {
    delete this->recognizer_;
  }
};

} // namespace PaddleOCR
