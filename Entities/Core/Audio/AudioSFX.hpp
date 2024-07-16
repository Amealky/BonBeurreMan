//
//  AudioSFX.hpp
//  BonBeurreMan
//
//  Copyright © 2018 Amealky. All rights reserved.
//


#ifndef AudioSFX_hpp
#define AudioSFX_hpp

#include <iostream>
#include <SFML/Audio.hpp>

using namespace std;
using namespace sf;

class AudioSFX {
    public:
        AudioSFX(string soundPath, string name);
        ~AudioSFX();
        
        //Core
        void load();
        void play();

        //Getter
        string getName();
        string getSoundPath();
        SoundBuffer* getSoundBuffer();
        Sound* getSound();

        //Setter
        void setName(string name);
        void setSoundPath(string soundPath);
        void setSoundBuffer(SoundBuffer* soundBuffer);
        void setSound(Sound* sound);

        //Operator
        bool operator==(const AudioSFX& sfx);

    private:
        string name;
        string soundPath;
        SoundBuffer* soundBuffer;
        Sound* sound;

};

#endif