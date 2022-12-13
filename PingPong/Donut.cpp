#include "Donut.h"

const float characterAspect = 11.f / 24.f;

struct Pixel {
	char character;
	unsigned short color;
};

struct vec3 {
	float x, y, z;

	vec3(float _x) : x(_x), y(_x), z(_x) {}
	vec3(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}

	vec3 operator+(vec3 const& b) { return vec3(x + b.x, y + b.y, z + b.z); }
	vec3 operator-(vec3 const& b) { return vec3(x - b.x, y - b.y, z - b.z); }
	vec3 operator*(vec3 const& b) { return vec3(x * b.x, y * b.y, z * b.z); }
	vec3 operator/(vec3 const& b) { return vec3(x / b.x, y / b.y, z / b.z); }

	float length() {
		return sqrtf(x * x + y * y + z * z);
	}

	vec3 normalize() {
		return vec3(x, y, z) / length();
	}

	float dot(vec3 const& b) {
		return x * b.x + y * b.y + z * b.z;
	}
};

struct vec2 {
	float x, y;

	vec2(float _x) : x(_x), y(_x) {}
	vec2(float _x, float _y) : x(_x), y(_y) {}

	vec2 operator+(vec2 const& b) { return vec2(x + b.x, y + b.y); }
	vec2 operator-(vec2 const& b) { return vec2(x - b.x, y - b.y); }
	vec2 operator*(vec2 const& b) { return vec2(x * b.x, y * b.y); }
	vec2 operator/(vec2 const& b) { return vec2(x / b.x, y / b.y); }

	float length() {
		return sqrtf(x * x + y * y);
	}

	vec2 normalize() {
		return vec2(x, y) / length();
	}

	static vec2 sphere(vec3 ro, vec3 rd, float r) {
		float b = ro.dot(rd);
		float c = ro.dot(ro) - r * r;
		float h = b * b - c;
		if (h < 0.f) return vec2(-1.f);
		h = sqrtf(h);
		return vec2(-b - h, -b + h);
	}
};


Pixel shader(vec2 uv, vec2 size, unsigned int t) {
	Pixel p = { ' ', 7U };

	static vec3 pos = vec3(-2, 0, 0);
    vec3 rd = vec3(1, uv.x, uv.y).normalize();

	if (GetAsyncKeyState('W') & 0x8000) {
		pos.x += 0.00001f;
	}
	if (GetAsyncKeyState('S') & 0x8000) {
		pos.x -= 0.00001f;
	}

	if (GetAsyncKeyState('A') & 0x8000) {
		pos.y -= 0.00001f;
	}
	if (GetAsyncKeyState('D') & 0x8000) {
		pos.y += 0.00001f;
	}

	vec3 light = vec3(sinf(t * 0.08f), cosf(t * 0.08f), -1.f).normalize();
	vec2 intersection = vec2::sphere(pos, rd, 1.f + sinf(t * 0.1f) * 0.1f);
	if (intersection.x > 0) {
		vec3 itPoint = pos + rd * intersection.x;
		vec3 n = itPoint.normalize();
		float diff = n.dot(light);

		if (diff > -0.7f)
			p.color = BACKGROUND_RED;
		if (diff > 0.4f)
			p.color = BACKGROUND_RED | BACKGROUND_INTENSITY;
		if (diff > 0.8f)
			p.color = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
		if (diff > 0.9f)
			p.color = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY;
	}
	else {
		p.color = BACKGROUND_BLUE | BACKGROUND_INTENSITY;
	}

	return p;
}


void Donut::setup()
{

}

void Donut::update(float delta)
{

}

void Donut::render()
{
	static unsigned int frame = 0;
	// ### Render ### //
	buffer->clear();

	for (unsigned int i = 0; i < buffer->getWidth() * buffer->getHeight(); i++) {
		unsigned short x = i % buffer->getWidth();
		unsigned short y = i / buffer->getWidth();
		float w = buffer->getWidth();
		float h = buffer->getHeight();
		vec2 uv(x / (float)w * 2.f - 1.f, y / (float)h * 2.f - 1.f);
		uv.x *= w / (float)h * characterAspect;
		Pixel p = shader(uv, { w, h }, frame);
		buffer->set(x, y, p.character, p.color);
	}
	frame++;
}

void Donut::setBuffer(ScreenBuffer* buff) {
	buffer = buff;
}

Donut::Donut() : Game(L"3D Donut")
{

}