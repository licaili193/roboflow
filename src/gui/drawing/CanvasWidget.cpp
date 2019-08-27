#include <cmath>
#include <algorithm>

#include "CanvasWidget.hpp"

namespace roboflow
{
namespace gui
{
namespace drawing
{

void CanvasWidget::init()
{
    // temporary init
}

void CanvasWidget::setRange(double x, double y, double dx, double dy)
{
    data_x_ = x;
    data_y_ = y;
    data_dx_ = dx;
    data_dy_ = dy;
}

void CanvasWidget::draw(BLContext &ctx)
{
    if (predraw(ctx))
    {
        const double normal_stoke_width =
            std::max(data_dx_ / viewport_width_, data_dy_ / viewport_height_);

        ctx.translate(0, viewport_height_);
        ctx.scale(viewport_width_ / data_dx_,
                  -viewport_height_ / data_dy_);
        ctx.translate(-data_x_, -data_y_);
        // begin drawing

        ctx.setStrokeWidth(normal_stoke_width);
        ctx.setStrokeStyle(BLRgba32(0xFF000000));
        ctx.strokeCircle(0, 0, 0.2);

        // end drawing
        postdraw(ctx);
    }
}

} // namespace drawing
} // namespace gui
} // namespace roboflow
