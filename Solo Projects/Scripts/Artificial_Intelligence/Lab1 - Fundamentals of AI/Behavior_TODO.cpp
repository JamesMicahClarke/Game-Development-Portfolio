//! \file Behavior_TODO.cpp
//! \brief Implements the <code>fullsail_ai::fundamentals::Behavior</code> abstract class.
//! \author Jeremiah Blanchard with code from Cromwell D. Enage

//#include <queue>   NOTE: Only use if your QueueList is not working
#include <stack>
#include "Behavior.h"

namespace fullsail_ai {
	namespace fundamentals {

		// DO NOT Edit or Use these two variables for any reason, it is for memory leak check purposes only.
		unsigned Behavior::createdCount = 0;
		unsigned Behavior::destroyedCount = 0;

		unsigned Behavior::getCreatedCount()
		{
			return createdCount;
		}

		unsigned Behavior::getDestroyedCount()
		{
			return destroyedCount;
		}

		Behavior::Behavior(char const* _description)
		{
			description = _description;
		}

		char const* Behavior::toString() const
		{
			return description;
		}

		// DO NOT edit this function, it is supposed to just return false
		bool Behavior::isLeaf() const
		{
			return false;
		}

		DLLEXPORT size_t Behavior::getChildCount() const
		{
			return children.size();
		}

		DLLEXPORT Behavior* Behavior::getChild(size_t index)
		{
			return children[index];
		}

		DLLEXPORT Behavior const* Behavior::getChild(size_t index) const
		{
			return children[index];
		}

		DLLEXPORT void Behavior::addChild(Behavior* child)
		{
			children.push_back(child);
			child->parent = this;
		}

		DLLEXPORT void Behavior::breadthFirstTraverse(void(*dataFunction)(Behavior const*)) const
		{
			QueueList<Behavior const*> list;
			list.enqueue(this);
			while (!list.isEmpty())
			{
				Behavior const* front = list.getFront();
				int childCount = front->getChildCount();
				list.dequeue();
				dataFunction(front);
				for (int i = 0; i < childCount; i++)
				{
					list.enqueue(front->children[i]);
				}

			}
		}



		DLLEXPORT void Behavior::preOrderTraverse(void(*dataFunction)(Behavior const*)) const
		{

			dataFunction(this);
			for (int i = 0; i < children.size(); i++)
			{
				children[i]->preOrderTraverse(dataFunction);
			}
		}

		DLLEXPORT void Behavior::postOrderTraverse(void(*dataFunction)(Behavior const*)) const
		{
			for (int i = 0; i < children.size(); i++)
			{
				children[i]->postOrderTraverse(dataFunction);
			}
			dataFunction(this);
		}

		//! \TODO
		//!   - Implement the <code>Behavior</code> methods.


	}
}  // namespace fullsail_ai::fundamentals
