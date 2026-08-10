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

	int handle_;
	int volume_;

	std::string name_;

private:
	

};