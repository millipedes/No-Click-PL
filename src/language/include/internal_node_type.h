#ifndef INT_NODE_TYPE_H
#define INT_NODE_TYPE_H

#include <stdlib.h>

typedef enum {
  IN_CANVAS_DECLARATION,
  IN_COLOR_DECLARATION,
  IN_STAR_NEWLINE_STMT,
  IN_STATEMENT,
  IN_SHAPE_ASSIGNMENT,
  IN_RECTANGLE_DECLARATION,
  IN_SHAPE,
  IN_POINT_DECLARATION,
  IN_PICK_NEWLINE_STMT,
  IN_ELLIPSE_DECLARATION,
  IN_TO_DECLARATION,
  IN_FROM_DECLARATION,
  IN_LINE_DECLARATION,
  IN_FOR_LOOP,
  IN_EXPRESSION,
  IN_EXPRESSION_ASSIGNMENT,
  IN_IF_STMT,
  IN_EXPRESSION_LIST,
  IN_HEIGHT_DECLARATION,
  IN_WIDTH_DECLARATION,
  IN_RECTANGLE_PARAMETERS,
  IN_ELLIPSE_PARAMETERS,
  IN_MAJOR_AXIS_DECLARATION,
  IN_MINOR_AXIS_DECLARATION,
  IN_THICKNESS_DECLARATION,
  IN_CANVAS_PARAMETERS,
} internal_node_type;

const char * internal_node_type_to_string(internal_node_type int_node_type);

#endif
