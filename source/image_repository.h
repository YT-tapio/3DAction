#pragma once

class ImageRepository
{
public:

	static ImageRepository& GetInstance()
	{
		static ImageRepository instance;
		return instance;
	}

	void Load();

	const int GetHandle(const std::string& name) const;

private:

	ImageRepository();

private:

	std::unordered_map<std::string, int> images_;
};