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

#include "NavigationFunctionDrawer.hpp"

#include "CanvasWidget.hpp"

namespace roboflow
{
namespace gui
{
namespace drawing
{

void CanvasWidget::setNavigationFunction(
    std::shared_ptr<navigation_function::NavigationFunction> nf)
{
    nf_ = nf;
}

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

        BLRect range(data_x_, data_y_, data_dx_, data_dy_);
        NavigationFunctionDrawer::drawNavigationFunction(
            nf_, range, ctx, normal_stoke_width);

        // end drawing
        postdraw(ctx);
    }
}

} // namespace drawing
} // namespace gui
} // namespace roboflow
