#ifndef TEXTURE_MANAGER_H
#define TEXTURE_MANAGER_H

#include <array>
#include <map>
#include <string>

#include "Color.h"

// The behavior of this class might be changing to work with BSA parsing and
// associated files.

// When loading wall and sprite textures from file, use a texture name parser or
// something that produces a texture/index -> filename mapping. Each of those would 
// get a unique integer ID either before or during parsing (perhaps depending on 
// the order they were parsed). Perhaps the ID could be their offset in GLOBAL.BSA.

class Surface;

struct SDL_PixelFormat;
struct SDL_Surface;

class TextureManager
{
private:
	typedef std::array<Color, 256> Palette;

	static const std::string PATH;

	Palette palette;
	std::map<std::string, Surface> surfaces;
	const SDL_PixelFormat *format;

    SDL_Surface *loadPNG(const std::string &fullPath);
	SDL_Surface *loadIMG(const std::string &fullPath);
public:
	TextureManager(const SDL_PixelFormat *format);
	~TextureManager();

	const SDL_PixelFormat *getFormat() const;

	// The filename given here is a partial path that excludes the "data/textures/" 
	// path and the texture extension (.png); both known only to the texture manager. 
	// A valid filename might be "interface/folder/some_image".
	const Surface &getSurface(const std::string &filename);

	// Set the currently used palette (default is PAL.COL).
	void setPalette(const std::string &paletteName);

	// Since cinematics are now loaded image by image instead of all at the same time,
	// there may be some stuttering that occurs. This method loads all of the sequences
	// into memory at the same time to compensate.
	void preloadSequences();
};

#endif
