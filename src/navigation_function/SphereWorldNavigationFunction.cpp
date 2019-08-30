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

#include "SphereWorldNavigationFunction.hpp"

namespace roboflow
{
namespace navigation_function
{

void SphereWorldNavigationFunction::setKappa(double kappa)
{
    kappa_ = kappa;
}

double SphereWorldNavigationFunction::getKappa() const
{
    return kappa_;
}

void SphereWorldNavigationFunction::setZerothObstacle(std::shared_ptr<math::Sphere> obj)
{
    zeroth_obstacle_ = obj;
}

bool SphereWorldNavigationFunction::setObstacle(std::shared_ptr<math::Sphere> obj)
{
    if (!obj)
        return false;
    uint64_t id = obj->getId();
    auto res = obstacles_.insert(std::make_pair(id, obj));
    return res.second;
}

bool SphereWorldNavigationFunction::eraseObstacle(uint64_t id)
{
    return static_cast<bool>(obstacles_.erase(id));
}

void SphereWorldNavigationFunction::setDestination(std::shared_ptr<math::ScalarObject> dest)
{
    destination_ = dest;
}

void SphereWorldNavigationFunction::clear()
{
    obstacles_.clear();
    zeroth_obstacle_.reset();
    destination_.reset();
    kappa_ = 1.0;
}

std::pair<double, bool> SphereWorldNavigationFunction::evaluate(Eigen::Vector2d p)
{
    double J = 0;
    if (auto t = destination_.lock())
        J = t->evaluate(p);
    else
        return std::make_pair(0, false); // TODO: log here

    double beta = 1.0;
    if (auto t = zeroth_obstacle_.lock())
    {
        double tmp = t->evaluate(p);
        if (tmp > 0)
            return std::make_pair(0, false); // TODO: log here
        else
            beta *= std::fabs(tmp);
    }
    else
    {
        // TODO: log here
        return std::make_pair(0, false);
    }
    for (auto pr : obstacles_)
    {
        auto o = pr.second;
        if (auto t = o.lock())
        {
            double tmp = t->evaluate(p);
            if (tmp < 0)
                return std::make_pair(0, false); // TODO: log here
            else
                beta *= tmp;
        }
        else
        {
            eraseObstacle(pr.first);
            // TODO: log here
        }
    }
    return std::make_pair(
        J / std::pow(std::pow(J, kappa_) + beta, 1.0 / kappa_),
        true);
}

} // namespace navigation_function
} // namespace roboflow