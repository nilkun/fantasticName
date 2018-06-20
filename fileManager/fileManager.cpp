#include "fileManager.h"

FileManager::FileManager() {
}

FileManager::~FileManager() {
}

bool FileManager::load(std::string filename)
{
  return ((file = SDL_RWFromFile( filename.c_str(), "r+b" ))!=nullptr);
}

void FileManager::writeString(std::string &text)
{
  const char* cstring = text.c_str();
  size_t sizeInBytes = sizeof(char) * strlen(cstring);
  size_t objectsInBuffer = 1;

  // INPUT: file, data buffer, size (in bytes), number of objects
  if(SDL_RWwrite(file, cstring, sizeInBytes, objectsInBuffer)==objectsInBuffer)
  {
    //std::cout << "Wrote " << objectsInBuffer << " characters with the size of " << sizeInBytes << " bytes." << std::endl;
    //std::cout << "String saved: " << cstring << std::endl;
  }
  else
  {
    std::cout << "Error writing file... Error: " << SDL_GetError() << std::endl;
  }

 char zero = '\0';
//
 SDL_RWwrite(file, &zero, 1, 1);

}

void FileManager::readString(std::string &text)
{
  // currently max size 256
  text = "";
  size_t bufferSize = 1;
  char buffer[bufferSize];

  size_t sizeInBytes = sizeof(char);
  size_t objectsInBuffer = 1;

  // filename, target to copy to, size of object, max number of objects to read;
  do
  {
    if(SDL_RWread(file, buffer, sizeInBytes, objectsInBuffer)==objectsInBuffer) {
      text += buffer[0];
    }
    else
    {
      //std::cout << "Error!!! " << SDL_GetError() << std::endl;
    };

  }
  while(buffer[0]!='\0');
  // std::cout << "string loaded: " << text << std::endl;
}


void FileManager::close()
{
  if(file != NULL) SDL_RWclose(file);
}

void FileManager::openToSave(std::string filename) {

  // Load file, or create if needed...
  std::string name = filename;
  file = SDL_RWFromFile( name.c_str(), "r+b" );
  if(file == nullptr) {
    // No such file, so create it
    file = SDL_RWFromFile( name.c_str(), "w+b" );
    if (file==nullptr) std::cout << "Error creating file!" << std::endl;
  }
}
