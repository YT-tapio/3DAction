#pragma once

struct AnimationData;

class AnimatorBase
{
public:

	AnimatorBase(const char* data_file_path,int handle);

	~AnimatorBase();

	virtual void Init();

	virtual void Update();

protected:

	void LoadFile(const char* file_path);

	const char* kDataFilePath = "";

	std::unordered_map<std::string, AnimationData> animation_datas_;
	std::string now_anim_name_;

	int handle_;

private:



};
