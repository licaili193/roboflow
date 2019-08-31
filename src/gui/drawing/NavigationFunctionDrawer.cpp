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

#include <functional>

#include "navigation_function/math/DestinationFunction.hpp"
#include "navigation_function/math/BubbleDestinationFunction.hpp"

#include "third_party/Jonathan/ListContour.h"

#include "NavigationFunctionDrawer.hpp"

namespace roboflow
{
namespace gui
{
namespace drawing
{

BLPath NavigationFunctionDrawer::drawStarObject(
    std::shared_ptr<navigation_function::math::StarObject> obj)
{
    auto c = obj->getCenter();
    BLPath path;
    double r = 0;
    bool is_first = true;
    while (r < 2.0 * M_PI)
    {
        double lou = obj->getRadius(r);
        if (is_first)
        {
            path.moveTo(c(0) + std::cos(r) * lou, c(1) + std::sin(r) * lou);
            is_first = false;
        }
        else
        {
            path.lineTo(c(0) + std::cos(r) * lou, c(1) + std::sin(r) * lou);
        }
        r += M_PI / 90.0;
    }
    return path;
}

std::vector<std::pair<BLPath, double>> NavigationFunctionDrawer::drawContour(
    std::shared_ptr<navigation_function::NavigationFunction> nf,
    BLRect rect)
{
    using Jonathan::CLineStrip;
    using Jonathan::CLineStripList;

    Jonathan::CListContour contour;
    double limits[4] = {rect.x, rect.x + rect.w, rect.y, rect.y + rect.h};
    std::vector<double> planes =
        {0.05, 0.1, 0.15, 0.2, 0.25, 0.3, 0.35, 0.4, 0.45, 0.5,
         0.55, 0.6, 0.65, 0.7, 0.75, 0.8, 0.85, 0.9, 0.95};
    contour.SetLimits(limits);
    contour.SetPlanes(planes);
    contour.SetFirstGrid(256, 256);
    contour.SetSecondaryGrid(1024, 1024);
    auto f = [&](double x, double y) -> double {
        return (nf->evaluate(x, y)).first;
    };
    contour.SetFieldFcn(f);

    // Plotting strip generated by CLineStripList
    // generating info
    contour.Generate();

    // draw line strips
    CLineStripList *pStripList;
    CLineStrip *pStrip;
    uint32_t i, index;
    CLineStripList::iterator pos;
    CLineStrip::iterator pos2;
    double pLimits[4];
    double x, y;

    std::vector<std::pair<BLPath, double>> res;

    contour.GetLimits(pLimits);
    for (i = 0; i < contour.GetNPlanes(); i++)
    {
        BLPath path;
        pStripList = contour.GetLines(i);
        for (pos = pStripList->begin(); pos != pStripList->end(); pos++)
        {
            pStrip = (*pos);
            if (pStrip->empty())
                continue;

            // putting point at start and end of strip
            // retreiving index
            bool is_first = true;
            for (auto index : *pStrip)
            {
                x = contour.GetXi(index);
                y = contour.GetYi(index);
                if (is_first)
                {
                    path.moveTo(x, y);
                    is_first = false;
                }
                else
                {
                    path.lineTo(x, y);
                }
            }
        }
        res.emplace_back(std::move(path), contour.GetPlane(i));
    }

    return res;
}

void NavigationFunctionDrawer::drawNavigationFunction(
    std::shared_ptr<navigation_function::NavigationFunction> nf,
    BLRect rect, BLContext &ctx, double normal_stoke_width)
{
    // draw contour
    auto c = std::move(drawContour(nf, rect));
    ctx.setStrokeWidth(normal_stoke_width);
    ctx.setStrokeStyle(BLRgba32(0xFF000000));
    for (auto p : c)
    {
        ctx.strokePath(p.first);
    }

    // draw boundary
    auto objs = std::move(nf->getObstacles());
    ctx.setStrokeWidth(2.0 * normal_stoke_width);
    for (auto p : objs)
    {
        auto path = std::move(drawStarObject(p));
        ctx.strokePath(path);
    }

    // draw destination
    auto p = nf->getDestinationFunction();
    if (p.second ==
        navigation_function::DestinationFunctionType::DestSphere)
    {
        using BD = navigation_function::math::BubbleDestinationFunction;
        std::shared_ptr<BD> dest = std::dynamic_pointer_cast<BD>(p.first);
        // dest->
        ctx.setFillStyle(BLRgba32(0xFF000000));
        ctx.fillCircle(dest->getDestX(), dest->getDestY(), 5.0 * normal_stoke_width);
        ctx.setStrokeWidth(normal_stoke_width);
        BLArray<double> dash;
        dash.append(5.0 * normal_stoke_width);
        dash.append(5.0 * normal_stoke_width);
        ctx.setStrokeDashArray(dash);
        ctx.strokeCircle(dest->getDestX(), dest->getDestY(), dest->getRadius());
    }
    else
    {
        using BD = navigation_function::math::DestinationFunction;
        std::shared_ptr<BD> dest = std::dynamic_pointer_cast<BD>(p.first);
        // dest->
        ctx.setFillStyle(BLRgba32(0xFF000000));
        ctx.fillCircle(dest->getDestX(), dest->getDestY(), normal_stoke_width);
    }
}

} // namespace drawing
} // namespace gui
} // namespace roboflow