#pragma once

enum class BehaviorStatus;

class NodeBase
{
public:

	NodeBase();

	virtual ~NodeBase();

	virtual BehaviorStatus Update();

protected:



private:



};