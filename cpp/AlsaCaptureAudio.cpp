#include "AlsaCaptureAudio.h"


static int recording;
void stop_recording(int param)
{
    recording = 0;
}
AlsaCaptureAudio::AlsaCaptureAudio()
{
    pFile = fopen("test.pcm", "wb");
    initAudioCapture();
}    
AlsaCaptureAudio::~AlsaCaptureAudio()
{
    //析构函数自动调用 释放资源
    closeCapture();
}
//初始化
int AlsaCaptureAudio::initAudioCapture()
{
    //Open PCM device for recording(capture)
    rc = snd_pcm_open(&handle, "default", SND_PCM_STREAM_CAPTURE, 0);
    if (rc < 0)
    {
        fprintf(stderr, "unable to open pcm device: %s\n", snd_strerror(rc));
        return rc;
    }
    printf("open success\n");
    //Allocate a hardware parameters object
    snd_pcm_hw_params_alloca(&params);
    //Fill it in with default values
    snd_pcm_hw_params_any(handle, params);
    //Interleaved mode
    snd_pcm_hw_params_set_access(handle, params, SND_PCM_ACCESS_RW_INTERLEAVED);
    //Signed 16-bit little-endian format 16位小端模式
    snd_pcm_hw_params_set_format(handle, params, SND_PCM_FORMAT_S16_LE);
    //Two channels 双通道
    snd_pcm_hw_params_set_channels(handle, params, 2);
    //44100 bits/sencod sampling rate (CD quality)比特率
    sample_rate = 44100;
    snd_pcm_hw_params_set_rate_near(handle, params, &sample_rate, &dir);
    //Set period size to 32 frames
    frames = 32;
    snd_pcm_hw_params_set_period_size_near(handle, params, &frames, &dir);
    //write the parameters to the driver
    rc = snd_pcm_hw_params(handle, params);
    if (rc < 0)
    {
        fprintf(stderr, "unable to set hw parameters: %s\n", snd_strerror(rc));
        return rc;
    }
    printf("write params success\n");

    //Use a buffer large enough to hole one period
    snd_pcm_hw_params_get_period_size(params, &frames, &dir);

    //16-bits  two channels  so *4
    size = frames * 4;
    buffer = (char *)malloc(size);

    //We want to loop for 5 seconds
    snd_pcm_hw_params_get_period_time(params, &sample_rate, &dir);

    return 1;
}

//录制音频
void AlsaCaptureAudio::captureAudio()
{
    recording = 1;
    while (recording)
    {
        //capture data
        rc = snd_pcm_readi(handle, buffer, frames);
        if (rc == -EPIPE)
        {
            fprintf(stderr, "overrun occurred\n");
            snd_pcm_prepare(handle);
        }else if (rc < 0)
        {
            fprintf(stderr, "error from read: %s\n", snd_strerror(rc));
        }else if (rc != (int)frames)
        {
            fprintf(stderr, "short read, read %d frames\n", rc);
        }
        printf("write to file......%d\n", size);
        //write to stdout
        rc = fwrite(buffer, sizeof(char), size, pFile);
        if (rc != size)
        {
            fprintf(stderr, "short write: wrote %d bytes\n", rc);
        }
        if (signal(SIGINT, stop_recording) == SIG_ERR)
        {
            fprintf(stderr, "signal() failed\n");
        }
    }
}
//释放资源
void AlsaCaptureAudio::closeCapture()
{
    snd_pcm_drain(handle);
    snd_pcm_close(handle);
    free(buffer);
    fclose(pFile);
    printf("closeCapture\n");

}