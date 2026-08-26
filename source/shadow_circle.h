#pragma once

class ShadowCircle
{
public:

	ShadowCircle(VECTOR* owner_pos,const float& size);

	~ShadowCircle();

	void Init();

	void Update();

	const void Draw() const;

private:

	void LoadFile();

private:

	VECTOR* owner_pos_;

	VECTOR pos_;
	VECTOR rot_;
	VECTOR scale_;

	int handle_;	// ‰e‚Ìƒ‚ƒfƒ‹
	float base_y_;	// ‰e‚ð“Š‰e‚·‚ébse‚Ìƒ|ƒWƒVƒ‡ƒ“

	float blend_rate_;
};