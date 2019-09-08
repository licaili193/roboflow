#include <cmath>
#include <algorithm>
#include <sstream>

#include "AxisWidget.hpp"

namespace roboflow
{
namespace gui
{
namespace drawing
{

AxisWidget::AxisWidget() : DrawableWidget()
{
    generate_font();
}

void AxisWidget::setRange(double x, double y, double dx, double dy)
{
    data_x_ = x;
    data_y_ = y;
    data_dx_ = std::max(dx, 0.0);
    data_dy_ = std::max(dy, 0.0);

    canvas_data_x_ = x - dx * 0.05;
    canvas_data_y_ = y - dy * 0.05;
    canvas_data_width_ = std::max(dx * 1.1, 0.0);
    canvas_data_height_ = std::max(dy * 1.1, 0.0);

    x_ticks_.clear();
    y_ticks_.clear();
    x_tick_labels_.clear();
    y_tick_labels_.clear();

    get_ticks();

    for (auto d : x_ticks_)
    {
        std::ostringstream os;
        os << d;
        std::string tmp = os.str();
        x_tick_labels_.push_back(std::move(tmp));
    }
    for (auto d : y_ticks_)
    {
        std::ostringstream os;
        os << d;
        std::string tmp = os.str();
        y_tick_labels_.push_back(std::move(tmp));
    }

    // iterate y axis labels to see what's the max width
    text_height_ = font_.size();
    max_y_label_width_ = 0.0;
    for (auto s : y_tick_labels_)
    {
        BLGlyphBuffer gb;
        gb.setUtf8Text(s.c_str(), s.length());
        BLTextMetrics m;
        font_.getTextMetrics(gb, m);
        double tmp = m.boundingBox.x1 - m.boundingBox.x0;
        if (max_y_label_width_ < tmp)
            max_y_label_width_ = tmp;
    }
    get_cached_canvas_dimension();
}

std::vector<double> AxisWidget::get_ticks_helper(double max, double min, int step_count)
{
    if (max <= min)
        return {};
    double epsilon = (max - min) / 1e6;
    max += epsilon;
    min -= epsilon;
    double range = max - min;

    double rough_step = range / (step_count - 1);
    std::vector<double> good_normalized_steps = {1, 1.5, 2, 2.5, 5, 7.5, 10};

    double step_power = std::pow(10.0, -std::floor(std::log10(std::fabs(rough_step))));
    double normalized_step = rough_step * step_power;
    double good_normalized_step = *(std::lower_bound(good_normalized_steps.begin(),
                                                     good_normalized_steps.end(),
                                                     normalized_step));
    double step = good_normalized_step / step_power;

    double scale_max = std::ceil(max / step) * step;
    double scale_min = std::floor(min / step) * step;

    std::vector<double> res;
    double scale_accum = scale_min;
    while (scale_accum <= scale_max)
    {
        if (std::fabs(scale_accum) < 1e-5)
            scale_accum = 0.0;
        res.push_back(scale_accum);
        scale_accum += step;
    }
    return res;
}

void AxisWidget::get_ticks()
{
    int steps = viewport_width_ / 100 + 2;
    steps = std::max(std::min(steps, 10), 2);
    x_ticks_ = std::move(get_ticks_helper(data_x_ + data_dx_, data_x_, steps));
    steps = viewport_height_ / 100 + 2;
    steps = std::max(std::min(steps, 10), 2);
    y_ticks_ = std::move(get_ticks_helper(data_y_ + data_dy_, data_y_, steps));
}

void AxisWidget::setDrawColormap(bool draw)
{
    is_draw_colormap_ = draw;
    get_cached_canvas_dimension();
}

void AxisWidget::setViewport(double x, double y, double w, double h)
{
    DrawableWidget::setViewport(x, y, w, h);
    get_cached_canvas_dimension();
}

void AxisWidget::draw(BLContext &ctx)
{
    if (predraw(ctx))
    {
        // begin drawing

        // draw each ticks
        ctx.setFillStyle(BLRgba32(0xFF000000));
        ctx.setStrokeStyle(BLRgba32(0xFF000000));
        for (int i = 0; i < x_ticks_.size(); i++)
        {
            if (x_ticks_[i] < canvas_data_x_ || x_ticks_[i] > canvas_data_x_ + canvas_data_width_)
                continue;
            BLGlyphBuffer gb;
            gb.setUtf8Text(x_tick_labels_[i].c_str(), x_tick_labels_[i].length());
            BLTextMetrics m;
            font_.getTextMetrics(gb, m);
            double pos_x = icx_ + (x_ticks_[i] - canvas_data_x_) / canvas_data_width_ * icw_;
            double pos_y = icy_ + ich_ + margin_;
            ctx.fillUtf8Text(BLPoint(pos_x - (m.boundingBox.x1 - m.boundingBox.x0) / 2.0,
                                     pos_y + font_.size()),
                             font_,
                             x_tick_labels_[i].c_str(), x_tick_labels_[i].length());
            ctx.strokeLine(pos_x, icy_ + ich_, pos_x, icy_ + ich_ - tick_length_);
        }
        for (int i = 0; i < y_ticks_.size(); i++)
        {
            if (y_ticks_[i] < canvas_data_y_ || y_ticks_[i] > canvas_data_y_ + canvas_data_height_)
                continue;
            BLGlyphBuffer gb;
            gb.setUtf8Text(y_tick_labels_[i].c_str(), y_tick_labels_[i].length());
            BLTextMetrics m;
            font_.getTextMetrics(gb, m);
            double pos_x = icx_ - m.boundingBox.x1 + m.boundingBox.x0 - margin_;
            double pos_y = icy_ + ich_ - (y_ticks_[i] - canvas_data_y_) / canvas_data_height_ * ich_;
            ctx.fillUtf8Text(BLPoint(pos_x, pos_y + font_.size() - text_height_ / 2.0),
                             font_, y_tick_labels_[i].c_str(), y_tick_labels_[i].length());
            ctx.strokeLine(icx_, pos_y, icx_ + tick_length_, pos_y);
        }

        // draw axis frame
        ctx.setStrokeWidth(frame_width_);
        ctx.strokeBox(icx_, icy_, icx_ + icw_, icy_ + ich_);

        // end drawing
        postdraw(ctx);
    }
}

void AxisWidget::generate_font()
{
    face_.createFromFile("/usr/share/fonts/truetype/ubuntu/Ubuntu-R.ttf");
    font_.createFromFace(face_, font_size_);
}

void AxisWidget::get_cached_canvas_dimension()
{
    icx_ = 2 * margin_ + max_y_label_width_;
    icy_ = margin_ + text_height_ / 2;
    icw_ = viewport_width_ - icx_ - margin_;
    if (is_draw_colormap_)
        icw_ -= margin_ + colormap_width_;
    ich_ = viewport_height_ - icy_ - 2 * margin_ - text_height_;
}

BLRect AxisWidget::getInnerCanvasRange() const
{
    return BLRect(canvas_data_x_, canvas_data_y_,
                  canvas_data_width_, canvas_data_height_);
}

BLRect AxisWidget::getInnerCanvasRect() const
{
    return BLRect(icx_, icy_, icw_, ich_);
}

BLRect AxisWidget::getColorMapRect() const
{
    return BLRect(viewport_width_ - colormap_width_ - margin_,
                  margin_, colormap_width_, std::max(viewport_height_ - 2 * margin_, 0.0));
}

} // namespace drawing
} // namespace gui
} // namespace roboflow
