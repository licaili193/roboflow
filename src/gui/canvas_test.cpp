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

#include <memory>

#include <blend2d.h>

#include "gui/drawing/AxisWidget.hpp"
#include "gui/drawing/CanvasWidget.hpp"
#include "gui/drawing/NavigationFunctionDrawer.hpp"
#include "navigation_function/SphereWorldNavigationFunction.hpp"
#include "navigation_function/math/Sphere.hpp"
#include "navigation_function/math/BubbleDestinationFunction.hpp"

int main(int argc, char *argv[])
{
    roboflow::gui::drawing::AxisWidget axis;
    axis.setViewport(0, 0, 720, 720);
    axis.setRange(-11, -11, 22, 22);
    axis.setDraw(true);

    roboflow::gui::drawing::CanvasWidget canvas;
    auto canvas_rect = axis.getInnerCanvasRect();
    auto canvas_range = axis.getInnerCanvasRange();
    canvas.setViewport(canvas_rect.x, canvas_rect.y,
                       canvas_rect.w, canvas_rect.h);
    canvas.setRange(canvas_range.x, canvas_range.y,
                    canvas_range.w, canvas_range.h);
    canvas.setDraw(true);

    using roboflow::navigation_function::DestinationFunctionType;
    using roboflow::navigation_function::SphereWorldNavigationFunction;
    using roboflow::navigation_function::math::BubbleDestinationFunction;
    using roboflow::navigation_function::math::Sphere;

    auto dest = std::make_shared<BubbleDestinationFunction>(0, 0, 2);
    auto obj_0 = std::make_shared<Sphere>(0, 0, 10);
    double lct = 0;
    auto obj_1 = std::make_shared<Sphere>(5 * std::cos(M_PI / 3.0 * lct),
                                          5 * std::sin(M_PI / 3.0 * lct), 1);
    auto nf = std::make_shared<SphereWorldNavigationFunction>();
    nf->setDestination(dest, DestinationFunctionType::DestSphere);
    nf->setZerothObstacle(obj_0);
    nf->setObstacle(obj_1);
    nf->setKappa(1.28);

    canvas.setNavigationFunction(nf);

    BLImage img(720, 720, BL_FORMAT_PRGB32);

    // Attach a rendering context into `img`.
    BLContext ctx(img);

    // Clear the image.
    ctx.setFillStyle(BLRgba32(0xFFFFFFFF));
    ctx.fillAll();

    // Fill some path.
    axis.draw(ctx);
    canvas.draw(ctx);

    // Detach the rendering context from `img`.
    ctx.end();

    // Let's use some built-in codecs provided by Blend2D.
    BLImageCodec codec;
    codec.findByName("BMP");
    img.writeToFile("canvas_test.bmp", codec);

    return 0;
}
