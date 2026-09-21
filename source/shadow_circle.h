#pragma once

class ShadowCircle
{
public:

	ShadowCircle(VECTOR* owner_pos, bool* owner_is_active,const float& size);

	~ShadowCircle();

	void Init();

	void Update();

	const void Draw() const;

private:

	void LoadFile();

private:

	VECTOR* owner_pos_;
	bool* owner_is_active_;

	VECTOR pos_;
	VECTOR rot_;
	VECTOR scale_;

	int handle_;	// ‰e‚Ìƒ‚ƒfƒ‹
	float base_y_;	// ‰e‚ð“Š‰e‚·‚ébse‚Ìƒ|ƒWƒVƒ‡ƒ“
	float blend_rate_; // ‰e‚Ì”–‚³

};