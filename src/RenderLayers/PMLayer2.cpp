//
// Created by Miquel Àngel Soler on 4/12/15.
//

#include "PMLayer2.h"

static const float Z_SIZE_OFFSET  = 1;
static const float Z_SIZE_FACTOR = 10;

PMLayer2::PMLayer2(int _fboWidth, int _fboHeight, KinectNodeType _kinectNodeType) : PMBaseLayer(_fboWidth, _fboHeight, _kinectNodeType)
{
    layerID = 2;
}

void PMLayer2::setup(ofPoint initialPosition)
{
    PMBaseLayer::setup(initialPosition);
}

void PMLayer2::update()
{
    PMBaseLayer::update();
#if ENABLE_KINECT
    int newBrushSize = int((((nodeInitialZ-kinectNodeData.z)*Z_SIZE_FACTOR)+Z_SIZE_OFFSET)*BRUSH_MAX_SIZE);
    if(newBrushSize>BRUSH_MIN_SIZE)
        setBrushSize(newBrushSize);
#endif
}

void PMLayer2::draw()
{
    PMBaseLayer::draw();
}

#pragma mark - Audio Events

void PMLayer2::pitchChanged(pitchParams &pitchParams)
{
}

void PMLayer2::energyChanged(energyParams &energyParams)
{
}

void PMLayer2::silenceStateChanged(silenceParams &silenceParams)
{
}

void PMLayer2::pauseStateChanged(pauseParams &pauseParams)
{
}

void PMLayer2::onsetDetected(onsetParams &onsetParams)
{
}

void PMLayer2::shtDetected(shtParams &shtParams)
{
}

void PMLayer2::melodyDirection(melodyDirectionParams &melodyDirectionParams)
{
}

void PMLayer2::melBandsChanged(melBandsParams &melBandsParams)
{
    float myEnergy = melBandsParams.bandsEnergy[2];
    brushAlpha = ofMap(myEnergy, 0.0, bandMaxEnergy, brushMinAlpha, brushMaxAlpha, true);

//    cout << "Brush Alpha L2> En:" << myEnergy << " Alpha: " << brushAlpha << endl;
}
