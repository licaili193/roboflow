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

#include <cmath>

#include "Squircle.hpp"

namespace roboflow
{
namespace navigation_function
{
namespace math
{

Squircle::Squircle(Eigen::Vector2d p, double s, double r, Eigen::Vector2d a)
    : transform_(a, r, p)
{
    is_init_ = false;
    setCenter(p);
    setSquareness(s);
    setRotation(r);
    setScale(a);
    is_init_ = true;
    set_cached_transform();
}

Squircle::Squircle(double x, double y, double s, double r, double sx, double sy)
    : Squircle({x, y}, s, r, {sx, sy}) {}

void Squircle::setCenter(Eigen::Vector2d p)
{
    center_ = std::move(p);
    if (is_init_)
        set_cached_transform();
}

void Squircle::setCenter(double x, double y)
{
    setCenter({x, y});
}

void Squircle::setSquareness(double s)
{
    s_ = s;
    if (is_init_)
        set_cached_transform();
}

void Squircle::setRotation(double ro)
{
    rotate_ = ro;
    if (is_init_)
        set_cached_transform();
}

void Squircle::setScale(Eigen::Vector2d s)
{
    scale_ = std::move(s);
    if (is_init_)
        set_cached_transform();
}

void Squircle::setScale(double sx, double sy)
{
    setScale({sx, sy});
}

void Squircle::set_cached_transform()
{
    transform_ = std::move(Transform(scale_, rotate_, center_));
}

double Squircle::evaluate(Eigen::Vector2d p) const
{
    auto tp = transform_(p);
    return (tp.squaredNorm() +
            std::sqrt(std::pow(tp(0), 4) +
                      std::pow(tp(1), 4) +
                      (2 - 4 * s_ * s_) * std::pow(tp(0) * tp(0), 2))) /
               2.0 -
           1.0;
}

double Squircle::getRadius(Eigen::Vector2d p) const
{
    auto tp = transform_(p);
    tp.normalize();
    double lou = std::sqrt(2.0 / (1.0 +
                                  std::sqrt(1.0 - 4.0 * s_ * s_ * std::pow(tp(0) * tp(1), 2.0))));
    auto tp2 = transform_.transformTo(lou * tp);
    return (tp2 - center_).norm();
}

double Squircle::getRadius(double angle) const
{
    Eigen::Vector2d p(std::cos(angle), std::sin(angle));
    return getRadius(center_ + p);
}

Eigen::Vector2d Squircle::getCenter() const
{
    return center_;
}

} // namespace math
} // namespace navigation_function
} // namespace roboflow
