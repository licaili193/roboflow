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

#include <cmath>
#include <algorithm>

#include "navigation_function/common/math/Squircle.hpp"

#include "CanvasWidget.hpp"

namespace roboflow
{
namespace gui
{
namespace drawing
{

void CanvasWidget::setRange(double x, double y, double dx, double dy)
{
    data_x_ = x;
    data_y_ = y;
    data_dx_ = dx;
    data_dy_ = dy;
}

void CanvasWidget::draw(BLContext &ctx)
{
    if (predraw(ctx))
    {
        const double normal_stoke_width =
            std::max(data_dx_ / viewport_width_, data_dy_ / viewport_height_);

        ctx.translate(0, viewport_height_);
        ctx.scale(viewport_width_ / data_dx_,
                  -viewport_height_ / data_dy_);
        ctx.translate(-data_x_, -data_y_);
        // begin drawing

        ctx.setStrokeWidth(normal_stoke_width);
        ctx.setStrokeStyle(BLRgba32(0xFF000000));

        navigation_function::math::Squircle sq(0.5, 0.5, 0.99, 0.6, 0.2, 0.4);
        BLPath path;
        double r = 0;
        bool is_first = true;
        while (r < 2.0 * M_PI)
        {
            double lou = sq.getRadius(r);
            if (is_first)
            {
                path.moveTo(0.5 + std::cos(r) * lou, 0.5 + std::sin(r) * lou);
                is_first = false;
            }
            else
            {
                path.lineTo(0.5 + std::cos(r) * lou, 0.5 + std::sin(r) * lou);
            }
            r += M_PI / 90.0;
        }
        ctx.strokePath(path);

        // end drawing
        postdraw(ctx);
    }
}

} // namespace drawing
} // namespace gui
} // namespace roboflow
