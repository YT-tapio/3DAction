#pragma once

class HPBody : public Object2D
{
public:
	
	HPBody(const std::string path);

	~HPBody() override;

	void Init() override;

	void Update() override;

	void Draw() override;

	void Debug() override;

protected:



private:



};