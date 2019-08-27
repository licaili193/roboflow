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

#ifndef __CANVASWIDGET__
#define __CANVASWIDGET__

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

class CanvasWidget final : public DrawableWidget
{
    double data_x_;
    double data_y_;
    double data_dx_;
    double data_dy_;

    // tempoary data
    // tempoary data

public:
    // temporary function to prepare the temporary data
    void init();

    // data range: x, y, dx, dy
    void setRange(double, double, double, double);

    void draw(BLContext &) override;
};

} // namespace drawing
} // namespace gui
} // namespace roboflow

#endif
