/*
  ==============================================================================

    GraphAnalyser.h
    Created: 9 May 2018 5:56:23pm
    Author:  Wojtek Pilwinski

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "CalculateDTFT.h"

//==============================================================================
/*
*/
class GraphAnalyser    : public Component, public Timer
{
public:
    GraphAnalyser();
    ~GraphAnalyser();
    
    void timerCallback() override;
    
    void setSampleRate(double sample_rate);
    void setNewBufSize(double new_buf_size);
    void setZoomLogar(double lowE, double topE);
    void setZoomLinear(double startTime, double endTime);
    void setLowEndIndex();
    void setFFT_DataSource(CalculateDTFT &fftData);

    void paint (Graphics&) override;
    void resized() override;
    
    void drawLinearGraph();
    void drawLogarGraph3();
    

private:
    Path fftGraph;
    CalculateDTFT *dataSource;
    
    double wSampleRate;
    double newBufferSize;
    double radix2BuffSize;
    double nyquist;
    float maxResolution;
    
    double dispResol;
    double dispLogScale;
    float zero_dB; // position on the displey of 0 dB
    double dispWidth;
    float logScaleWidth1;
    float logNyquist;
    float low_End;
    float low_End_index;
    float top_End;
    float top_End_index;
    float timeStart;
    float timeEnd;
    float linearDivider;
    
public:
    bool isForward;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (GraphAnalyser)
};