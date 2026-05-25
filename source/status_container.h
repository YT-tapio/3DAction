#pragma once

struct Status;

class StatusContainer
{
public:

	StatusContainer(const std::string owner_name);

	~StatusContainer();

	void Init();

	void Update();

	void Debug();

	const Status GetCurrentStatus() const;

private:

	void LoadFile(const std::string owner_name);

	Status base_status_;		// ‰Šúó‘Ô
	Status current_status_;		// Œ»İ‚Ìó‘Ô

	// ƒoƒtŠÖ˜A



};
