#pragma once

#include "../Composite.hpp"

namespace bt
{

/*
    The Selector composite ticks each child node in order.
    If a child succeeds or runs, the sequence returns the same status.
    In the next tick, it will try to run each child in order again.
    If all children fails, only then does the selector fail.
 */
class Selector : public Composite
{
public:
void Initialize()
{
	index = 0;
}

Status Update()
{
	if (HasNoChildren())
		return Status::Success;

	// Keep going until a child behavior says it's running.
	while (1)
	{
		std::shared_ptr<bt::Node> &child = children.at(index);
		bt::Node::Status status = child->Tick();

		// If the child succeeds, or keeps running, do the same.
		if (status != Status::Failure)
			return status;

		// Hit the end of the array, it didn't end well...
		if (++index == (signed)children.size())
			return Status::Failure;
	}
}

using Ptr = std::shared_ptr<Selector>;
};

static Selector::Ptr MakeSelector()
{
	return std::make_shared<Selector>();
}

}
