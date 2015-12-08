//
//  Config.h
//  ConductrEnter
//
//  Created by Miquel �ngel Soler on 5/6/15.
//
//

#pragma once

#ifndef ConductrEnter_Config_h
#define ConductrEnter_Config_h

#define ENABLE_SOUNDFLOWER true
#define ENABLE_KINECT true

static const float          WINDOW_SCALE_FACTOR         = 0.5f;
static const float          FBO_SCALE_FACTOR            = 3.0f;

static const int            WINDOW_WIDTH                = 1080;
static const int            WINDOW_HEIGHT               = 1920;

static const int            DEFAULT_WINDOW_WIDTH        = int(float(WINDOW_WIDTH) * WINDOW_SCALE_FACTOR);
static const int            DEFAULT_WINDOW_HEIGHT       = int(float(WINDOW_HEIGHT) * WINDOW_SCALE_FACTOR);

static const int            FBO_WIDTH                   = int(float(WINDOW_WIDTH) * FBO_SCALE_FACTOR);
static const int            FBO_HEIGHT                  = int(float(WINDOW_HEIGHT) * FBO_SCALE_FACTOR);

static const ofWindowMode   DEFAULT_WINDOW_MODE         = OF_WINDOW;

static const int            DEFAULT_SAMPLERATE          = 44100;
static const int            DEFAULT_BUFFERSIZE          = 512;

#endif
