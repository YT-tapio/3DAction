#pragma once

class EnemyBase;

class EnemyGroup
{
public:

	static EnemyGroup& GetInstance()
	{
		static EnemyGroup instance;
		return instance;
	}

	EnemyGroup(const EnemyGroup&) = delete;
	EnemyGroup& operator = (const EnemyGroup&) = delete;

	void Awake();

	void Init();

	void Update();

	void Draw();

	void Debug();

private:

	EnemyGroup();

	void LoadFile();

	std::vector<std::shared_ptr<EnemyBase>> enemies;
};