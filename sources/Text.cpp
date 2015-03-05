/**
 * Text.cpp
 *
 */

#include "Text.h"

Text::Text():
	texture(nullptr) {
	this->color = Color("white");
}

Text::~Text() {
	if (texture) {
		SDL_DestroyTexture(texture);
	}
}

void Text::setFont(Font *new_font) {
	font = new_font;
}

void Text::setColor(Color new_color)
{
	color = new_color;
}

void Text::print(Window *window, std::string text, int x, int y) {
	if (texture) {
		SDL_DestroyTexture(texture);
	}

	TTF_Font *primary_font = font->getFont();

	SDL_Color font_color = {color.r(),
							color.g(),
							color.b(),
							color.a()};

	SDL_Surface* text_surface = TTF_RenderText_Solid(primary_font,
													text.c_str(),
													font_color);

	if (text_surface) {
		SDL_Renderer* renderer = window->getRenderer();
		texture = SDL_CreateTextureFromSurface(renderer, text_surface);

		int width, height;
		SDL_QueryTexture(texture, NULL, NULL, &width, &height);

		SDL_Rect clip = {0, 0, width, height};
		SDL_Rect destination = {x, y, clip.w, clip.h};

		SDL_RenderCopy(renderer, texture, &clip, &destination);
	} else {
		printf("Text could not be printed! SDL_Error: %s\n", SDL_GetError());
	}

	SDL_FreeSurface(text_surface);
}