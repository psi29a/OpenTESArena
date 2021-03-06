#include <cassert>
#include <map>

#include "TextureFile.h"

#include "TextureName.h"
#include "TextureSequenceName.h"

// The filename of each TextureName, by type.
const std::map<TextureName, std::string> TextureFilenames =
{
	// Cursors.
	{ TextureName::QuillCursor, "POINTER.IMG" },
	{ TextureName::SwordCursor, "ARENARW.IMG" },

	// Equipment overlays.
	{ TextureName::FemaleNonMagicShirt, "FSSHIRT.IMG" },
	{ TextureName::FemaleMagicShirt, "FRSHIRT.IMG" },
	{ TextureName::FemalePants, "FPANTS.IMG" },
	{ TextureName::MaleNonMagicShirt, "MSSHIRT.IMG" },
	{ TextureName::MaleMagicShirt, "MRSHIRT.IMG" },
	{ TextureName::MalePants, "MPANTS.IMG" },

	// Fonts.
	{ TextureName::FontA, "fonts/font_a" },
	{ TextureName::FontArena, "fonts/arena_font" },
	{ TextureName::FontB, "fonts/font_b" },
	{ TextureName::FontC, "fonts/font_c" },
	{ TextureName::FontChar, "fonts/char_font" },
	{ TextureName::FontD, "fonts/font_d" },
	{ TextureName::FontFour, "fonts/font_4" },
	{ TextureName::FontS, "fonts/font_s" },
	{ TextureName::FontTeeny, "fonts/teeny_font" },

	// Interface.
	{ TextureName::CharacterCreation, "interface/character_creation" },
	{ TextureName::CharacterEquipment, "EQUIP.IMG" },
	{ TextureName::CharacterStats, "CHARSTAT.IMG" },
	{ TextureName::CompassFrame, "COMPASS.IMG" },
	{ TextureName::CompassSlider, "SLIDER.IMG" },	
	{ TextureName::GameWorldInterface, "P1.IMG" },
	{ TextureName::Icon, "interface/icon" },
	{ TextureName::IntroTitle, "TITLE.IMG" },
	{ TextureName::IntroQuote, "QUOTE.IMG" },
	{ TextureName::MainMenu, "MENU.IMG" },
	{ TextureName::ParchmentBig, "PARCH.IMG" },
	{ TextureName::ParchmentPopup, "interface/parchment/parchment_popup" },
	{ TextureName::PauseBackground, "OP.IMG" },
	{ TextureName::PopUp, "POPUP.IMG" }, // I think this is what ChooseClassPanel should use.
	{ TextureName::PopUp11, "POPUP11.IMG" },
	{ TextureName::UpDown, "UPDOWN.IMG" },
	{ TextureName::YesNoCancel, "YESNO.IMG" },

	// Main quest dungeon splash screens.
	{ TextureName::CryptOfHeartsSplash, "CRYPT.IMG" },
	{ TextureName::CrystalTowerSplash, "TOWER.IMG" },
	{ TextureName::DagothUrSplash, "DAGOTHUR.IMG" },
	{ TextureName::EldenGroveSplash, "GROVE.IMG" },
	{ TextureName::FangLairSplash, "FANGLAIR.IMG" },
	{ TextureName::HallsOfColossusSplash, "COLOSSUS.IMG" },
	{ TextureName::LabyrinthianSplash, "LABRINTH.IMG" },
	{ TextureName::MurkwoodSplash, "MIRKWOOD.IMG" },

	// Maps.
	{ TextureName::BlackMarshMap, "BLAKMRSH.IMG" },
	{ TextureName::ElsweyrMap, "ELSWEYR.IMG" },
	{ TextureName::HammerfellMap, "HAMERFEL.IMG" },
	{ TextureName::HighRockMap, "HIGHROCK.IMG" },
	{ TextureName::ImperialProvinceMap, "IMPERIAL.IMG" },
	{ TextureName::MorrowindMap, "MOROWIND.IMG" },
	{ TextureName::SkyrimMap, "SKYRIM.IMG" },
	{ TextureName::SummersetIsleMap, "SUMERSET.IMG" },
	{ TextureName::ValenwoodMap, "VALNWOOD.IMG" },
	{ TextureName::WorldMap, "TAMRIEL.IMG" },
};

// The filename prefix of each TextureSequenceName (with sub-folders). When looking
// for files in the sequence, "-#" will be appended to the name for the number of
// the file, with more numbers added as needed.
const std::map<TextureSequenceName, std::string> TextureSequenceFilenames =
{
	// Interface.
	{ TextureSequenceName::IntroBook, "interface/intro/intro" },
	{ TextureSequenceName::IntroStory, "interface/intro_story/intro_story" },
	{ TextureSequenceName::OpeningScroll, "interface/scroll/scroll" },
	{ TextureSequenceName::NewGameStory, "interface/new_game_story/new_game_story" },
	{ TextureSequenceName::Silmane, "interface/silmane/silmane" },
};

// The number of images in each texture sequence. I think these numbers are necessary
// without doing some directory counting, and that sounds like a bad idea, with all
// the possible mix-ups with text files lying around and duplicates and such.
// These could be parsed in from a text file, but it's not necessary.
const std::map<TextureSequenceName, int> TextureSequenceCounts =
{
	// Interface.
	{ TextureSequenceName::IntroBook, 75 },
	{ TextureSequenceName::IntroStory, 3 },
	{ TextureSequenceName::OpeningScroll, 49 },
	{ TextureSequenceName::NewGameStory, 9 },
	{ TextureSequenceName::Silmane, 19 },
};

std::vector<TextureSequenceName> TextureFile::getSequenceNames()
{
	std::vector<TextureSequenceName> names;
	for (const auto &pair : TextureSequenceFilenames)
	{
		names.push_back(pair.first);
	}

	return names;
}

std::string TextureFile::fromName(TextureName textureName)
{
	auto filename = TextureFilenames.at(textureName);
	return filename;
}

std::vector<std::string> TextureFile::fromName(TextureSequenceName sequenceName)
{
	const auto &filename = TextureSequenceFilenames.at(sequenceName);
	const int &count = TextureSequenceCounts.at(sequenceName);

	std::vector<std::string> filenames;

	// Generate the list of filenames to load from file later.
	for (int i = 0; i < count; ++i)
	{
		auto countString = "-" + std::to_string(i + 1);
		filenames.push_back(filename + countString);
	}

	return filenames;
}
