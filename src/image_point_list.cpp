//
// Created by kushn on 7/3/2022.
//

#include "image_point_list.hpp"

Image_point_list::~Image_point_list(){
  for (Image_point* point : points) {
    delete point;
  }
}

Image_point_list::Image_point_list() {

}

void Image_point_list::add(Image_point* point) {
  points.push_back(point);
}
