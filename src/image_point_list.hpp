//
// Created by kushn on 7/3/2022.
//

#ifndef SRC__IMAGE_POINT_LIST_HPP_
#define SRC__IMAGE_POINT_LIST_HPP_

#include <list>
#include "image_point.hpp"

class Image_point_list {
 public:
  std::list<Image_point *> points;
  ~Image_point_list();
  Image_point_list();
  void add(Image_point* point);
};

#endif //SRC__IMAGE_POINT_LIST_HPP_
