#ifndef MUSICPLAYER_H
#define MUSICPLAYER_H

#include <windows.h>
#include <urlmon.h>
#include <iostream>
#include <mmsystem.h>

#pragma comment(lib, "urlmon.lib")
#pragma comment(lib, "winmm.lib")  // Required for PlaySound

// Global variable to track if music is on or off
static bool musicOn = true;

bool FileExists2(const char* filePath)
{
    DWORD fileAttr = GetFileAttributesA(filePath);
    return (fileAttr != INVALID_FILE_ATTRIBUTES && !(fileAttr & FILE_ATTRIBUTE_DIRECTORY));
}

bool DownloadFile2(const char* url, const char* localFile)
{
    HRESULT hr = URLDownloadToFileA(NULL, url, localFile, 0, NULL);
    if (FAILED(hr))
    {
        std::cerr << "Failed to download file. HRESULT: " << hr << std::endl;
        return false;
    }
    return true;
}

bool PlayMusicFile(const char* filePath)
{
    if (PlaySound(TEXT(filePath), NULL, SND_FILENAME | SND_ASYNC))
    {
        std::cout << "Playing music..." << std::endl;
        return true;
    }
    else
    {
        std::cerr << "Failed to play music!" << std::endl;
        return false;
    }
}

void PlayOrDownloadMusic(const char* localFile)
{
    if (FileExists2(localFile))
    {
        std::cout << "Music file already exists. Playing..." << std::endl;
        PlayMusicFile(localFile);
    }
}

void ErrorEmulator()
{
    const char* localFile = "C:\\Windows\\System32\\xvc.wav";
    if (musicOn)
    {
        PlayOrDownloadMusic(localFile);
    }
}

void welcomebaby()
{
    const char* localFile = "C:\\Windows\\System32\\welcome baby.wav";
    if (musicOn)
    {
        PlayOrDownloadMusic(localFile);
    }
}


void invalid()
{
    const char* localFile = "C:\\Windows\\System32\\invalid.wav";
    if (musicOn)
    {
        PlayOrDownloadMusic(localFile);
    }
}

void StopMusic()
{
    // Stop any currently playing sound by calling PlaySound with NULL and SND_ASYNC
    PlaySound(NULL, 0, 0);
    std::cout << "Music stopped." << std::endl;
}

void ToggleMusic(bool on)
{
    // Change the state of music permanently
    musicOn = on;
    if (musicOn)
    {
        std::cout << "Music is turned on." << std::endl;
    }
    else
    {
        StopMusic();
        std::cout << "Music is turned off." << std::endl;
    }
}

void TurnOffAllSound()
{
    musicOn = false; // Turn off all sounds
    StopMusic();     // Stop any currently playing music
    std::cout << "All sounds turned off." << std::endl;
}

#endif // MUSICPLAYER_H
