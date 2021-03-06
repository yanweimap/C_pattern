#include "adapter.h"

static int convert_points_to_item(struct point * leftbottom, struct point * righttop, struct base_item * item){
  item->width = (righttop->x - leftbottom->x);
  item->high  = (righttop->y - leftbottom->y);

  return 0;
}

static float adapter_get_area(void *private_data,
                              struct point * leftbottom,
                              struct point * righttop){
  struct base_item item;
  convert_points_to_item(leftbottom, righttop, &item);
  return acquire_area(&item);
}

static void adapter_get_center_point(void *private_data,
                                     struct point *leftbottom,
                                     struct point *righttop,
                                     struct point *center){
  struct base_item item;
  convert_points_to_item(leftbottom, righttop, &item);
  acquire_center_point(&item, leftbottom, center);
}

static rectangle_operation_adapter adapter_ops = {
  .get_area = adapter_get_area,
  .get_center_point = adapter_get_center_point,
};

rectangle_info_adapter * rectangle_info_adapter_init(rectangle_info_adapter * info_adp,
                                                     struct point * leftbottom,
                                                     struct point * righttop){
  return (rectangle_info_adapter *) rectangle_info_init((struct rectangle_info *) info_adp,
                                                        leftbottom,
                                                        righttop);
}


rectangle_shape_adapter * rectangle_shape_adapter_init(rectangle_shape_adapter * adapterp,
                                                       rectangle_info_adapter * info){
  adapterp->ops = &adapter_ops;
  adapterp->info = info;
  adapterp->private_data = adapterp;
  return adapterp;
}

