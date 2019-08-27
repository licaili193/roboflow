// The MIT License (MIT)

// Copyright (c) 2019 Caili Li

//  Permission is hereby granted, free of charge, to any person obtaining a
//  copy of this software and associated documentation files (the "Software"),
//  to deal in the Software without restriction, including without limitation
//  the rights to use, copy, modify, merge, publish, distribute, sublicense,
//  and/or sell copies of the Software, and to permit persons to whom the
//  Software is furnished to do so, subject to the following conditions:
//
//  The above copyright notice and this permission notice shall be included in
//  all copies or substantial portions of the Software.
//
//  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
//  OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
//  FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
//  DEALINGS IN THE SOFTWARE.

/* code */

#ifndef __AXISWIDGET__
#define __AXISWIDGET__

#include <string>
#include <vector>
#include <utility>

#include <blend2d.h>

#include "DrawableWidget.hpp"

namespace roboflow
{
namespace gui
{
namespace drawing
{

class AxisWidget final : public DrawableWidget
{
  double data_x_;
  double data_y_;
  double data_dx_;
  double data_dy_;

  double canvas_data_x_;
  double canvas_data_y_;
  double canvas_data_width_;
  double canvas_data_height_;

  // parameters
  bool is_draw_colormap_ = false;
  double margin_ = 5.0;
  double frame_width_ = 1.0;
  double tick_length_ = 5.0;
  double font_size_ = 12.0;
  double colormap_width_ = 100.0;
  uint32_t front_color_ = 0x00000000;

  // font
  BLFont font_;
  BLFontFace face_;

  // data ticks
  std::vector<double> x_ticks_;
  std::vector<double> y_ticks_;
  std::vector<std::string> x_tick_labels_;
  std::vector<std::string> y_tick_labels_;

  double max_y_label_width_;
  double text_height_;

  // cached canvas dimension
  double icx_;
  double icy_;
  double icw_;
  double ich_;

  // data range: max, min, step number
  std::vector<double> get_ticks_helper(double, double, int);
  void get_ticks();
  void get_cached_canvas_dimension();

  void generate_font();

public:
  AxisWidget();

  // data range: x, y, dx, dy
  void setRange(double, double, double, double);
  void setDrawColormap(bool);

  void draw(BLContext &) override;
  void setViewport(double, double, double, double) override;

  // return inner canvas data range: x, y, dx, dy
  BLRect getInnerCanvasRange() const;
  // return inner canvas dimension: x, y, w, h
  BLRect getInnerCanvasRect() const;
  BLRect getColorMapRect() const;
};

} // namespace drawing
} // namespace gui
} // namespace roboflow

#endif
