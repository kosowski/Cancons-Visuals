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

#define ENABLE_SOUNDFLOWER false
#define ENABLE_KINECT false
#define ENABLE_MULTIPLE_FBOS false
#define ENABLE_MULTILAYER_EXPORT false


static const float          WINDOW_SCALE_FACTOR         = 0.5;
static const float          FBO_SCALE_FACTOR            = 1.0f;

static const int            WINDOW_WIDTH                = 1080;
static const int            WINDOW_HEIGHT               = 1920;

static const int            DEFAULT_WINDOW_WIDTH        = int(float(WINDOW_WIDTH) * WINDOW_SCALE_FACTOR);
static const int            DEFAULT_WINDOW_HEIGHT       = int(float(WINDOW_HEIGHT) * WINDOW_SCALE_FACTOR);

#if ENABLE_MULTIPLE_FBOS
static const int            FBO_WIDTH                   = int(float(WINDOW_WIDTH) * FBO_SCALE_FACTOR);
static const int            FBO_HEIGHT                  = int(float(WINDOW_HEIGHT) * FBO_SCALE_FACTOR);
#else
static const int            FBO_WIDTH                   = int(float(WINDOW_WIDTH) * FBO_SCALE_FACTOR);
static const int            FBO_HEIGHT                  = int(float(WINDOW_HEIGHT) * FBO_SCALE_FACTOR);
#endif

static const ofWindowMode   DEFAULT_WINDOW_MODE         = OF_WINDOW;

static const int            DEFAULT_SAMPLERATE          = 44100;
static const int            DEFAULT_BUFFERSIZE          = 512;

#endif
