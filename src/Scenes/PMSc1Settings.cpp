//
//  PMSc1Settings.cpp
//  PMConcertParaules
//
//  Created by Miquel Àngel Soler on 7/10/15.
//
//

#include "PMSc1Settings.hpp"

PMSc1Settings::PMSc1Settings() : PMBaseScene("Scene 1")
{
    ofBackground(150);
    setFade(1000, 1000);
    //setupGUI_SONG();
}

void PMSc1Settings::setup()
{
    
}

void PMSc1Settings::setupGUI_SONG(){
    gui_song = new ofxUISuperCanvas("Welcome to Visual Songs");
    gui_song->addSpacer();
    gui_song->addSpacer();
    vector<string> song_names;
    song_names.push_back("ONhdfjkdshflaksjdhflksajdhflkjashdljfhE");    song_names.push_back("TWO");    song_names.push_back("THREE");    song_names.push_back("FOUR");    song_names.push_back("FIVE");
    gui_song->setWidgetFontSize(OFX_UI_FONT_SMALL);
    ddl = gui_song->addDropDownList("CHOSE YOUR SONG", song_names);
    ddl->setAllowMultiple(false);
    ddl->setAutoClose(true);
    gui_song->autoSizeToFitWidgets();
    gui_song->setDrawWidgetPadding(true);
    //gui_song->set
    ofAddListener(gui_song->newGUIEvent, this, &PMSc1Settings::guiEvent);
}

void PMSc1Settings::update()
{
    
}

void PMSc1Settings::draw()
{
    
}

void PMSc1Settings::guiEvent(ofxUIEventArgs &e)
{
    
}

