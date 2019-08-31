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

#ifndef __TRANSFORM__
#define __TRANSFORM__

#include <Eigen/Core>

namespace roboflow
{
namespace navigation_function
{
namespace math
{

class Transform
{
  Eigen::Vector2d scale_;
  double rotate_;
  Eigen::Vector2d translate_;

  Eigen::Matrix2d affine_;

  void construct_affine();

public:
  // scale factor, rotation radian, translate vector
  Transform(Eigen::Vector2d, double, Eigen::Vector2d);
  // scale x, scale y, rotation radian, translate x, translate y
  Transform(double, double, double, double, double);

  Transform(const Transform &other);
  void operator=(const Transform &other);
  Transform(const Transform &&other);
  void operator=(const Transform &&other);

  // input: coordinate of the transformed frame (current wall frame)
  // return: coordinate of the original frame (rigid body frame)
  Eigen::Vector2d operator()(Eigen::Vector2d) const;
  Eigen::Vector2d transformFrom(Eigen::Vector2d) const;
  // input: coordinate of the original frame (rigid body frame)
  // return: coordinate of the transformed frame (current wall frame)
  Eigen::Vector2d transformTo(Eigen::Vector2d) const;
};

} // namespace math
} // namespace navigation_function
} // namespace roboflow

#endif
