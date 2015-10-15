//
//  PMDeviceAudioAnalyzer.cpp
//  ConcertParaules
//
//  Created by Miquel Àngel Soler on 25/9/15.
//
//

#include "PMDeviceAudioAnalyzer.hpp"

///--------------------------------------------------------------
PMDeviceAudioAnalyzer::PMDeviceAudioAnalyzer(ofBaseApp *app, int _deviceID, int _inChannels, int _outChannels, int _sampleRate, int _bufferSize)
{
    deviceID = _deviceID;
    inChannels = _inChannels;
    outChannels = _outChannels;
    sampleRate = _sampleRate;
    bufferSize = _bufferSize;
//    numBuffers = _numBuffers;
    numBuffers = bufferSize/64;

    soundStream.printDeviceList();

    soundStream.setDeviceID(deviceID);
    cout << "Device Id: " << deviceID << endl;
    cout << "Setup: " << app << ", " << outChannels << ", " << inChannels << ", " << sampleRate << ", " << bufferSize << ", " << numBuffers << endl;

    isSetup = false;
}

///--------------------------------------------------------------
PMDeviceAudioAnalyzer::~PMDeviceAudioAnalyzer()
{
    for (int i=0; i<inChannels; i++)
        delete buffers[i];
    delete []buffers;

    for (unsigned int i=0; i<audioAnalyzers.size(); i++)
        delete audioAnalyzers[i];
    audioAnalyzers.clear();
}

///--------------------------------------------------------------
void PMDeviceAudioAnalyzer::setup(PMDAA_ChannelMode _channelMode, int _channelNumber)
{
    if (isSetup) return;

    channelMode = _channelMode;
    channelNumber = (channelMode == PMDAA_CHANNEL_MONO) ? _channelNumber : -1;

    int numUsedChannels = (channelMode == PMDAA_CHANNEL_MONO) ? 1 : inChannels;

    // Creation of audio in buffers
    // Buffer matrix:
    // - Rows: channels
    // - Cols: channel buffer

    buffers = new float *[numUsedChannels];
    for (int i=0; i<numUsedChannels; i++)
        buffers[i] = new float[bufferSize];

    // ofxAudioAnalyzer(s) setup

    for (int i=0; i<numUsedChannels; i++)
    {
        ofxAudioAnalyzer *analyzer = new ofxAudioAnalyzer();
        analyzer->setup(bufferSize, sampleRate);

        audioAnalyzers.push_back(analyzer);
    }

    isSetup = true;
}

///--------------------------------------------------------------
void PMDeviceAudioAnalyzer::start()
{
    soundStream.stop();

    soundStream.setup(outChannels, inChannels, sampleRate, bufferSize, numBuffers);
    soundStream.setInput(this);
}

///--------------------------------------------------------------
void PMDeviceAudioAnalyzer::stop()
{
    soundStream.stop();
}

///--------------------------------------------------------------
void PMDeviceAudioAnalyzer::audioIn(float *input, int bufferSize, int nChannels)
{
    int numUsedChannels = (channelMode == PMDAA_CHANNEL_MONO) ? 1 : inChannels;

    // Parse input array
    for (int i=0; i<numUsedChannels; ++i)
        for (int j=0; j<bufferSize; j++)
            buffers[i][j] = input[i + (nChannels * j)];

    pitchParams pitchParams;
    pitchParams.deviceID = deviceID;

    onsetParams onsetParams;
    onsetParams.deviceID = deviceID;

    for (int i=0; i<numUsedChannels; i++)
    {
        audioAnalyzers[i]->analyze(buffers[i], bufferSize);

        // Pitch
        pitchParams.channel = (channelMode == PMDAA_CHANNEL_MONO) ? channelNumber : i;
        pitchParams.freq = audioAnalyzers[i]->getPitchFreq();
        pitchParams.midiNote = 0;
        pitchParams.midiNoteNoOctave = 0;
        ofNotifyEvent(eventPitchChanged, pitchParams, this);

        cout << "CH" << pitchParams.channel << " - Pitch freq:" << audioAnalyzers[i]->getPitchFreq() << endl;

        // Onset
        if (audioAnalyzers[i]->getIsOnset())
        {
            onsetParams.channel = (channelMode == PMDAA_CHANNEL_MONO) ? channelNumber : i;
            cout << "CH" << onsetParams.channel << " - Onset!" << endl;
            ofNotifyEvent(eventOnsetDetected, onsetParams, this);
        }
    }
}