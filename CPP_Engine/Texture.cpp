#pragma once
#include "Texture.h"
#include <SDL_image.h>

Texture::Texture()
{
	renderer = nullptr;
	texture = nullptr;
	width = 0;
	height = 0;
}

Texture::Texture(SDL_Renderer* r)
{
	renderer = r;
	texture = nullptr;
	width = 0;
	height = 0;
}

Texture::Texture(SDL_Renderer* r, string path, int w, int h)
{
	renderer = r;
	width = w;
	height = h;
	texture = loadFromFile(path);
}

Texture::~Texture()
{
	free();
}

SDL_Texture* Texture::loadFromFile(string path)
{
	free();

	SDL_Texture* newTexture = nullptr;

	SDL_Surface* surface = IMG_Load(path.c_str());	

	if (surface == nullptr)
	{
		printf("unable to load image %s : %s", path.c_str(), IMG_GetError());
	}
	else
	{
		// Uncomment for transparency keyframing
		//SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format, 0, 0xFF, 0xFF));

		newTexture = SDL_CreateTextureFromSurface(renderer, surface);
		if (newTexture == nullptr)
		{
			printf("unable to create texture %s : %s", path.c_str(), SDL_GetError());
		}
		else
		{
			//width = surface->w;
			//height = surface->h;
		}
		SDL_FreeSurface(surface);
	}
	return newTexture;
}

void Texture::render(int x, int y)
{
	SDL_Rect renderQuad = { x, y, width, height };
	SDL_RenderCopy(renderer, texture, NULL, &renderQuad);
}

void Texture::free()
{
	if (texture != nullptr)
	{
		SDL_DestroyTexture(texture);
		texture = nullptr;
		width = 0;
		height = 0;
	}
}

SDL_Texture* Texture::getTexture()
{
	return texture;
}

int Texture::getWidth()
{
	return width;
}

int Texture::getHeight()
{
	return height;
}
