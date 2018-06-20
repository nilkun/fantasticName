*************************************************
Game Engine with a Fantastic Name v0.5.1
2018 Nilkun	(alpha)
*************************************************

A game engine for SDL2.

It currently has functions to create textures from images, fonts, text, et.c.

Some functions might not be documented here.


The structure is as follows:

/creatorTools
  * tools to create textures
  * Has the following classes and functions:
      class FontAtlas
        * holds a font texture and index
      class TextureCreator {
        setColor()
          * Sets the color of the texture (when creating from fonts)
        fromImage()
          * Creates texture from image
        fromFontToText()
          * Creates texture from text (on the fly font)
        filledRectangle()
          * Creates a filled rectangle
        createFontAtlas()
          * Creates a font atlas
        fromAtlasToText()
          * Renders text to one line by using an atlas
        fromAtlasToTextbox()
          * Renders text to multiple rows from vector of strings

/events
  * handles events

/resources
  * place to put images and fonts

/window
  * handles everything related to the window
  * Has the following classes and functions:
      class Screen {
        std::vector<Viewport> viewports;
          * controls the viewports
        Screen();
        Screen(const char* title, int width, int height);
          * constructors
        void init();
        void close();
          * quite self explanatory
        SDL_Renderer* getRenderer();
          * to get hold of the renderer
        Viewport* addViewport() ;
        Viewport* addViewport(SDL_Rect &position);
          * adding viewport functions
        void clear();
          * clears the screen
        void render();
          * renders all viewports
