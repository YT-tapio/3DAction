#pragma once

struct AnimationData;

class AnimatorBase
{
public:

	AnimatorBase(const char* data_file_path,int handle);

	~AnimatorBase();

	void Init();

	virtual void Update();

	void PlayRequest(std::string name);

protected:

	void LoadFile(const char* file_path);

	void ResetRequest();

	const char* kDataFilePath = "";

	std::vector<std::string> request_names_;

	std::unordered_map<std::string, AnimationData> animation_datas_;
	std::string now_anim_name_;
	
	int handle_;
	bool is_end_;

private:

	

};
