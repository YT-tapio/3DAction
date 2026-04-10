#pragma once

class EffectBase;

class EffectManager
{
public:

	static EffectManager& GetInstance()
	{
		static EffectManager instance;
		return instance;
	}

	EffectManager(const EffectManager&) = delete;
	EffectManager& operator = (const EffectManager&) = delete;

	void Awake();

	void Init();

	void Update();

	void Draw();

	void Debug();

	void Play(const int& id);

	void Stop(const int& id);

	void End(const int& id,const int& end_id);

	void RePlay(const int& id);

	const bool CheckIsPlay(const int& id) const;

private:

	EffectManager();

	void LoadFile();

	std::unordered_map<int, std::shared_ptr<EffectBase>> effects_;


};