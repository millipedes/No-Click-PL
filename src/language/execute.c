/**
 * @file   execute.c
 * @brief  This file contains the execution functions for the language. Note
 * that this language is dynamically typed!
 * @author Matthew C. Lindeman
 * @date   July 10, 2023
 * @bug    None known
 * @todo   Nothing
 */
#include "include/execute.h"

void execute(ast head, symbol_table st) {
  switch(head->category) {
    case IN_CANVAS_DECLARATION:
      result canvas_result = execute_canvas_declaration(head->children[0],
          (result){0}, st);
      st = add_member(st, canvas_result.result, "CANVAS",
          canvas_result.result_type);
      execute(head->children[1], st);
      break;
    case IN_STAR_NEWLINE_STMT:
    case IN_PICK_NEWLINE_STMT:
      for(int i = 0; i < head->no_children; i++)
        execute(head->children[i], st);
      break;
    case IN_EXPRESSION_ASSIGNMENT:
      result expression_result = execute_expression(head->children[2],
          (result){0}, st);
      st = add_member(st, expression_result.result,
          head->children[0]->leaf->literal, expression_result.result_type);
      break;
    case IN_SHAPE_ASSIGNMENT:
      result shape_result = execute_shape_declaration(head->children[2],
          (result){0}, st);
      st = add_member(st, shape_result.result, head->children[0]->leaf->literal,
          shape_result.result_type);
      break;
    default:
      fprintf(stderr, "[EXECUTE]: (Main) Something went terribly worng\n");
      exit(1);
  }
}

result execute_canvas_declaration(ast head, result value, symbol_table st) {
  value.result_type = NCL_CANVAS;
  for(int i = 0; i < head->no_children; i++) {
    switch(head->children[i]->category) {
      case IN_WIDTH_DECLARATION:
        value.result.the_canvas.width
          = execute_expression(head->children[i]->children[0], (result){0}, st)
          .result.the_integer;
        break;
      case IN_HEIGHT_DECLARATION:
        value.result.the_canvas.height
          = execute_expression(head->children[i]->children[0], (result){0}, st)
          .result.the_integer;
        break;
      case IN_COLOR_DECLARATION:
        value.result.the_canvas.color
          = execute_color_declaration(head->children[i], (result){0}, st)
            .result.the_color;
        break;
      case IN_CANVAS_PARAMETERS:
        value = execute_canvas_declaration(head->children[i], value, st);
        break;
      case STRING:
        value.result.the_canvas = add_out_file_name(value.result.the_canvas,
            head->children[i]->leaf->literal);
        break;
      default:
        fprintf(stderr, "[EXECUTE_CANVAS_DECLARATION]: Something went "
            "terribly wrong\n");
        exit(1);
        break;
    }
  }
  return value;
}

result execute_shape_declaration(ast head, result value, symbol_table st) {
  switch(head->category) {
    case IN_RECTANGLE_DECLARATION:
       value = execute_rectangle_declaration(head->children[0],
             (result){0}, st);
      break;
    case IN_ELLIPSE_DECLARATION:
       value = execute_ellipse_declaration(head->children[0],
             (result){0}, st);
      break;
    case IN_POINT_DECLARATION:
       value = execute_point_declaration(head, (result){0}, st);
      break;
    case IN_COLOR_DECLARATION:
       value = execute_color_declaration(head, (result){0}, st);
      break;
    case IN_LINE_DECLARATION:
       value = execute_line_declaration(head, (result){0}, st);
      break;
    default:
      fprintf(stderr, "[EXECUTE]: (Shape) Something went terribly worng\n");
      exit(1);
  }
  return value;
}

result execute_rectangle_declaration(ast head, result value, symbol_table st) {
  value.result_type = NCL_RECTANGLE;
  for(int i = 0; i < head->no_children; i++) {
    switch(head->children[i]->category) {
      case IN_WIDTH_DECLARATION:
        value.result.the_rect.width
          = execute_expression(head->children[i]->children[0], (result){0}, st)
          .result.the_integer;
        break;
      case IN_HEIGHT_DECLARATION:
        value.result.the_rect.height
          = execute_expression(head->children[i]->children[0], (result){0}, st)
          .result.the_integer;
        break;
      case IN_THICKNESS_DECLARATION:
        value.result.the_rect.thickness
          = execute_expression(head->children[i]->children[0], (result){0}, st)
          .result.the_integer;
        break;
      case IN_COLOR_DECLARATION:
        value.result.the_rect.color
          = execute_color_declaration(head->children[i], (result){0}, st)
            .result.the_color;
        break;
      case IN_RECTANGLE_PARAMETERS:
        value = execute_rectangle_declaration(head->children[i], value, st);
        break;
      case IN_POINT_DECLARATION:
        value.result.the_rect.center
          = execute_point_declaration(head->children[i], (result){0}, st)
          .result.the_point;
        break;
      default:
        fprintf(stderr, "[EXECUTE_RECTANGLE_DECLARATION]: Something went "
            "terribly wrong\n");
        exit(1);
        break;
    }
  }
  return value;
}

result execute_ellipse_declaration(ast head, result value, symbol_table st) {
  value.result_type = NCL_ELLIPSE;
  for(int i = 0; i < head->no_children; i++) {
    switch(head->children[i]->category) {
      case IN_MAJOR_AXIS_DECLARATION:
        value.result.the_ellipse.major_axis
          = execute_expression(head->children[i]->children[0], (result){0}, st)
          .result.the_integer;
        break;
      case IN_MINOR_AXIS_DECLARATION:
        value.result.the_ellipse.minor_axis
          = execute_expression(head->children[i]->children[0], (result){0}, st)
          .result.the_integer;
        break;
      case IN_THICKNESS_DECLARATION:
        value.result.the_ellipse.thickness
          = execute_expression(head->children[i]->children[0], (result){0}, st)
          .result.the_integer;
        break;
      case IN_COLOR_DECLARATION:
        value.result.the_ellipse.color
          = execute_color_declaration(head->children[i], (result){0}, st)
            .result.the_color;
        break;
      case IN_ELLIPSE_PARAMETERS:
        value = execute_ellipse_declaration(head->children[i], value, st);
        break;
      case IN_POINT_DECLARATION:
        value.result.the_rect.center
          = execute_point_declaration(head->children[i], (result){0}, st)
          .result.the_point;
        break;
      default:
        fprintf(stderr, "[EXECUTE_ELLIPSE_DECLARATION]: Something went "
            "terribly wrong\n");
        exit(1);
        break;
    }
  }
  return value;
}

result execute_color_declaration(ast head, result value, symbol_table st) {
  value.result_type = NCL_COLOR;
  value.result.the_color = (pixel){
    execute_expression(head->children[0], (result){0}, st).result.the_integer,
    execute_expression(head->children[1], (result){0}, st).result.the_integer,
    execute_expression(head->children[2], (result){0}, st).result.the_integer,
  };
  return value;
}

result execute_point_declaration(ast head, result value, symbol_table st) {
  value.result_type = NCL_POINT;
  // TODO add ability for lang to process all of the other point style
  // characteristics
  value.result.the_point = (point){
    execute_expression(head->children[0], (result){0}, st).result.the_integer,
    execute_expression(head->children[1], (result){0}, st).result.the_integer,
    0,
    (pixel){0},
    1
  };
  return value;
}

result execute_line_declaration(ast head, result value, symbol_table st) {
  value.result_type = NCL_LINE;
  // TODO add ability for lang to process all of the other line style
  // characteristics
  // Add ability to do shape stuff here
  result to_shape = execute_shape_declaration(head->children[0]->children[0],
      (result){0}, st);
  result from_shape = execute_shape_declaration(head->children[1]->children[0],
      (result){0}, st);
  point to_point = {0};
  point from_point = {0};
  switch(to_shape.result_type) {
    case NCL_POINT:
      to_point = to_shape.result.the_point;
      break;
    default:
      fprintf(stderr, "[EXECUTE_LINE_DECLARATION]: Something went terribly "
          "wrong\nExiting\n");
      exit(1);
  }
  switch(from_shape.result_type) {
    case NCL_POINT:
      from_point = from_shape.result.the_point;
      break;
    default:
      fprintf(stderr, "[EXECUTE_LINE_DECLARATION]: Something went terribly "
          "wrong\nExiting\n");
      exit(1);
  }
  value.result.the_line = (line){
    to_point,
    from_point,
    0,
    (pixel){0},
    1
  };
  return value;
}

result execute_expression(ast head, result value, symbol_table st) {
  // TODO implement unary minus
  // TODO implement array semantics
  if(head) {
    if(!head->leaf) {
      result the_result = {0};
      for(int i = 0; i < head->no_children; i++) {
        switch(head->category) {
          case IN_EXPRESSION:
            result left = execute_expression(head->children[0], (result){0},
                st);
            result right = execute_expression(head->children[2], (result){0},
                st);
            switch(head->children[1]->leaf->category) {
              case PLUS:
                if(left.result_type == right.result_type) {
                  switch(left.result_type) {
                    case NCL_STRING:
                      fprintf(stderr, "[EXECUTE_EXPRESSION]: string not "
                          "implemented\n");
                      exit(1);
                    case NCL_DOUBLE:
                      the_result.result.the_double = left.result.the_double
                        + right.result.the_double;
                      the_result.result_type = NCL_DOUBLE;
                      return the_result;
                    case NCL_INTEGER:
                      the_result.result.the_integer = left.result.the_integer
                        + right.result.the_integer;
                      the_result.result_type = NCL_INTEGER;
                      return the_result;
                    default:
                      fprintf(stderr, "[EXECUTE_EXPRESSION]: %s addition not "
                          "supported, exiting\n",
                          ncl_type_to_string(left.result_type));
                      exit(1);
                  }
                } else if(IS_LEFT_UPCAST(left, right)) {
                  the_result.result_type = NCL_DOUBLE;
                  the_result.result.the_double =
                    (double)(left.result.the_integer) + right.result.the_double;
                  return the_result;
                } else if(IS_RIGHT_UPCAST(left, right)) {
                  the_result.result_type = NCL_DOUBLE;
                  the_result.result.the_double = left.result.the_double
                    + (double)(right.result.the_integer);
                  return the_result;
                }
                break;
              case MINUS:
                if(left.result_type == right.result_type) {
                  switch(left.result_type) {
                    case NCL_DOUBLE:
                      the_result.result.the_double = left.result.the_double
                        - right.result.the_double;
                      the_result.result_type = NCL_DOUBLE;
                      return the_result;
                    case NCL_INTEGER:
                      the_result.result.the_integer = left.result.the_integer
                        - right.result.the_integer;
                      the_result.result_type = NCL_INTEGER;
                      return the_result;
                    default:
                      fprintf(stderr, "[EXECUTE_EXPRESSION]: %s subtraction not"
                          " supported, exiting\n",
                          ncl_type_to_string(left.result_type));
                      exit(1);
                  }
                } else if(IS_LEFT_UPCAST(left, right)) {
                  the_result.result_type = NCL_DOUBLE;
                  the_result.result.the_double =
                    (double)(left.result.the_integer) - right.result.the_double;
                  return the_result;
                } else if(IS_RIGHT_UPCAST(left, right)) {
                  the_result.result_type = NCL_DOUBLE;
                  the_result.result.the_double = left.result.the_double
                    - (double)(right.result.the_integer);
                  return the_result;
                }
                break;
              case STAR:
                if(left.result_type == right.result_type) {
                  switch(left.result_type) {
                    case NCL_DOUBLE:
                      the_result.result.the_double = left.result.the_double
                        * right.result.the_double;
                      the_result.result_type = NCL_DOUBLE;
                      return the_result;
                    case NCL_INTEGER:
                      the_result.result.the_integer = left.result.the_integer
                        * right.result.the_integer;
                      the_result.result_type = NCL_INTEGER;
                      return the_result;
                    default:
                      fprintf(stderr, "[EXECUTE_EXPRESSION]: %s multiplication "
                          "not supported, exiting\n",
                          ncl_type_to_string(left.result_type));
                      exit(1);
                  }
                } else if(IS_LEFT_UPCAST(left, right)) {
                  the_result.result_type = NCL_DOUBLE;
                  the_result.result.the_double =
                    (double)(left.result.the_integer) * right.result.the_double;
                  return the_result;
                } else if(IS_RIGHT_UPCAST(left, right)) {
                  the_result.result_type = NCL_DOUBLE;
                  the_result.result.the_double = left.result.the_double
                    * (double)(right.result.the_integer);
                  return the_result;
                }
                break;
              case SLASH:
                if(left.result_type == right.result_type) {
                  switch(left.result_type) {
                    case NCL_DOUBLE:
                      the_result.result.the_double = left.result.the_double
                        / right.result.the_double;
                      the_result.result_type = NCL_DOUBLE;
                      return the_result;
                    case NCL_INTEGER:
                      the_result.result.the_integer = left.result.the_integer
                        / right.result.the_integer;
                      the_result.result_type = NCL_INTEGER;
                      return the_result;
                    default:
                      fprintf(stderr, "[EXECUTE_EXPRESSION]: %s division not "
                          "supported, exiting\n",
                          ncl_type_to_string(left.result_type));
                      exit(1);
                  }
                } else if(IS_LEFT_UPCAST(left, right)) {
                  the_result.result_type = NCL_DOUBLE;
                  the_result.result.the_double =
                    (double)(left.result.the_integer) / right.result.the_double;
                  return the_result;
                } else if(IS_RIGHT_UPCAST(left, right)) {
                  the_result.result_type = NCL_DOUBLE;
                  the_result.result.the_double = left.result.the_double
                    / (double)(right.result.the_integer);
                  return the_result;
                }
                break;
              case PERCENT:
                if(left.result_type == right.result_type) {
                  switch(left.result_type) {
                    case NCL_INTEGER:
                      the_result.result.the_integer = left.result.the_integer
                        % right.result.the_integer;
                      the_result.result_type = NCL_INTEGER;
                      return the_result;
                    default:
                      fprintf(stderr, "[EXECUTE_EXPRESSION]: %s modulus not "
                          "supported, exiting\n",
                          ncl_type_to_string(left.result_type));
                      exit(1);
                  }
                }
                break;
            }
            break;
          case IN_EXPRESSION_LIST:
            fprintf(stderr, "Not implemented yet\n");
            exit(1);
            break;
          default:
            fprintf(stderr, "[EXECUTE_EXPRESSION]: Something went terribly "
                "wrong\n");
            exit(1);
        }
      }
    } else if(head->leaf) {
      size_t literal_len = 0;
      switch(head->leaf->category) {
        case INTEGER:
          value.result_type = NCL_INTEGER;
          value.result.the_integer = atoi(head->leaf->literal);
          return value;
        case DOUBLE:
          value.result_type = NCL_DOUBLE;
          value.result.the_double = atof(head->leaf->literal);
          return value;
        case TRUE:
          value.result_type = NCL_BOOL;
          value.result.the_bool = 1;
          return value;
        case FALSE:
          value.result_type = NCL_BOOL;
          value.result.the_bool = 0;
          return value;
        case NAME:
          return find_symbol(st, head->leaf->literal);
        case STRING:
          value.result_type = NCL_STRING;
          literal_len = strnlen(head->leaf->literal, MAX_NAME);
          value.result.the_string = calloc(literal_len + 1, sizeof(char));
          strncpy(value.result.the_string, head->leaf->literal,
              literal_len);
          return value;
        default:
          fprintf(stderr, "[EXECUTE_EXPRESSION]: Something went terribly wrong"
              "\n");
          exit(1);
      }
    } else {
      fprintf(stderr, "[EXECUTE_EXPRESSION]: Something went terribly wrong\n");
      exit(1);
    }
  }
  fprintf(stderr, "[EXECUTE_EXPRESSION]: Something went terribly wrong\n");
  exit(1);
}
