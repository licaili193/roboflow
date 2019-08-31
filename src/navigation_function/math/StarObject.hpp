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

#ifndef __STAROBJECT__
#define __STAROBJECT__

#include <vector>

#include <Eigen/Core>

namespace roboflow
{
namespace navigation_function
{
namespace math
{

class StarObject
{
  static uint64_t __star_object_index;

  uint64_t id_;

public:
  StarObject();

  // direction vector
  virtual double getRadius(Eigen::Vector2d) const = 0;
  // angle
  virtual double getRadius(double) const = 0;
  virtual Eigen::Vector2d getCenter() const = 0;

  uint64_t getId() const;
};

} // namespace math
} // namespace navigation_function
} // namespace roboflow

#endif
