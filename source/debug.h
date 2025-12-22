#pragma once

class Debug
{
public:

	static Debug& GetInstance()
	{
		static Debug instance;
		return instance;
	}

	Debug(const Debug&) = delete;
	Debug& operator = (const Debug&) = delete;

	void Reset();

	void Update();

	// デバッグしたときの要素のカウント
	void Add();

	const int GetLineSize() const;

	const int GetNum() const;

	const int GetNowLineSize() const;

	const bool GetIsDisp() const;

	

private:

	Debug();

	const int kLineSize = 15;

	int num_;
	bool is_disp_;

};
