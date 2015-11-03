//
//  PMColorContainer.cpp
//  PMCancons_Visuals
//
//  Created by Eduard Frigola on 02/11/15.
//
//

#include "PMColorContainer.hpp"


PMColorContainer::PMColorContainer(int _x, int _y, int _width, int _height, ofColor _color)
{
    this->color=_color;
    this->x=_x;
    this->y=_y;
    this->width=_width;
    this->height=_height;
}

void PMColorContainer::draw()
{
    ofPushMatrix();
        ofSetRectMode(OF_RECTMODE_CENTER);
        ofSetColor(color);
        ofDrawRectRounded(x, y, width, height, 2);
    ofPopMatrix();
}

void PMColorContainer::setColor(ofColor _color)
{
    color=_color;
}