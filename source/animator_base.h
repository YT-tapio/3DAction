#pragma once

struct AnimationData;

class AnimatorBase
{
public:

	AnimatorBase(const char* data_file_path,int handle);

	virtual ~AnimatorBase();

	void Init();

	void Update();

	void PlayRequest(std::string name);

	/// <summary>
	/// ˆø”‚ÌÄ¶ŠÔ‚ğ“¾‚é
	/// </summary>
	/// <param name="name"></param>
	/// <returns></returns>
	const float GetPlayTime(std::string name) const;

	const std::string GetNowAnimName() const;

protected:

	virtual void ChangeAnimation();

	void LoadFile(const char* file_path);

	void ResetRequest();

	const char* kDataFilePath = "";

	const std::string kNothing = "nothing";

	std::vector<std::string> request_names_;

	std::unordered_map<std::string, AnimationData> animation_datas_;
	std::string now_anim_name_;
	std::string before_anim_name_;

	int handle_;
	bool is_end_;

private:

	

};
