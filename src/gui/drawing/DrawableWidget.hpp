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

#ifndef __DRAWABLEWIDGET__
#define __DRAWABLEWIDGET__

#include <blend2d.h>

namespace roboflow
{
namespace gui
{
namespace drawing
{

class DrawableWidget
{
protected:
  double viewport_x_;
  double viewport_y_;
  double viewport_width_;
  double viewport_height_;

  bool is_draw_;

  // if predraw returns false, postdraw should net be called
  virtual bool predraw(BLContext &);
  virtual void postdraw(BLContext &);

public:
  DrawableWidget();

  // starting at the top left corner
  // x, y, width, height
  virtual void setViewport(double, double, double, double);
  void setDraw(bool);

  virtual void draw(BLContext &) = 0;
};

} // namespace drawing
} // namespace gui
} // namespace roboflow

#endif
