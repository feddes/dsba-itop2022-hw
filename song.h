#ifndef SONG_H
#define SONG_H

#include <iostream>

struct Song
{
   public:
    std::string title;
    std::string artist;
    int year;
    std::string genre;
    int energy;
    int dance;
    int duration;
};

#endif  // SONG_H
