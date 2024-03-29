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

#ifndef __DESTINATIONFUNCTION__
#define __DESTINATIONFUNCTION__

#include <Eigen/Core>

#include "ScalarObject.hpp"

namespace roboflow
{
namespace navigation_function
{
namespace math
{

class DestinationFunction final : public ScalarObject
{
  Eigen::Vector2d destination_;

public:
  // destination location: x, y
  DestinationFunction(double, double);
  DestinationFunction(Eigen::Vector2d);

  // destination location: x, y
  void setDestination(double, double);
  void setDestination(Eigen::Vector2d);
  // destination offset: dx, dy
  void offset(double, double);

  Eigen::Vector2d getDestination() const;
  double getDestX() const;
  double getDestY() const;

  double evaluate(Eigen::Vector2d) const override;
};

} // namespace math
} // namespace navigation_function
} // namespace roboflow

#endif
