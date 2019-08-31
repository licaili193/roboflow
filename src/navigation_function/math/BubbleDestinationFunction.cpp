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

#include "BubbleDestinationFunction.hpp"

namespace roboflow
{
namespace navigation_function
{
namespace math
{

BubbleDestinationFunction::BubbleDestinationFunction(Eigen::Vector2d dest, double r)
{
    setDestination(dest);
    setRadius(r);
}

BubbleDestinationFunction::BubbleDestinationFunction(double x, double y, double r)
{
    setDestination(x, y);
    setRadius(r);
}

void BubbleDestinationFunction::setDestination(Eigen::Vector2d dest)
{
    destination_ = std::move(dest);
}

void BubbleDestinationFunction::setDestination(double x, double y)
{
    setDestination({x, y});
}

void BubbleDestinationFunction::setRadius(double r)
{
    radius_ = r;
}

void BubbleDestinationFunction::offset(double dx, double dy)
{
    destination_(0) += dx;
    destination_(1) += dy;
}

double BubbleDestinationFunction::evaluate(Eigen::Vector2d p) const
{
    return std::pow((p - destination_).squaredNorm() - radius_ * radius_, 2.0);
}

Eigen::Vector2d BubbleDestinationFunction::getDestination() const
{
    return destination_;
}

double BubbleDestinationFunction::getDestX() const
{
    return destination_(0);
}

double BubbleDestinationFunction::getDestY() const
{
    return destination_(1);
}

double BubbleDestinationFunction::getRadius() const
{
    return radius_;
}

} // namespace math
} // namespace navigation_function
} // namespace roboflow
