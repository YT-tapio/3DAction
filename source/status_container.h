#pragma once

enum class AttackType;
class VariableTimer;
class Status;

class StatusContainer
{
public:

	StatusContainer(const std::string owner_name, const VECTOR& hp_pos, const VECTOR& hp_size);

	~StatusContainer();

	void Init();

	void Update();

	void Draw();

	void Debug();

	void TakeDamage(float atk,AttackType type);

	void TakeHeal(float heal);

	const Status GetBaseStatus() const;

	const Status GetCurrentStatus() const;

private:

	void LoadFile(const std::string owner_name);

private:

	Status base_status_;		// 初期状態
	Status current_status_;		// 現在の状態

	//TODO：HP描画は違うところで行いましょう
	// HP描画のposition(いったんここで)
	VECTOR hp_pos_;
	VECTOR hp_size_;
	// TODO：バフ系は後から

};
