#pragma once

enum class AttackType;
class VariableTimer;
class Status;

class StatusContainer
{
public:

	StatusContainer(const std::string owner_name);

	~StatusContainer();

	void Init();

	void Update();

	void Debug();

	void TakeDamage(float atk,AttackType type);

	const Status GetCurrentStatus() const;

private:

	void LoadFile(const std::string owner_name);

private:

	Status base_status_;		// ‰Šúó‘Ô
	Status current_status_;		// Œ»İ‚Ìó‘Ô

	// TODOFƒoƒtŒn‚ÍŒã‚©‚ç

};
