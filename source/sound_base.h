#pragma once

class SoundBase
{
public:

	SoundBase();

	virtual ~SoundBase();

	virtual void Init();

	virtual void Update();

	void Play();

	void Stop();

	const std::string GetName() const;

protected:

	std::string name_;

	int handle_;
	int volume_;

	bool loop_;

private:
	

};