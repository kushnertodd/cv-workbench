//
// Created by kushn on 7/3/2022.
//

#include "image_point_list.hpp"

Image_point_list::~Image_point_list(){
  for (Point* point : points) {
    delete point;
  }
}

Image_point_list::Image_point_list() {

}

void Image_point_list::add(Point* point) {
  points.push_back(point);
}
