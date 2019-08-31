// The MIT License (MIT)

// Copyright (c) 2019 Caili LI

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

#ifndef __SPHERE__
#define __SPHERE__

#include <vector>

#include <Eigen/Core>

#include "ScalarObject.hpp"
#include "StarObject.hpp"

namespace roboflow
{
namespace navigation_function
{
namespace math
{

class Sphere final : public ScalarObject, public StarObject
{
    Eigen::Vector2d center_;
    double radius_;

public:
    // center location, radius
    Sphere(Eigen::Vector2d, double);
    // center location: x, y, radius: r
    Sphere(double, double, double);

    // center location
    void setCenter(Eigen::Vector2d);
    // center location: x, y
    void setCenter(double, double);
    // radius: r
    void setRadius(double);

    double evaluate(Eigen::Vector2d) const override;
    double getRadius(Eigen::Vector2d) const override;
    double getRadius(double) const override;
    Eigen::Vector2d getCenter() const override;
};

} // namespace math
} // namespace navigation_function
} // namespace roboflow

#endif
