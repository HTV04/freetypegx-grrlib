/*
 * FreeTypeGX for GRRLIB
 *
 * FreeTypeGX is a wrapper class for libFreeType which renders a compiled
 * FreeType parsable font into a GX texture for Wii homebrew development.
 * Copyright (C) 2008-2010 Armin Tamzarian
 *
 * This file is part of FreeTypeGX.
 *
 * FreeTypeGX is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published
 * by the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * FreeTypeGX is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with FreeTypeGX.  If not, see <http://www.gnu.org/licenses/>.
 */

/** \mainpage FreeTypeGX for GRRLIB
 *
 * \section sec_intro Introduction
 *
 * FreeTypeGX is a wrapper class for libFreeType which renders a compiled FreeType parsable font into a GX texture for Wii homebrew development.
 * <br>
 * FreeTypeGX is written in C++ and makes use of a selectable pre-buffered or buffer-on-demand methodology to allow fast and efficient printing of text to the EFB.
 * <p>
 * This library was developed in-full by Armin Tamzarian with the support of developers in \#wiidev on EFnet. Special thanks go out to Tantric of <a href = "https://github.com/dborth">too much to list</a> and dimok of <a href="https://sourceforge.net/projects/wiixplorer/">WiiXplorer</a> for their performance modifications.
 *
 * \section sec_installation_source Installation (Source Code)
 *
 * -# Ensure that you have GRRLIB installed in your development environment with the library added to your Makefile where appropriate.
 * -# Ensure that you have the FreeType Wii library installed in your development environment with the library added to your Makefile where appropriate.
 * -# Ensure that you have the <a href = "https://github.com/ArminTamzarian/metaphrasis">Metaphrasis</a> library installed in your development environment with the library added to your Makefile where appropriate.
 * -# Extract the FreeTypeGX archive.
 * -# Copy the contents of the <i>src</i> directory into your project's development path.
 * -# Include the FreeTypeGX header file in your code using syntax such as the following:
 * \code
 * #include "FreeTypeGX.h"
 * \endcode
 *
 * \section sec_installation_library Installation (Library)
 *
 * -# Ensure that you have GRRLIB installed in your development environment with the library added to your Makefile where appropriate.
 * -# Ensure that you have the FreeType Wii library installed in your development environment with the library added to your Makefile where appropriate.
 * -# Ensure that you have the <a href = "https://github.com/ArminTamzarian/metaphrasis">Metaphrasis</a> library installed in your development environment with the library added to your Makefile where appropriate.
 * -# Extract the FreeTypeGX archive.
 * -# Copy the contents of the <i>libogc</i> directory into your <i>devKitPro/libogc</i> directory.
 * -# Include the FreeTypeGX header file in your code using syntax such as the following:
 * \code
 * #include "FreeTypeGX.h"
 * \endcode
 *
 * \section sec_freetypegx_prerequisites FreeTypeGX Prerequisites
 *
 * Before you begin using FreeTypeGX in your project you must ensure that the you have some method by which to allocate the font data buffer for use within the initialization routines. For examples showing the most common methods to generate a font data buffer for use with FreeTypeGX see the included examples. These examples illustrate the following methods:
 * \n
 * \li <i>example1</i> - Compiling a font into the executable
 * \li <i>example2</i> - Loading a font from a file located on an SD card or USB drive
 *
 * Note that both of these example result with the creation of the following example variables:
 *
 * \li <i>uint8_t* rursus_compact_mono_ttf</i> - A buffer containing the font data.
 * \li <i>FT_Long rursus_compact_mono_ttf_size</i> - A long value containing the size of the font data buffer in bytes.
 *
 * \section sec_freetypegx_usage FreeTypeGX Usage
 *
 * -# Within the file you included the FreeTypeGX.h header create an instance object of the FreeTypeGX class:
 * \code
 * FreeTypeGX *freeTypeGX = new FreeTypeGX();
 * \endcode
 * Alternately you can specify a texture format to which you would like to render the font characters. Note that the default value for this parameter is GX_TF_RGBA8.
 * \code
 * FreeTypeGX *freeTypeGX = new FreeTypeGX(GX_TF_RGB565);
 * \endcode
 * \n
 * Currently supported textures are:
 * \li <i>GX_TF_I4</i>
 * \li <i>GX_TF_I8</i>
 * \li <i>GX_TF_IA4</i>
 * \li <i>GX_TF_IA8</i>
 * \li <i>GX_TF_RGB565</i>
 * \li <i>GX_TF_RGB5A3</i>
 * \li <i>GX_TF_RGBA8</i>
 *
 * \n
 * -# Using the allocated FreeTypeGX instance object call the loadFont function to load the font from the compiled buffer and specify the desired point size. Note that this function can be called multiple times to load a new:
 * \code
 * freeTypeGX->loadFont(rursus_compact_mono_ttf, rursus_compact_mono_ttf_size, 64);
 * \endcode
 * Alternately you can specify a flag which will load and cache all available font glyphs immediately. Note that on large font sets enabling this feature could take a significant amount of time.
 * \code
 * freeTypeGX->loadFont(rursus_compact_mono_ttf, rursus_compact_mono_ttf_size, 64, true);
 * \endcode
 * \n
 * -# Using the allocated FreeTypeGX instance object call the drawText function to print a string at the specified screen X and Y coordinates to the current EFB:
 * \code
 * freeTypeGX->drawText(10, 25, _TEXT("FreeTypeGX Rocks!"));
 * \endcode
 * Alternately you can specify a color you would like to apply to the printed characters:
 * \code
 * freeTypeGX->drawText(10, 25, _TEXT("FreeTypeGX Rocks!"), 0xffffffff);
 * \endcode
 * Furthermore you can also specify a group of styling parameters which will modify the positioning or style of the text:
 * \code
 * freeTypeGX->drawText(10, 25, _TEXT("FreeTypeGX Rocks!"), 0xffffffff,
 *                      FTGX_JUSTIFY_CENTER | FTGX_ALIGN_BOTTOM | FTGX_STYLE_UNDERLINE);
 * \endcode
 * \n
 * Currently style parameters are:
 * \li <i>FTGX_JUSTIFY_LEFT</i>
 * \li <i>FTGX_JUSTIFY_CENTER</i>
 * \li <i>FTGX_JUSTIFY_RIGHT</i>
 * \li <i>FTGX_ALIGN_TOP</i>
 * \li <i>FTGX_ALIGN_MIDDLE</i>
 * \li <i>FTGX_ALIGN_BOTTOM</i>
 * \li <i>FTGX_STYLE_UNDERLINE</i>
 * \li <i>FTGX_STYLE_STRIKE</i>
 *
 * \section sec_license License
 *
 * FreeTypeGX is distributed under the GNU Lesser General Public License.
 */

#ifndef FREETYPEGX_H_
#define FREETYPEGX_H_

#include <gccore.h>
#include <ft2build.h>
#include FT_FREETYPE_H
#include FT_BITMAP_H
#include "Metaphrasis.h"

#include <malloc.h>
#include <string.h>
#include <map>

/*! \struct ftgxCharData_
 *
 * Font face character glyph relevant data structure.
 */
typedef struct ftgxCharData_ {
	int glyphAdvanceX;	/**< Character glyph X coordinate advance in pixels. */
	unsigned int glyphIndex;	/**< Character glyph index in the font face. */

	int textureWidth;	/**< Texture width in pixels/bytes. */
	int textureHeight;	/**< Texture glyph height in pixels/bytes. */

	int renderOffsetY;	/**< Texture Y axis bearing offset. */
	int renderOffsetMax;	/**< Texture Y axis bearing maximum value. */
	int renderOffsetMin;	/**< Texture Y axis bearing minimum value. */

	uint32_t* glyphDataTexture;	/**< Glyph texture bitmap data buffer. */
} ftgxCharData;

#define _TEXT(t) L ## t /**< Unicode helper macro. */
#define EXPLODE_UINT8_TO_UINT32(x) (x << 24) | (x << 16) | (x << 8) | x

#define FTGX_NULL				0x0000

#define FTGX_JUSTIFY_MASK		0x000f
#define FTGX_JUSTIFY_LEFT		0x0001
#define FTGX_JUSTIFY_CENTER		0x0002
#define FTGX_JUSTIFY_RIGHT		0x0004

#define FTGX_ALIGN_MASK			0x00f0
#define FTGX_ALIGN_TOP			0x0010
#define FTGX_ALIGN_MIDDLE		0x0020
#define FTGX_ALIGN_BOTTOM		0x0040

#define FTGX_STYLE_MASK			0x0f00
#define FTGX_STYLE_UNDERLINE	0x0100
#define FTGX_STYLE_STRIKE		0x0200

#define FTGX_COMPATIBILITY_DEFAULT_TEVOP_GX_MODULATE	0X0001
#define FTGX_COMPATIBILITY_DEFAULT_TEVOP_GX_DECAL		0X0002
#define FTGX_COMPATIBILITY_DEFAULT_TEVOP_GX_BLEND		0X0004
#define FTGX_COMPATIBILITY_DEFAULT_TEVOP_GX_REPLACE		0X0008
#define FTGX_COMPATIBILITY_DEFAULT_TEVOP_GX_PASSCLR		0X0010

#define FTGX_COMPATIBILITY_DEFAULT_VTXDESC_GX_NONE		0X0100
#define FTGX_COMPATIBILITY_DEFAULT_VTXDESC_GX_DIRECT	0X0200
#define FTGX_COMPATIBILITY_DEFAULT_VTXDESC_GX_INDEX8	0X0400
#define FTGX_COMPATIBILITY_DEFAULT_VTXDESC_GX_INDEX16	0X0800

#define FTGX_COMPATIBILITY_NONE							0x0000
#define FTGX_COMPATIBILITY_GRRLIB						FTGX_COMPATIBILITY_DEFAULT_TEVOP_GX_PASSCLR | FTGX_COMPATIBILITY_DEFAULT_VTXDESC_GX_NONE
#define FTGX_COMPATIBILITY_LIBWIISPRITE					FTGX_COMPATIBILITY_DEFAULT_TEVOP_GX_MODULATE | FTGX_COMPATIBILITY_DEFAULT_VTXDESC_GX_DIRECT

const unsigned int ftgxWhite = 0xffffffff; /**< Constant color value used only to sanitize Doxygen documentation. */

/*! \class FreeTypeGX for GRRLIB
 * \brief Wrapper class for the FreeType library with GX rendering. Adapted for GRRLIB.
 * \author Armin Tamzarian and HTV04
 * \version 0.3.2-grrlib1
 *
 * FreeTypeGX acts as a wrapper class for the FreeType library. It supports precaching of transformed glyph data into
 * a specified texture format. Rendering of the data to the EFB is accomplished through the application of high performance
 * GX texture functions resulting in high throughput of string rendering.
 */
class FreeTypeGX {

	private:
		FT_Library ftLibrary;		/**< FreeType FT_Library instance. */
		FT_Byte * ftFontBuffer;		/**< Pointer to the current font buffer */
		FT_Long ftFontBufferSize;	/**< Size of the current font buffer */
		FT_UInt ftPointSize;		/**< Requested size of the rendered font. */
		FT_Short ftAscender;		/**< Ascender value of the rendered font. */
		FT_Short ftDescender;		/**< Descender value of the rendered font. */

		bool ftKerningEnabled;		/**< Flag indicating the availability of font kerning data. */
		FT_Face ftFace;				/**< Reusable FreeType FT_Face object. */

		uint8_t textureFormat;		/**< Defined texture format of the target EFB. */
		uint8_t vertexIndex;		/**< Vertex format descriptor index. */
		uint32_t compatibilityMode;	/**< Compatibility mode for default tev operations and vertex descriptors. */
		std::map<wchar_t, ftgxCharData> fontData; /**< Map which holds the glyph data structures for the corresponding characters. */

		bool widthCachingEnabled;
		std::map<const wchar_t*, int> cacheTextWidth;

		static int maxVideoWidth; /**< Maximum width of the video screen. */

		static int adjustTextureWidth(int textureWidth, uint8_t textureFormat);
		static int adjustTextureHeight(int textureHeight, uint8_t textureFormat);

		int getStyleOffsetWidth(int width, int format);
		int getStyleOffsetHeight(int format);
		ftgxCharData* getCharacter(wchar_t character);

		void unloadFont();
		ftgxCharData *cacheGlyphData(wchar_t charCode);
		int cacheGlyphDataComplete();
		void loadGlyphData(FT_Bitmap *bmp, ftgxCharData *charData);

		void drawTextFeature(float x, float y, int width, int format, unsigned int color);
		void copyTextureToFramebuffer(GXTexObj *texObj, float texWidth, float texHeight, float screenX, float screenY, unsigned int color);
		void copyFeatureToFramebuffer(float featureWidth, float featureHeight, float screenX, float screenY, unsigned int color);

	public:
		FreeTypeGX(uint8_t textureFormat = GX_TF_RGBA8);
		~FreeTypeGX();

		bool setKerningEnabled(bool enabled);
		bool getKerningEnabled();
		bool setTextWidthCachingEnabled(bool enabled);
		bool getTextWidthCachingEnabled();
		void clearTextWidthCache();

		static wchar_t* charToWideChar(char* p);
		static wchar_t* charToWideChar(const char* p);
		static int setMaxVideoWidth(int width);

		int loadFont(uint8_t* fontBuffer, FT_Long bufferSize, FT_UInt pointSize, bool cacheAll = false);
		int loadFont(const uint8_t* fontBuffer, FT_Long bufferSize, FT_UInt pointSize, bool cacheAll = false);

		int drawText(float x, float y, wchar_t *text, unsigned int color = ftgxWhite, int textStyling = FTGX_NULL);
		int drawText(float x, float y, wchar_t const *text, unsigned int color = ftgxWhite, int textStyling = FTGX_NULL);

		int getWidth(wchar_t *text);
		int getWidth(wchar_t const *text);
		int getHeight(wchar_t *text);
		int getHeight(wchar_t const *text);
};

#endif /* FREETYPEGX_H_ */
