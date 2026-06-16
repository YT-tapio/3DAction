#pragma once

class EnemyUIGroup
{
public:

	static EnemyUIGroup& GetInstance()
	{
		static EnemyUIGroup instance;
		return instance;
	}

	EnemyUIGroup(const EnemyUIGroup&) = delete;
	EnemyUIGroup& operator = (const EnemyUIGroup&) = delete;

	void Init();

	void Update();

	void Draw();

private:

	EnemyUIGroup();

private:



};