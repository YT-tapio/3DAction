#pragma once

struct AnimationData;

class AnimatorBase
{
public:

	AnimatorBase(const std::string data_file_path,int handle);

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

	const float GetTotalTime(std::string name) const;

	const float GetRatio(std::string name) const;

	const std::string GetNowAnimName() const;

protected:

	virtual void ChangeAnimation();

	void LoadFile(const std::string file_path);

	void ResetRequest();

	std::string kDataFilePath;

	const std::string kNothing = "nothing";

	std::vector<std::string> request_names_;

	std::unordered_map<std::string, AnimationData> animation_datas_;
	std::string now_anim_name_;
	std::string before_anim_name_;

	int handle_;
	bool is_end_;

private:

	

};
