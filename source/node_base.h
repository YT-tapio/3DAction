#pragma once

enum class BehaviorStatus;

class NodeBase
{
public:

	NodeBase();

	virtual ~NodeBase();

	virtual void Init();

	virtual BehaviorStatus Update();

	virtual void Debug();

protected:



private:



};