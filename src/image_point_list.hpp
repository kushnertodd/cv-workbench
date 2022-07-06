//
// Created by kushn on 7/3/2022.
//

#ifndef SRC__POINT_LIST_HPP_
#define SRC__POINT_LIST_HPP_

#include <list>
#include "point.hpp"

class Image_point_list {
 public:
  std::list<Point *> points;
  ~Image_point_list();
  Image_point_list();
  void add(Point* point);
};

#endif //SRC__POINT_LIST_HPP_
