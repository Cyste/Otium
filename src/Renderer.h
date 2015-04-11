/*
Copyright 2015 Mariusz Dzikowski

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/
#ifndef OTIUM_RENDERER_H
#define OTIUM_RENDERER_H

namespace Otium
{

class Renderer
{
private:
	std::map<uint32, void*> _fonts;

public:
	Renderer()
	{
	}

	virtual ~Renderer()
	{
	}

	void* FindFont(uint32 font)
	{
		if (_fonts.find(font) != _fonts.end())
		{
			return _fonts[font];
		}
		return 0;
	}

	void AddFont(const char* fontName, void* font)
	{
		uint32 id;
		OTIUM_HASH_CODE(id, fontName);
		_fonts[id] = font;
	}

	virtual void* RenderFont(uint32 font, const char* text, uint32 wrapLength, uint32 color, int32* srcWidth, int32* srcHeight) = 0;

	virtual void RenderImage(void* image, 
							 int32 x, int32 y, int32 width, int32 height,
							 int32 srcX, int32 srcY, int32 srcWidth, int32 srcHeight) = 0;

	virtual void RenderCopy(int32 x, int32 y, int32 width, int32 height,
							int32 srcX, int32 srcY, int32 srcWidth, int32 srcHeight) = 0;

	virtual void FreeImage(void* image) = 0;
};

}

#ifdef _SDL_H
#include "RendererSDL.h"
namespace Otium { typedef RendererSDL DefaultRenderer; }
#else
namespace Otium { typedef Renderer DefaultRenderer; }
#endif

#endif