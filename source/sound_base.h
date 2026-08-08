#pragma once

class SoundBase
{
public:

	SoundBase();

	virtual ~SoundBase();

	virtual void Init();

	void Play(const std::string& name);

	void Stop();


protected:

	/// <summary>
	/// Ä¶‚·‚éî•ñ‚ğƒZƒbƒg‚·‚é
	/// </summary>
	virtual void SetPlayData(const std::string& name);

protected:

	int handle_;
	

private:

	

};