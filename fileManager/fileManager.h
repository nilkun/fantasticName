//Open file for reading in binary
#ifndef __FILEMANAGER_H__
#define __FILEMANAGER_H__

#include <SDL2/SDL.h>
#include <vector>
#include <iostream>

class FileManager {
public:
  FileManager();
  ~FileManager();
  SDL_RWops* file;
  bool load(std::string filename);
  void close();
  void openToSave(std::string filename);
  void writeString(std::string &text);
  void readString(std::string &text);
  template <class T> void readData(T &data);
  template <class T> void writeData(T &data);
};

template <class T>void FileManager::readData(T &data) {
  size_t sizeInBytes = sizeof(T);
  size_t objectsInBuffer = 1;
  // filename, target to copy to, size of object, max number of objects to read;
  if(SDL_RWread(file, &data, sizeInBytes, objectsInBuffer)==objectsInBuffer)
    {
      // std::cout << "Read " << objectsInBuffer << " objects with the size of " << sizeInBytes << " bytes." << std::endl;
      // std::cout << "DATA: " << data << std::endl;
    }
    else
    {
      std::cout << "Error loading '" << file << "' Error: " << SDL_GetError() << std::endl;
    }
}

template <class T>void FileManager::writeData(T &data) {
  size_t sizeInBytes = sizeof(T);
  size_t objectsInBuffer = 1;

  // INPUT: file, data buffer, size (in bytes), number of objects
  if(SDL_RWwrite(file, &data, sizeInBytes, objectsInBuffer)==objectsInBuffer)
  {
    // std::cout << "Wrote " << objectsInBuffer << " objects with the size of " << sizeInBytes << "b." << std::endl;
  }
  else
  {
    std::cout << "Error writing file... Error: " << SDL_GetError() << std::endl;
  }
}

#endif
