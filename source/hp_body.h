#pragma once

class HPBody : public Object2D
{
public:
	
	HPBody(const ImageData& data, const VECTOR& pos, float size_rate, float rot
		, std::function<int()> get_base_hp_, std::function<int()> get_current_hp_);

	~HPBody() override;

	void Init() override;

	void Update() override;

	void Draw() override;

	void Debug() override;

private:

	// ŠÖ”ƒ|ƒCƒ“ƒ^‚Åhp‚ğæ“¾‚·‚é
	std::function<int()> get_base_hp_;
	std::function<int()> get_current_hp_;

	// body‚ğ‰B‚·‚½‚ß‚Ìbox‚Ì‘å‚«‚³
	float blind_width_;
	float blind_height_;

	float 

};