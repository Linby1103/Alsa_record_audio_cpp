#ifndef ALSACAPTUREAUDIO_H
#define ALSACAPTUREAUDIO_H
#include <alsa/asoundlib.h>
#include <signal.h>


class AlsaCaptureAudio
{
    public:
    AlsaCaptureAudio();
    int initAudioCapture();
    void captureAudio();
    void closeCapture();
  ~AlsaCaptureAudio();

    protected:
        int rc;
        int size;
        snd_pcm_t *handle;
        snd_pcm_hw_params_t *params;
        unsigned int sample_rate;
        int dir;
        snd_pcm_uframes_t frames;
        char *buffer;
        FILE* pFile;
};
#endif 