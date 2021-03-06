/*
  ==============================================================================

    DisplayWindow.cpp
    Created: 18 Apr 2018 10:20:17pm
    Author:  Wojtek Pilwinski

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "Display_Logarithmic.h"

//==============================================================================
Display_Logarithmic::Display_Logarithmic()
{
    margXLeft = 46.0f;
    margXRight = 10.0f;
    margYBot = 20.0f+30.0f;
    margYTop = 22.0f;
    
    wZoom.setSliderStyle(Slider::SliderStyle::ThreeValueHorizontal);
    addAndMakeVisible(&wZoom);
    wZoom.setTextBoxStyle(Slider::NoTextBox, true, 0, 0);
    wZoom.addListener(this);
}

Display_Logarithmic::~Display_Logarithmic()
{
}

void Display_Logarithmic::paint (Graphics& g)
{
    float lineThickness = 0.7f;
    float altLineThickness = 0.3f;

    if(wNyquist>1)
    {
        _winX = getWidth() - margXLeft - margXRight;
        _winY = getHeight() - margYBot - margYTop;

        
        scale1Hz     = (log10(1.0f)     - log10(lowEnd)) / (log10(topEnd) - log10(lowEnd));
        scale2Hz     = (log10(2.0f)     - log10(lowEnd)) / (log10(topEnd) - log10(lowEnd));
        scale3Hz     = (log10(3.0f)     - log10(lowEnd)) / (log10(topEnd) - log10(lowEnd));
        scale4Hz     = (log10(4.0f)     - log10(lowEnd)) / (log10(topEnd) - log10(lowEnd));
        scale5Hz     = (log10(5.0f)     - log10(lowEnd)) / (log10(topEnd) - log10(lowEnd));
        scale6Hz     = (log10(6.0f)     - log10(lowEnd)) / (log10(topEnd) - log10(lowEnd));
        scale7Hz     = (log10(7.0f)     - log10(lowEnd)) / (log10(topEnd) - log10(lowEnd));
        scale8Hz     = (log10(8.0f)     - log10(lowEnd)) / (log10(topEnd) - log10(lowEnd));
        scale10Hz    = (log10(10.0f)    - log10(lowEnd)) / (log10(topEnd) - log10(lowEnd));
        scale20Hz    = (log10(20.0f)    - log10(lowEnd)) / (log10(topEnd) - log10(lowEnd));
        scale30Hz    = (log10(30.0f)    - log10(lowEnd)) / (log10(topEnd) - log10(lowEnd));
        scale40Hz    = (log10(40.0f)    - log10(lowEnd)) / (log10(topEnd) - log10(lowEnd));
        scale50Hz    = (log10(50.0f)    - log10(lowEnd)) / (log10(topEnd) - log10(lowEnd));
        scale60Hz    = (log10(60.0f)    - log10(lowEnd)) / (log10(topEnd) - log10(lowEnd));
        scale70Hz    = (log10(70.0f)    - log10(lowEnd)) / (log10(topEnd) - log10(lowEnd));
        scale80Hz    = (log10(80.0f)    - log10(lowEnd)) / (log10(topEnd) - log10(lowEnd));
        scale100Hz   = (log10(100.0f)   - log10(lowEnd)) / (log10(topEnd) - log10(lowEnd));
        scale200Hz   = (log10(200.0f)   - log10(lowEnd)) / (log10(topEnd) - log10(lowEnd));
        scale300Hz   = (log10(300.0f)   - log10(lowEnd)) / (log10(topEnd) - log10(lowEnd));
        scale400Hz   = (log10(400.0f)   - log10(lowEnd)) / (log10(topEnd) - log10(lowEnd));
        scale500Hz   = (log10(500.0f)   - log10(lowEnd)) / (log10(topEnd) - log10(lowEnd));
        scale600Hz   = (log10(600.0f)   - log10(lowEnd)) / (log10(topEnd) - log10(lowEnd));
        scale700Hz   = (log10(700.0f)   - log10(lowEnd)) / (log10(topEnd) - log10(lowEnd));
        scale800Hz   = (log10(800.0f)   - log10(lowEnd)) / (log10(topEnd) - log10(lowEnd));
        scale1000Hz  = (log10(1000.0f)  - log10(lowEnd)) / (log10(topEnd) - log10(lowEnd));
        scale2000Hz  = (log10(2000.0f)  - log10(lowEnd)) / (log10(topEnd) - log10(lowEnd));
        scale3000Hz  = (log10(3000.0f)  - log10(lowEnd)) / (log10(topEnd) - log10(lowEnd));
        scale4000Hz  = (log10(4000.0f)  - log10(lowEnd)) / (log10(topEnd) - log10(lowEnd));
        scale5000Hz  = (log10(5000.0f)  - log10(lowEnd)) / (log10(topEnd) - log10(lowEnd));
        scale6000Hz  = (log10(6000.0f)  - log10(lowEnd)) / (log10(topEnd) - log10(lowEnd));
        scale7000Hz  = (log10(7000.0f)  - log10(lowEnd)) / (log10(topEnd) - log10(lowEnd));
        scale8000Hz  = (log10(8000.0f)  - log10(lowEnd)) / (log10(topEnd) - log10(lowEnd));
        scale10000Hz = (log10(10000.0f) - log10(lowEnd)) / (log10(topEnd) - log10(lowEnd));
        scale20000Hz = (log10(20000.0f) - log10(lowEnd)) / (log10(topEnd) - log10(lowEnd));
        scaleNyquist = (log10(nyqFr)    - log10(lowEnd)) / (log10(topEnd) - log10(lowEnd));
        scaleSampRat = (log10(sampRat)  - log10(lowEnd)) / (log10(topEnd) - log10(lowEnd));
        
        g.setColour(Colours::lightblue);
        
        g.drawLine(margXLeft, margYTop, margXLeft, margYTop+ _winY);
        
        
        if(scale1Hz < 1.0f && scale1Hz > 0.0f) {
            g.drawLine((scale1Hz * _winX)+margXLeft, margYTop, (scale1Hz * _winX)+margXLeft, margYTop+ _winY, lineThickness);
            g.drawText("1",    margXLeft-31.0f + (scale1Hz*_winX),    getHeight()-margYBot, 60, 20, Justification::centred);
        }
 
        if(scale2Hz < 1.0f && scale2Hz > 0.0f) {
            g.drawLine((scale2Hz * _winX)+margXLeft, margYTop, (scale2Hz * _winX)+margXLeft, margYTop+ _winY, altLineThickness);
            if(topEnd - lowEnd < 20  || scale1Hz<0.0f)
                g.drawText("2",    margXLeft-31.0f + (scale2Hz*_winX),    getHeight()-margYBot, 60, 20, Justification::centred);
        }
        
        if(scale3Hz < 1.0f && scale3Hz > 0.0f) {
            g.drawLine((scale3Hz * _winX)+margXLeft, margYTop, (scale3Hz * _winX)+margXLeft, margYTop+ _winY, altLineThickness);
            if(topEnd - lowEnd < 20  || scale2Hz<0.0f)
                g.drawText("3",    margXLeft-31.0f + (scale3Hz*_winX),    getHeight()-margYBot, 60, 20, Justification::centred);
        }
        
        if(scale4Hz < 1.0f && scale4Hz > 0.0f) {
            g.drawLine((scale4Hz * _winX)+margXLeft, margYTop, (scale4Hz * _winX)+margXLeft, margYTop+ _winY, altLineThickness);
            if(topEnd - lowEnd < 20  || scale3Hz<0.0f)
                g.drawText("4",    margXLeft-31.0f + (scale4Hz*_winX),    getHeight()-margYBot, 60, 20, Justification::centred);
        }
        
        
        if(scale5Hz < 1.0f && scale5Hz > 0.0f) {
            g.drawLine((scale5Hz * _winX)+margXLeft, margYTop, (scale5Hz * _winX)+margXLeft, margYTop+ _winY, altLineThickness);
            if(topEnd - lowEnd < 20  || scale4Hz<0.0f)
                g.drawText("5",    margXLeft-31.0f + (scale5Hz*_winX),    getHeight()-margYBot, 60, 20, Justification::centred);
        }
        
        if(scale6Hz < 1.0f && scale6Hz > 0.0f) {
            g.drawLine((scale6Hz * _winX)+margXLeft, margYTop, (scale6Hz * _winX)+margXLeft, margYTop+ _winY, altLineThickness);
            if(topEnd - lowEnd < 20  || scale5Hz<0.0f)
                g.drawText("6",    margXLeft-31.0f + (scale6Hz*_winX),    getHeight()-margYBot, 60, 20, Justification::centred);
        }
        
        if(scale7Hz < 1.0f && scale7Hz > 0.0f) {
            g.drawLine((scale7Hz * _winX)+margXLeft, margYTop, (scale7Hz * _winX)+margXLeft, margYTop+ _winY, altLineThickness);
            if(topEnd - lowEnd < 20  || scale6Hz<0.0f)
                g.drawText("7",    margXLeft-31.0f + (scale7Hz*_winX),    getHeight()-margYBot, 60, 20, Justification::centred);
        }
        
        if(scale8Hz < 1.0f && scale8Hz > 0.0f) {
            g.drawLine((scale8Hz * _winX)+margXLeft, margYTop, (scale8Hz * _winX)+margXLeft, margYTop+ _winY, altLineThickness);
            if(topEnd - lowEnd < 20  || scale7Hz<0.0f)
                g.drawText("8",    margXLeft-31.0f + (scale8Hz*_winX),    getHeight()-margYBot, 60, 20, Justification::centred);
        }
        
        
        if(scale10Hz < 1.0f && scale10Hz > 0.0f) {
            g.drawLine((scale10Hz * _winX)+margXLeft, margYTop, (scale10Hz * _winX)+margXLeft, margYTop+ _winY, lineThickness);
            g.drawText("10",    margXLeft-31.0f + (scale10Hz*_winX),    getHeight()-margYBot, 60, 20, Justification::centred);
        }
        
        if(scale20Hz < 1.0f && scale20Hz > 0.0f) {
            g.drawLine((scale20Hz * _winX)+margXLeft, margYTop, (scale20Hz * _winX)+margXLeft, margYTop+ _winY, altLineThickness);
            if((topEnd - lowEnd < 100 && scale5Hz<0.0f)  || scale10Hz<0.0f || scale30Hz>1.0f)
                g.drawText("20",    margXLeft-31.0f + (scale20Hz*_winX),    getHeight()-margYBot, 60, 20, Justification::centred);
        }
        
        if(scale30Hz < 1.0f && scale30Hz > 0.0f) {
            g.drawLine((scale30Hz * _winX)+margXLeft, margYTop, (scale30Hz * _winX)+margXLeft, margYTop+ _winY, altLineThickness);
            if((topEnd - lowEnd < 100 && scale5Hz<0.0f)  || scale20Hz<0.0f || scale40Hz>1.0f)
                g.drawText("30",    margXLeft-31.0f + (scale30Hz*_winX),    getHeight()-margYBot, 60, 20, Justification::centred);
        }
        
        if(scale40Hz < 1.0f && scale40Hz > 0.0f) {
            g.drawLine((scale40Hz * _winX)+margXLeft, margYTop, (scale40Hz * _winX)+margXLeft, margYTop+ _winY, altLineThickness);
            if((topEnd - lowEnd < 100 && scale5Hz<0.0f)  || scale30Hz<0.0f || scale50Hz>1.0f)
                g.drawText("40",    margXLeft-31.0f + (scale40Hz*_winX),    getHeight()-margYBot, 60, 20, Justification::centred);
        }
        
        if(scale50Hz < 1.0f && scale50Hz > 0.0f) {
            g.drawLine((scale50Hz * _winX)+margXLeft, margYTop, (scale50Hz * _winX)+margXLeft, margYTop+ _winY, altLineThickness);
            if((topEnd - lowEnd < 100 && scale5Hz<0.0f)  || scale40Hz<0.0f || scale60Hz>1.0f)
                g.drawText("50",    margXLeft-31.0f + (scale50Hz*_winX),    getHeight()-margYBot, 60, 20, Justification::centred);
        }
        
        if(scale60Hz < 1.0f && scale60Hz > 0.0f) {
            g.drawLine((scale60Hz * _winX)+margXLeft, margYTop, (scale60Hz * _winX)+margXLeft, margYTop+ _winY, altLineThickness);
            if((topEnd - lowEnd < 100 && scale5Hz<0.0f)  || scale50Hz<0.0f || scale70Hz>1.0f)
                g.drawText("60",    margXLeft-31.0f + (scale60Hz*_winX),    getHeight()-margYBot, 60, 20, Justification::centred);
        }
        
        if(scale70Hz < 1.0f && scale70Hz > 0.0f) {
            g.drawLine((scale70Hz * _winX)+margXLeft, margYTop, (scale70Hz * _winX)+margXLeft, margYTop+ _winY, altLineThickness);
            if((topEnd - lowEnd < 100 && scale5Hz<0.0f)  || scale60Hz<0.0f || scale80Hz>1.0f)
                g.drawText("70",    margXLeft-31.0f + (scale70Hz*_winX),    getHeight()-margYBot, 60, 20, Justification::centred);
        }
        
        if(scale80Hz < 1.0f && scale80Hz > 0.0f) {
            g.drawLine((scale80Hz * _winX)+margXLeft, margYTop, (scale80Hz * _winX)+margXLeft, margYTop+ _winY, altLineThickness);
            if((topEnd - lowEnd < 100 && scale5Hz<0.0f)  || scale70Hz<0.0f || scale100Hz>1.0f)
                g.drawText("80",    margXLeft-31.0f + (scale80Hz*_winX),    getHeight()-margYBot, 60, 20, Justification::centred);
        }
        
        if(scale100Hz < 1.0f && scale100Hz > 0.0f) {
            g.drawLine((scale100Hz * _winX)+margXLeft, margYTop, (scale100Hz * _winX)+margXLeft, margYTop+ _winY, lineThickness);
            g.drawText("100",   margXLeft-30.0f + (scale100Hz*_winX),   getHeight()-margYBot, 60, 20, Justification::centred);
        }
        
        if(scale200Hz < 1.0f && scale200Hz > 0.0f) {
            g.drawLine((scale200Hz * _winX)+margXLeft, margYTop, (scale200Hz * _winX)+margXLeft, margYTop+ _winY, altLineThickness);
            if((topEnd - lowEnd < 1250 && scale50Hz<0.0f)  || scale100Hz<0.0f || scale300Hz>1.0f)
                g.drawText("200",   margXLeft-30.0f + (scale200Hz*_winX),  getHeight()-margYBot, 60, 20, Justification::centred);
        }
        
        if(scale300Hz < 1.0f && scale300Hz > 0.0f) {
            g.drawLine((scale300Hz * _winX)+margXLeft, margYTop, (scale300Hz * _winX)+margXLeft, margYTop+ _winY, altLineThickness);
            if((topEnd - lowEnd < 1250 && scale50Hz<0.0f)  || scale200Hz<0.0f || scale400Hz>1.0f)
                g.drawText("300",   margXLeft-30.0f + (scale300Hz*_winX),  getHeight()-margYBot, 60, 20, Justification::centred);
        }
        
        if(scale400Hz < 1.0f && scale400Hz > 0.0f) {
            g.drawLine((scale400Hz * _winX)+margXLeft, margYTop, (scale400Hz * _winX)+margXLeft, margYTop+ _winY, altLineThickness);
            if((topEnd - lowEnd < 1250 && scale50Hz<0.0f)  || scale300Hz<0.0f || scale500Hz>1.0f)
                g.drawText("400",   margXLeft-30.0f + (scale400Hz*_winX),  getHeight()-margYBot, 60, 20, Justification::centred);
        }
        
        if(scale500Hz < 1.0f && scale500Hz > 0.0f) {
            g.drawLine((scale500Hz * _winX)+margXLeft, margYTop, (scale500Hz * _winX)+margXLeft, margYTop+ _winY, altLineThickness);
            if((topEnd - lowEnd < 1250 && scale50Hz<0.0f)  || scale400Hz<0.0f || scale600Hz>1.0f)
                g.drawText("500",   margXLeft-30.0f + (scale500Hz*_winX),  getHeight()-margYBot, 60, 20, Justification::centred);
        }
        
        if(scale600Hz < 1.0f && scale600Hz > 0.0f) {
            g.drawLine((scale600Hz * _winX)+margXLeft, margYTop, (scale600Hz * _winX)+margXLeft, margYTop+ _winY, altLineThickness);
            if((topEnd - lowEnd < 1250 && scale50Hz<0.0f)  || scale500Hz<0.0f || scale700Hz>1.0f)
                g.drawText("600",   margXLeft-30.0f + (scale600Hz*_winX),  getHeight()-margYBot, 60, 20, Justification::centred);
        }
        
        if(scale700Hz < 1.0f && scale700Hz > 0.0f) {
            g.drawLine((scale700Hz * _winX)+margXLeft, margYTop, (scale700Hz * _winX)+margXLeft, margYTop+ _winY, altLineThickness);
            if((topEnd - lowEnd < 1250 && scale50Hz<0.0f)  || scale600Hz<0.0f || scale800Hz>1.0f)
                g.drawText("700",   margXLeft-30.0f + (scale700Hz*_winX),  getHeight()-margYBot, 60, 20, Justification::centred);
        }
        
        if(scale800Hz < 1.0f && scale800Hz > 0.0f) {
            g.drawLine((scale800Hz * _winX)+margXLeft, margYTop, (scale800Hz * _winX)+margXLeft, margYTop+ _winY, altLineThickness);
            if((topEnd - lowEnd < 1250 && scale50Hz<0.0f)  || scale700Hz<0.0f || scale1000Hz>1.0f)
                g.drawText("800",   margXLeft-30.0f + (scale800Hz*_winX),  getHeight()-margYBot, 60, 20, Justification::centred);
        }
        
        if(scale1000Hz <1.0f && scale1000Hz > 0.0f) {
            g.drawLine((scale1000Hz * _winX)+margXLeft, margYTop, (scale1000Hz * _winX)+margXLeft, margYTop+ _winY, lineThickness);
            g.drawText("1k",    margXLeft-30.0f + (scale1000Hz*_winX),   getHeight()-margYBot, 60, 20, Justification::centred);
        }
        
        if(scale2000Hz <1.0f && scale2000Hz > 0.0f) {
            g.drawLine((scale2000Hz * _winX)+margXLeft, margYTop, (scale2000Hz * _winX)+margXLeft, margYTop+ _winY, altLineThickness);
            if((topEnd - lowEnd < 21050 && scale500Hz<0.0f)  || scale1000Hz<0.0f || scale3000Hz>1.0f)
                g.drawText("2k",    margXLeft-30.0f + (scale2000Hz*_winX),   getHeight()-margYBot, 60, 20, Justification::centred);
        }
        
        if(scale3000Hz <1.0f && scale3000Hz > 0.0f) {
            g.drawLine((scale3000Hz * _winX)+margXLeft, margYTop, (scale3000Hz * _winX)+margXLeft, margYTop+ _winY, altLineThickness);
            if((topEnd - lowEnd < 21050 && scale500Hz<0.0f)  || scale2000Hz<0.0f || scale4000Hz>1.0f)
                g.drawText("3k",    margXLeft-30.0f + (scale3000Hz*_winX),   getHeight()-margYBot, 60, 20, Justification::centred);
        }
        
        if(scale4000Hz <1.0f && scale4000Hz > 0.0f) {
            g.drawLine((scale4000Hz * _winX)+margXLeft, margYTop, (scale4000Hz * _winX)+margXLeft, margYTop+ _winY, altLineThickness);
            if((topEnd - lowEnd < 21050 && scale500Hz<0.0f)  || scale3000Hz<0.0f || scale5000Hz>1.0f)
                g.drawText("4k",    margXLeft-30.0f + (scale4000Hz*_winX),    getHeight()-margYBot, 60, 20, Justification::centred);
        }
        
        if(scale5000Hz <1.0f && scale5000Hz > 0.0f) {
            g.drawLine((scale5000Hz * _winX)+margXLeft, margYTop, (scale5000Hz * _winX)+margXLeft, margYTop+ _winY, altLineThickness);
            if((topEnd - lowEnd < 21050 && scale500Hz<0.0f)  || scale4000Hz<0.0f || scale6000Hz>1.0f)
                g.drawText("5k",    margXLeft-30.0f + (scale5000Hz*_winX),    getHeight()-margYBot, 60, 20, Justification::centred);
        }
        
        if(scale6000Hz <1.0f && scale6000Hz > 0.0f) {
            g.drawLine((scale6000Hz * _winX)+margXLeft, margYTop, (scale6000Hz * _winX)+margXLeft, margYTop+ _winY, altLineThickness);
            if((topEnd - lowEnd < 21050 && scale500Hz<0.0f)  || scale5000Hz<0.0f || scale7000Hz>1.0f)
                g.drawText("6k",    margXLeft-30.0f + (scale6000Hz*_winX),    getHeight()-margYBot, 60, 20, Justification::centred);
        }
        
        if(scale7000Hz <1.0f && scale7000Hz > 0.0f) {
            g.drawLine((scale7000Hz * _winX)+margXLeft, margYTop, (scale7000Hz * _winX)+margXLeft, margYTop+ _winY, altLineThickness);
            if((topEnd - lowEnd < 21050 && scale500Hz<0.0f)  || scale6000Hz<0.0f || scale8000Hz>1.0f)
                g.drawText("7k",    margXLeft-30.0f + (scale7000Hz*_winX),    getHeight()-margYBot, 60, 20, Justification::centred);
        }
        
        if(scale8000Hz <1.0f && scale8000Hz > 0.0f) {
            g.drawLine((scale8000Hz * _winX)+margXLeft, margYTop, (scale8000Hz * _winX)+margXLeft, margYTop+ _winY, altLineThickness);
            if((topEnd - lowEnd < 21050 && scale500Hz<0.0f)  || scale7000Hz<0.0f || scale10000Hz>1.0f)
                g.drawText("8k",    margXLeft-30.0f + (scale8000Hz*_winX),    getHeight()-margYBot, 60, 20, Justification::centred);
        }
        
        if(scale10000Hz <1.0f && scale10000Hz > 0.0f) {
            g.drawLine((scale10000Hz * _winX)+margXLeft, margYTop, (scale10000Hz * _winX)+margXLeft, margYTop+ _winY, lineThickness);
            g.drawText("10k",    margXLeft-30.0f + (scale10000Hz*_winX),    getHeight()-margYBot, 60, 20, Justification::centred);
        }
        
        if(scale20000Hz <1.0f && scale20000Hz > 0.0f) {
            g.drawLine((scale20000Hz * _winX)+margXLeft, margYTop, (scale20000Hz * _winX)+margXLeft, margYTop+ _winY, lineThickness);
            g.drawText("20k",   margXLeft-30.0f + (scale20000Hz*_winX),   getHeight()-margYBot, 60, 20, Justification::centred);
        }
        
        g.setColour(Colours::lightyellow);
        if(scaleNyquist <=1.0f && scaleNyquist >= 0.0f) {
            g.drawLine((scaleNyquist * _winX)+margXLeft, margYTop, (scaleNyquist * _winX)+margXLeft, margYTop+ _winY);
            g.drawText("N",     margXLeft-30.0f + (scaleNyquist*_winX),  margYTop-20,          60, 20, Justification::centredBottom);
        }
        
    //    g.setColour(Colours::indianred);
    //    if(scaleVIII <= 1.0f) {
    //        g.drawLine((scaleVIII * _winX)+margXLeft, margYTop, (scaleVIII * _winX)+margXLeft, margYTop+ _winY);
    //        g.drawText("sr",    12.0f + (scaleVIII*_winX), margYTop-20,          60, 20, Justification::centredBottom);
    //        sampRatMark = sampRat/1000;
    //        g.drawText((String)sampRatMark + "k",    12.0f   + (scaleVIII*_winX), getHeight()-margYBot, 60, 20, Justification::centred);
    //    }
        
        
        g.setColour(Colours::lightblue);
        g.drawLine(margXLeft+_winX, margYTop, margXLeft+_winX, margYTop+ _winY);
        
        //Horizontal lines
        for (int i=0; i<5; i++) {
            g.drawLine(margXLeft-4, ((float)i*_winY/4.0f)+margYTop, margXLeft+_winX, ((float)i*_winY/4.0f)+margYTop);
        }
        
        
        g.drawText( " 24dB",   margXLeft-47, (0*_winY/4.0f)+margYTop-9,  40, 20, Justification::right);
        g.drawText( "  0dB",   margXLeft-47, (1*_winY/4.0f)+margYTop-9,  40, 20, Justification::right);
        g.drawText( "-24dB",   margXLeft-47, (2*_winY/4.0f)+margYTop-9,  40, 20, Justification::right);
        g.drawText( "-48dB",   margXLeft-47, (3*_winY/4.0f)+margYTop-9,  40, 20, Justification::right);
        g.drawText( "-72dB",   margXLeft-47, (4*_winY/4.0f)+margYTop-9,  40, 20, Justification::right);
    }
    
    g.setColour (Colours::grey);
    g.drawRect (getLocalBounds(), 1);
}

void Display_Logarithmic::resized()
{
    wZoom.setBounds(margXLeft-11, getHeight()-33, getWidth()-(margXLeft-11), 30);
}

int Display_Logarithmic::getDisplayHeight()
{
    return getHeight()-margYBot-margYTop;
}

int Display_Logarithmic::getDisplayWidth()
{
    return getWidth()-margXLeft-margXRight;
}

int Display_Logarithmic::getDisplayMargXLeft()
{
    return margXLeft;
}

int Display_Logarithmic::getDisplayMargYTop()
{
    return margYTop;
}

void Display_Logarithmic::setNyquist(double nyquistFreq)
{
    wNyquist = nyquistFreq;
    topEnd = wNyquist;
    wZoom.setRange(-0.0001, wNyquist, 0.01);
//        wZoom.setSkewFactorFromMidPoint(440.0);
    
    wZoom.setMinAndMaxValues(200.0, wNyquist, dontSendNotification);
    aPlusMinus = (wZoom.getMaxValue() - wZoom.getMinValue()) / 2.0f;
    wZoom.setValue( ((wZoom.getMaxValue()-wZoom.getMinValue())/2.0) + wZoom.getMinValue(), dontSendNotification );
    middlThumb = wZoom.getValue();

    sliderValueChanged(&wZoom);
}

void Display_Logarithmic::sliderValueChanged (Slider *slider)
{
    if(slider == &wZoom)
    {
        aPlusMinus = (wZoom.getMaxValue() - wZoom.getMinValue()) / 2.0f;

        if (wZoom.getThumbBeingDragged() == 1 || wZoom.getThumbBeingDragged() == 2) {
            wZoom.setValue(((wZoom.getMaxValue() - wZoom.getMinValue()) / 2.0) + wZoom.getMinValue(), dontSendNotification);
        }
        else
        {
            if      (wZoom.getMinValue() <= wZoom.getMinimum() && wZoom.getValue()<middlThumb) {
                wZoom.setValue(middlThumb, dontSendNotification);
                return;
            }
            else if (wZoom.getMaxValue() >= wZoom.getMaximum()-0.01 && wZoom.getValue()>middlThumb) {
                wZoom.setValue(middlThumb, dontSendNotification);
                return;
            }
            else {
                wZoom.setMinAndMaxValues(wZoom.getValue() - aPlusMinus, wZoom.getValue() + aPlusMinus, dontSendNotification);
            }
        }
        
        middlThumb = wZoom.getValue();

        lowEnd = pow(10.0, wZoom.getMinValue()*log10(22050.0)/22050.0);
        topEnd = pow(10.0, wZoom.getMaxValue()*log10(22050.0)/22050.0);
        
        repaint();
        graphAnalyser->setZoomLogar(lowEnd, topEnd);

    }
}

void Display_Logarithmic::whatToDisplay(GraphAnalyser &graph)
{
    graphAnalyser = &graph;
}
