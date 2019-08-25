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

#include <blend2d.h>

#include "gui/drawing/AxisWidget.hpp"

int main(int argc, char *argv[])
{
    roboflow::gui::drawing::AxisWidget axis;
    axis.setViewport(0, 0, 480, 480);
    axis.setRange(-1, -1, 2, 2);
    axis.setDraw(true);

    BLImage img(480, 480, BL_FORMAT_PRGB32);

    // Attach a rendering context into `img`.
    BLContext ctx(img);

    // Clear the image.
    ctx.setFillStyle(BLRgba32(0xFFFFFFFF));
    ctx.fillAll();

    // Fill some path.
    axis.draw(ctx);

    // Detach the rendering context from `img`.
    ctx.end();

    // Let's use some built-in codecs provided by Blend2D.
    BLImageCodec codec;
    codec.findByName("BMP");
    img.writeToFile("canvas_test.bmp", codec);

    return 0;
}
