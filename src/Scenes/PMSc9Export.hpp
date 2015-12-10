//
//  PMSc9Export.hpp
//  PMCancons_Visuals
//
//  Created by Eduard Frigola on 30/10/15.
//
//

#ifndef PMSc9Export_hpp
#define PMSc9Export_hpp

#include "PMBaseScene.hpp"

#endif /* PMSc9Export_hpp */

class PMSc9Export : public PMBaseScene
{
public:
    
    PMSc9Export();
    
    void setup();
    void update();
    void draw();
    void exit(){};
    void updateEnter(){PMBaseScene::updateEnter();};
    void updateExit(){PMBaseScene::updateExit();};
    
    void keyPressed(int key);

    
private:
    
    ofImage     plantilla;
    ofTrueTypeFont bigFont, smallFont;
    string  textInput;
    float   timestamp;
    bool isSlash;
};