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

#ifndef __NAVIGATIONFUNCTION__
#define __NAVIGATIONFUNCTION__

#include <vector>
#include <memory>
#include <utility>

#include <Eigen/Core>

#include "navigation_function/math/StarObject.hpp"
#include "navigation_function/math/ScalarObject.hpp"

namespace roboflow
{
namespace navigation_function
{

enum class DestinationFunctionType
{
    DestPoint,
    DestSphere
};

class NavigationFunction
{
public:
    // point
    virtual std::pair<double, bool> evaluate(Eigen::Vector2d) = 0;
    // point: x, y
    virtual std::pair<double, bool> evaluate(double, double) = 0;
    // get all obstacles, including the zeroth obsatcle
    virtual std::vector<std::shared_ptr<math::StarObject>> getObstacles() const = 0;
    // get destination function and its type
    virtual std::pair<std::shared_ptr<math::ScalarObject>, DestinationFunctionType>
    getDestinationFunction() const = 0;
};

} // namespace navigation_function
} // namespace roboflow

#endif