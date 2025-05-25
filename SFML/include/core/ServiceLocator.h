#pragma once
#include "AudioManager.h"

class ServiceLocator {
public:
    static void provide(std::shared_ptr<AudioManager> service) {
        audioService = service;
    }

    static std::shared_ptr<AudioManager> getAudio() {
        return audioService;
    }

private:
    static std::shared_ptr<AudioManager> audioService;
};
