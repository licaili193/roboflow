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

#include "DrawableWidget.hpp"

namespace roboflow
{
namespace gui
{
namespace drawing
{

DrawableWidget::DrawableWidget()
{
  viewport_x_ = viewport_y_ = 0;
  viewport_width_ = viewport_height_ = 0;

  is_draw_ = false;
}

void DrawableWidget::setDraw(bool draw)
{
  is_draw_ = draw;
}

void DrawableWidget::setViewport(double x, double y, double w, double h)
{
  viewport_x_ = x;
  viewport_y_ = y;
  viewport_width_ = w;
  viewport_height_ = h;
}

bool DrawableWidget::predraw(BLContext &ctx)
{
  if (!is_draw_ || viewport_width_ <= 0 || viewport_height_ <= 0)
    return false;
  ctx.save();
  ctx.translate(viewport_x_, viewport_y_);
  ctx.clipToRect(0, 0, viewport_width_, viewport_height_);
  return true;
}

void DrawableWidget::postdraw(BLContext &ctx)
{
  ctx.restore();
}

} // namespace drawing
} // namespace gui
} // namespace roboflow
