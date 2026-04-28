#pragma once

enum class NodeStatus;

class NodeBase
{
public:

	NodeBase();

	virtual ~NodeBase();

	virtual NodeStatus Update();

protected:



private:



};