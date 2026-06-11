#pragma once

class CharacterNameUI : public StringUI
{
public:

	CharacterNameUI(const std::string& file_path,const std::string& name);

	~CharacterNameUI() override;

	void Init() override;

	void Update() override;

	const void Draw() const override;

private:

	std::string name_;

};