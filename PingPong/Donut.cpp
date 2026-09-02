#include "Donut.h"
#include <algorithm>
#include <cmath>

const float characterAspect = 11.f / 24.f;

struct Pixel {
	char character;
	unsigned short color;
};

struct vec3 {
	float x, y, z;

	explicit vec3(float _x) : x(_x), y(_x), z(_x) {}
	vec3(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}

	vec3 operator+(vec3 const& b) const { return vec3(x + b.x, y + b.y, z + b.z); }
	vec3 operator-(vec3 const& b) const { return vec3(x - b.x, y - b.y, z - b.z); }
	vec3 operator*(vec3 const& b) const { return vec3(x * b.x, y * b.y, z * b.z); }
	vec3 operator/(vec3 const& b) const { return vec3(x / b.x, y / b.y, z / b.z); }

	float length() const {
		return sqrtf(x * x + y * y + z * z);
	}

	vec3 normalize() const {
		return vec3(x, y, z) / vec3(length());
	}

	float dot(vec3 const& b) const {
		return x * b.x + y * b.y + z * b.z;
	}
};

struct vec2 {
	float x, y;

	explicit vec2(float _x) : x(_x), y(_x) {}
	vec2(float _x, float _y) : x(_x), y(_y) {}

	vec2 operator+(vec2 const& b) const { return vec2(x + b.x, y + b.y); }
	vec2 operator-(vec2 const& b) const { return vec2(x - b.x, y - b.y); }
	vec2 operator*(vec2 const& b) const { return vec2(x * b.x, y * b.y); }
	vec2 operator/(vec2 const& b) const { return vec2(x / b.x, y / b.y); }

	float length() const {
		return sqrtf(x * x + y * y);
	}

	vec2 normalize() const {
		return vec2(x, y) / vec2(length());
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


// Per-frame values (light direction, sphere radius, camera) are computed once in render()
// and passed in; the old version recomputed them and polled the keyboard for every cell.
static Pixel shader(vec2 uv, vec3 const& pos, vec3 const& light, float radius) {
	Pixel p = { ' ', 7U };

	vec3 rd = vec3(1, uv.x, uv.y).normalize();

	vec2 intersection = vec2::sphere(pos, rd, radius);
	if (intersection.x > 0) {
		vec3 itPoint = pos + rd * vec3(intersection.x);
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
	const float dt = std::min(delta, 50.f);
	const float speed = 0.002f * dt; // camera units per ms -> 2 units/s regardless of FPS or screen size

	if (keyDown('W')) {
		camX += speed;
	}
	if (keyDown('S')) {
		camX -= speed;
	}

	if (keyDown('A')) {
		camY -= speed;
	}
	if (keyDown('D')) {
		camY += speed;
	}

	time += dt;
}

void Donut::render()
{
	// ### Render ### //
	buffer->clear();

	const float t = time / 16.f; // same animation rate as the old per-frame counter at ~60 fps
	const vec3 pos(camX, camY, camZ);
	const vec3 light = vec3(sinf(t * 0.08f), cosf(t * 0.08f), -1.f).normalize();
	const float radius = 1.f + sinf(t * 0.1f) * 0.1f;

	const int w = buffer->getWidth();
	const int h = buffer->getHeight();
	const float aspect = static_cast<float>(w) / static_cast<float>(h) * characterAspect;
	for (int y = 0; y < h; y++) {
		for (int x = 0; x < w; x++) {
			vec2 uv(x / static_cast<float>(w) * 2.f - 1.f, y / static_cast<float>(h) * 2.f - 1.f);
			uv.x *= aspect;
			Pixel p = shader(uv, pos, light, radius);
			buffer->set(static_cast<short>(x), static_cast<short>(y), p.character, p.color);
		}
	}
}

Donut::Donut() : Game(L"3D Donut")
{

}
