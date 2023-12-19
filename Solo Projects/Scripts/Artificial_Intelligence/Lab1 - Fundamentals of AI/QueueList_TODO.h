//! \file QueueList_TODO.h
//! \brief Defines the <code>fullsail_ai::data_structures::QueueList</code> class template
//! implementation.
//! \author Cromwell D. Enage
#ifndef _FULLSAIL_AI_FUNDAMENTALS_QUEUELIST_TODO_H_
#define _FULLSAIL_AI_FUNDAMENTALS_QUEUELIST_TODO_H_

namespace fullsail_ai {
	namespace fundamentals {

		//! \TODO
		//!   - Complete the definition of the <code>QueueList::Iterator</code> pre-increment operator.
		//!   - Complete the definition of the <code>QueueList::Iterator</code> dereference operator.
		//!   - Define the <code>QueueList</code> constructor.
		//!   - Define the <code>QueueList</code> destructor.
		//!   - Define the <code>QueueList</code> methods.


		template <typename T>
		QueueList <T > ::QueueList() { front = nullptr; back = nullptr; }

		template <typename T>
		QueueList<T>::~QueueList() { removeAll(); }

		template <typename T>
		typename QueueList<T>::Iterator& QueueList<T>::Iterator::operator++()
		{
			// TODO: Complete the definition of this operator.
			if (currentNode != nullptr)
			{
				this->currentNode = currentNode->next;

			}
			return *this;
		}

		template <typename T>
		T QueueList<T>::Iterator::operator*() const
		{
			// TODO: Complete the definition of this operator.
			return this->currentNode->data;

		}

		template <typename T>
		bool QueueList<T>::isEmpty() const
		{
			if (front != nullptr)
			{
				return false;
			}
			return true;
		}

		template<typename T>
		inline void QueueList<T>::enqueue(T element)
		{
			Node* ele = new Node(element);

			if (front == nullptr)
			{
				front = ele;
				back = ele;
			}
			else
			{

				back->next = ele;
				back = ele;
			}
		}

		template <typename T>
		void QueueList<T>::dequeue()
		{
			if (front == back)
			{
				Node* remove = front;
				front = nullptr;
				back = nullptr;
				delete remove;
			}
			if (front != nullptr)
			{

				Node* dead = front;
				front = front->next;
				delete dead;
			}
		}

		template <typename T>
		void QueueList<T>::remove(T element)
		{
			Node* temp = front;
			Node* prev = nullptr;
			while (temp != nullptr)
			{
				if (temp->data == element)
				{

					if (temp == front)
					{
						temp = temp->next;
						this->dequeue();
						break;
					}
					else
					{ 
						Node* remove = temp;
						prev->next = temp->next;
						delete remove;
						break;
					}
				}
				prev = temp;
				temp = prev->next;
			}
		}


		template <typename T>
		void QueueList<T>::removeAll()
		{
			if (front == back)
			{
				Node* remove = front;
				front = nullptr;
				back = nullptr;
				delete remove;
			}
			while (front != nullptr && back != nullptr)
			{
				Node* kill = front;
				front = front->next;
				delete kill;
			}
		}

		template <typename T>
		bool QueueList<T>::contains(T element) const
		{
			if (front == nullptr && back == nullptr)
			{
				return false;
			}
			else
			{
				Node* noder = front;
				while (noder != nullptr)
				{

					if (noder->data != element)
					{
						noder = noder->next;

					}
					else
					{
						return true;
					}

				}
				return false;
			}

		}

		template <typename T>
		T QueueList<T>::getFront() const
		{
			return front->data;
		}
	}
}  // namespace fullsail_ai::fundamentals

#endif  // _FULLSAIL_AI_FUNDAMENTALS_QUEUELIST_TODO_H_

