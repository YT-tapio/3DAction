#pragma once

class SceneBase
{
public:

	SceneBase();

	virtual ~SceneBase();

	virtual void Init();

	virtual void Update();

	virtual void Draw();

	const virtual std::string GetName() const;

protected:


private:

};