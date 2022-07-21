image_dir=../../images
for f in \
  square45-90_gray_kirsch_e_direction.bin \
  square45-90_gray_kirsch_e_direction.jpg \
  square45-90_gray_kirsch_ne_direction.bin \
  square45-90_gray_kirsch_ne_direction.jpg \
  square45-90_gray_kirsch_nw_direction.bin \
  square45-90_gray_kirsch_nw_direction.jpg \
  square45-90_gray_kirsch_s_direction.bin \
  square45-90_gray_kirsch_s_direction.jpg \
  square45-90_gray_kirsch_se_direction.bin \
  square45-90_gray_kirsch_se_direction.jpg \
  square45-90_gray_kirsch_sw_direction.bin \
  square45-90_gray_kirsch_sw_direction.jpg \
  square45-90_gray_kirsch_w_direction.bin \
  square45-90_gray_kirsch_w_direction.jpg 
do
  echo $image_dir/$f
  rm -f $image_dir/$f
done
