#include "AudioSFX.hpp"

AudioSFX::AudioSFX(string soundPath, string name) {
    this->soundPath = soundPath;
    this->name = name;
    this->soundBuffer = new SoundBuffer();
    this->sound = new Sound();
}

AudioSFX::~AudioSFX() {
    delete soundBuffer;
    delete sound;
}

void AudioSFX::load() {
    if(soundBuffer->loadFromFile(soundPath)) {
        sound->setBuffer(*soundBuffer);
    } else {
        throw runtime_error("Error while loading sound : " + getSoundPath());
    }

}

void AudioSFX::play() {
    this->sound->play();
}

string AudioSFX::getName() {
    return this->name;
}

string AudioSFX::getSoundPath() {
    return this->soundPath;
}

SoundBuffer* AudioSFX::getSoundBuffer() {
    return this->soundBuffer;
}

Sound* AudioSFX::getSound() {
    return this->sound;
}

void AudioSFX::setName(string name) {
    this->name = name;
}

void AudioSFX::setSoundPath(string soundPath) {
    this->soundPath = soundPath;
}

void AudioSFX::setSoundBuffer(SoundBuffer* soundBuffer) {
    this->soundBuffer = soundBuffer;
}

void AudioSFX::setSound(Sound* sound) {
    this->sound = sound;
}

bool AudioSFX::operator==(const AudioSFX& sfx) {
    if(this->name == sfx.name) {
        return true;
    }
    return false;
}