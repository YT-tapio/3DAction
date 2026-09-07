#pragma once

class ModelRepository
{
public:

	static ModelRepository& GetInstance()
	{
		static ModelRepository instance;
		return instance;
	}

	void Load();

	const int GetHandle(const std::string& name) const;

private:

	ModelRepository();

private:

	std::unordered_map<std::string, int> models_;

};