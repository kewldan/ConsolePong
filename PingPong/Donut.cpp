#include "Donut.h"

struct Pixel {
	char character;
	unsigned short color;
};


Pixel shader(unsigned short x, unsigned short y, unsigned short w, unsigned short h) {

	return {x < w / 2 ? '#' : ' ', 7U};
}


void Donut::setup()
{

}

void Donut::update(float delta)
{
	
}

void Donut::render()
{
	// ### Render ### //
	buffer->clear();

	buffer->text(0, 0, "Hello 3D world!");
	
	for (unsigned short x = 0; x < buffer->getWidth(); x++) {
		for (unsigned short y = 0; y < buffer->getHeight(); y++) {
			Pixel p = shader(x, y, buffer->getWidth(), buffer->getHeight());
			buffer->set(x, y, p.character, p.color);
		}
	}
}

void Donut::setBuffer(ScreenBuffer* buff) {
	buffer = buff;
}

Donut::Donut() : Game("3D Donut")
{
	
}