/*
  ==============================================================================

    Skin.cpp
    Created: 20 Apr 2022 12:02:31pm
    Author:  ellio

  ==============================================================================
*/

#include "Skin.h"
void Skin::drawRotarySlider(juce::Graphics& g, int x, int y, int width, int height, float sliderPos,
    const float rotaryStartAngle, const float rotaryEndAngle, juce::Slider& slider)
{
    using namespace juce; {
        auto outline = Colours::darkgrey;
        auto fill = Colours::darkturquoise;

        auto bounds = Rectangle<int>(x, y, width, height).toFloat().reduced(10);

        auto radius = jmin(bounds.getWidth(), bounds.getHeight()) / 2.0f;
        auto toAngle = rotaryStartAngle + sliderPos * (rotaryEndAngle - rotaryStartAngle);
        auto lineW = jmin(2.0f, radius * 0.5f);
        auto arcRadius = radius - lineW * 0.5f;

        //unselected arc
        Path backgroundArc;
        backgroundArc.addCentredArc(bounds.getCentreX(),
            bounds.getCentreY(),
            arcRadius,
            arcRadius,
            0.0f,
            rotaryStartAngle,
            rotaryEndAngle,
            true);

        g.setColour(outline);
        g.strokePath(backgroundArc, PathStrokeType(lineW, PathStrokeType::curved, PathStrokeType::rounded));

        if (slider.isEnabled())
        {
            //selected arc
            Path valueArc;
            valueArc.addCentredArc(bounds.getCentreX(),
                bounds.getCentreY(),
                arcRadius,
                arcRadius,
                0.0f,
                rotaryStartAngle,
                toAngle,
                true);

            g.setColour(fill);
            g.strokePath(valueArc, PathStrokeType(lineW, PathStrokeType::curved, PathStrokeType::rounded));
        }

        auto thumbWidth = lineW * 3.0f;
        Point<float> thumbPoint(bounds.getCentreX() + arcRadius * std::cos(toAngle - MathConstants<float>::halfPi),
            bounds.getCentreY() + arcRadius * std::sin(toAngle - MathConstants<float>::halfPi));

        g.setColour(slider.findColour(Slider::thumbColourId));
        g.drawLine(backgroundArc.getBounds().getCentreX(), backgroundArc.getBounds().getCentreY(), thumbPoint.getX(), thumbPoint.getY(), lineW);
        g.fillEllipse(Rectangle<float>(thumbWidth, thumbWidth).withCentre(thumbPoint));
    }
}

juce::Label* Skin::createSliderTextBox(juce::Slider& slider)
{
    using namespace juce; {

        Label* l = LookAndFeel_V4::createSliderTextBox(slider);
        l->setColour(Label::textColourId, Colours::white);
        l->setColour(Label::outlineColourId, Colour(0x00000000));
        l->setFont(10.0f);

        return l;
    }
}

juce::Slider::SliderLayout Skin::getSliderLayout(juce::Slider& slider)
{
    using namespace juce; {
        // 1. compute the actually visible textBox size from the slider textBox size and some additional constraints

        int minXSpace = 0;
        int minYSpace = 15;
        auto localBounds = slider.getLocalBounds();
        auto textBoxWidth = jmax(0, jmin(slider.getTextBoxWidth(), localBounds.getWidth() - minXSpace));
        auto textBoxHeight = jmax(0, jmin(slider.getTextBoxHeight(), localBounds.getHeight() - minYSpace));

        Slider::SliderLayout layout;

        // 2. set the textBox bounds
        layout.textBoxBounds.setWidth(textBoxWidth);
        layout.textBoxBounds.setHeight(textBoxHeight);
        layout.textBoxBounds.setX((localBounds.getWidth() - textBoxWidth) / 2);
        layout.textBoxBounds.setY(10);



        // 3. set the slider bounds
        layout.sliderBounds = localBounds;
        layout.sliderBounds.removeFromTop(textBoxHeight);

        const int thumbIndent = getSliderThumbRadius(slider);
        if (slider.isHorizontal())    layout.sliderBounds.reduce(thumbIndent, 0);
        else if (slider.isVertical()) layout.sliderBounds.reduce(0, thumbIndent);

        return layout;
    }
}
