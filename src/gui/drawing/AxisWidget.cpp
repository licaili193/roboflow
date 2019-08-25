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
}

void AxisWidget::draw(BLContext &ctx)
{
    if (predraw(ctx))
    {
        // begin drawing

        // iterate y axis labels to see what's the max width
        double max_width = 0;
        double text_height = font_.size();
        for (auto s : y_tick_labels_)
        {
            BLGlyphBuffer gb;
            gb.setUtf8Text(s.c_str(), s.length());
            BLTextMetrics m;
            font_.getTextMetrics(gb, m);
            double tmp = m.boundingBox.x1 - m.boundingBox.x0;
            if (max_width < tmp)
                max_width = tmp;
        }

        // calculate four corners of the inner canvas
        double icx = 2 * margin_ + max_width;
        double icy = margin_ + text_height / 2;
        double icw = viewport_width_ - icx - margin_;
        if (is_draw_colormap_)
            icw -= margin_ + colormap_width_;
        double ich = viewport_height_ - icy - 2 * margin_ - text_height;

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
            double pos_x = icx + (x_ticks_[i] - canvas_data_x_) / canvas_data_width_ * icw;
            double pos_y = icy + ich + margin_;
            ctx.fillUtf8Text(BLPoint(pos_x - (m.boundingBox.x1 - m.boundingBox.x0) / 2.0,
                                     pos_y + font_.size()),
                             font_,
                             x_tick_labels_[i].c_str(), x_tick_labels_[i].length());
            ctx.strokeLine(pos_x, icy + ich, pos_x, icy + ich - tick_length_);
        }
        for (int i = 0; i < y_ticks_.size(); i++)
        {
            if (y_ticks_[i] < canvas_data_y_ || y_ticks_[i] > canvas_data_y_ + canvas_data_height_)
                continue;
            BLGlyphBuffer gb;
            gb.setUtf8Text(x_tick_labels_[i].c_str(), x_tick_labels_[i].length());
            BLTextMetrics m;
            font_.getTextMetrics(gb, m);
            double pos_x = icx - m.boundingBox.x1 + m.boundingBox.x0 - margin_;
            double pos_y = icy + ich - (y_ticks_[i] - canvas_data_y_) / canvas_data_height_ * ich;
            ctx.fillUtf8Text(BLPoint(pos_x, pos_y + font_.size() - text_height / 2.0),
                             font_, y_tick_labels_[i].c_str(), y_tick_labels_[i].length());
            ctx.strokeLine(icx, pos_y, icx + tick_length_, pos_y);
        }

        // draw axis frame
        ctx.setStrokeWidth(frame_width_);
        ctx.strokeBox(icx, icy, icx + icw, icy + ich);

        // end drawing
        postdraw(ctx);
    }
}

void AxisWidget::generate_font()
{
    face_.createFromFile("/usr/share/fonts/truetype/ubuntu/Ubuntu-R.ttf");
    font_.createFromFace(face_, font_size_);
}

std::vector<double> AxisWidget::getInnerCanvasRange() const
{
    return {canvas_data_x_, canvas_data_y_,
            canvas_data_width_, canvas_data_height_};
}

std::pair<double, double> AxisWidget::getColorMapSize() const
{
    return std::make_pair(colormap_width_, std::max(viewport_height_ - 2 * margin_, 0.0));
}

} // namespace drawing
} // namespace gui
} // namespace roboflow