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

#include "Transform.hpp"

namespace roboflow
{
namespace navigation_function
{
namespace math
{

Transform::Transform(double s, double r, Eigen::Vector2d t)
{
    scale_ = s;
    rotate_ = r;
    translate_ = t;

    construct_affine();
}

Transform::Transform(double s, double r, double x, double y)
{
    Transform(s, r, {x, y});
}

void Transform::construct_affine()
{
    Eigen::Matrix2d S = (Eigen::Matrix2d() << scale_, 0, 0, scale_).finished();
    Eigen::Matrix2d R = (Eigen::Matrix2d() << std::cos(rotate_), -std::sin(rotate_),
                         std::sin(rotate_), std::cos(rotate_))
                            .finished();
    affine_ = S * R;
}

Eigen::Vector2d Transform::transformFrom(Eigen::Vector2d p)
{
    return affine_.inverse() * (p - translate_);
}

Eigen::Vector2d Transform::transformTo(Eigen::Vector2d p)
{
    return affine_ * p + translate_;
}

} // namespace math
} // namespace navigation_function
} // namespace roboflow
