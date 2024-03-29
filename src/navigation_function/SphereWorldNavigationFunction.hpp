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

#ifndef __SPHEREWORLDNAVIGATIONFUNCTION__
#define __SPHEREWORLDNAVIGATIONFUNCTION__

#include <memory>
#include <utility>
#include <unordered_map>

#include <Eigen/Core>

#include "navigation_function/NavigationFunction.hpp"
#include "navigation_function/math/Sphere.hpp"
#include "navigation_function/math/ScalarObject.hpp"

namespace roboflow
{
namespace navigation_function
{

class SphereWorldNavigationFunction final : public NavigationFunction
{
    std::unordered_map<uint64_t, std::weak_ptr<math::Sphere>> obstacles_;
    std::weak_ptr<math::Sphere> zeroth_obstacle_;
    std::weak_ptr<math::ScalarObject> destination_;
    double kappa_ = 1.0;
    DestinationFunctionType d_type_;

public:
    // insert specific obstacle; return: successful or not
    bool setObstacle(std::shared_ptr<math::Sphere>);
    // set the obstacle defining the workspace
    void setZerothObstacle(std::shared_ptr<math::Sphere>);
    // set destination function
    void setDestination(std::shared_ptr<math::ScalarObject>, DestinationFunctionType);
    // clear all obstacles
    void clear();
    // delete specific obstcle; return: successful or not
    bool eraseObstacle(uint64_t);
    // set kappa
    void setKappa(double);
    // get kappa
    double getKappa() const;

    // point
    std::pair<double, bool> evaluate(Eigen::Vector2d) override;
    // point: x, y
    std::pair<double, bool> evaluate(double, double) override;
    // get all obstacles, including the zeroth obsatcle
    std::vector<std::shared_ptr<math::StarObject>> getObstacles() const override;
    // get destination function and its type
    std::pair<std::shared_ptr<math::ScalarObject>, DestinationFunctionType>
    getDestinationFunction() const override;
};

} // namespace navigation_function
} // namespace roboflow

#endif
