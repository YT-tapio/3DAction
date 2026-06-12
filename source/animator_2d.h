#pragma once

struct Animation2DData;

class Animator2D
{
public:

	Animator2D(const std::string& data_file_path);

	virtual ~Animator2D();

	void Init();

	void Update();

	void PlayRequest(std::string name);

	/// <summary>
	/// アニメーションを再生
	/// </summary>
	void Start();

	/// <summary>
	/// アニメーションをストップ
	/// </summary>
	void Stop();

	/// <summary>
	/// アニメーションのキャンセルを有効に
	/// </summary>
	void Cancel();

	const std::string GetNowAnimName() const;

	/// <summary>
	/// 現在のアニメーションを返す
	/// </summary>
	/// <param name="name"></param>
	/// <returns></returns>
	const int GetNowHandle() const;

	/// <summary>
	/// 指定されたアニメーションのデータを返す
	/// </summary>
	/// <param name="name"></param>
	/// <returns></returns>
	const int GetHandle(const std::string& name) const;

private:

	void LoadFile(const std::string& data_file_path);

private:

	std::list<std::string> request_names_;

	std::unordered_map<std::string, Animation2DData> datas_;

	std::string now_anim_name_;
	std::string before_anim_name_;
};