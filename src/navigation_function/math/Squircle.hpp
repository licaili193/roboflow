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

#include <vector>

#include <Eigen/Core>

#include "ScalarObject.hpp"
#include "StarObject.hpp"
#include "Transform.hpp"

namespace roboflow
{
namespace navigation_function
{
namespace math
{

class Squircle final : public ScalarObject, public StarObject
{
    Eigen::Vector2d center_;
    double s_;
    double rotate_;
    Eigen::Vector2d scale_;

    // cached transform
    Transform transform_;
    bool is_init_;

    void set_cached_transform();

public:
    // center location, squareness, rotation, scale factor
    Squircle(Eigen::Vector2d, double, double, Eigen::Vector2d);
    // center location: x, y, squareness: s, rotation r,scale: sx, sy
    Squircle(double, double, double, double, double, double);

    // center location
    void setCenter(Eigen::Vector2d);
    // center location: x, y
    void setCenter(double, double);
    // squareness: s
    void setSquareness(double);
    // rotation: angle
    void setRotation(double);
    // scale factor
    void setScale(Eigen::Vector2d);
    // scale factor: sx, sy
    void setScale(double, double);

    double evaluate(Eigen::Vector2d) const override;
    double getRadius(Eigen::Vector2d) const override;
    double getRadius(double) const override;
    Eigen::Vector2d getCenter() const override;
};

} // namespace math
} // namespace navigation_function
} // namespace roboflow
