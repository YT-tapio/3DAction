#pragma once

class Object2D;

class HPBar
{
public:

	HPBar(const std::string path, std::function<int()> get_base_hp_, std::function<int()> get_current_hp_);

	~HPBar();

	void Init();

	void Update();

	void Draw();

protected:

	void LoadFile(const std::string path, std::function<int()> get_base_hp_, std::function<int()> get_current_hp_);

private:

	// ui
	std::vector<std::shared_ptr<Object2D>> ui_;

};