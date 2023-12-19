using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace PG02_LinkedLists
{
    public class PG2Queue<T>
    {
        public int Count { get; private set; }
        Node<T> _head = null;
        Node<T> _tail = null;

        public void Enqueue(T data)
        {
            Node<T> queued = new Node<T>(){ Data = data };
            if (Count == 0)
            {
                _tail = queued;
                _head = queued;
                Count++;
            }
            else
            {
                _tail.Next = queued;
                _tail = queued;
            }
        }
        public T Dequeue()
        {
            T dequeue;
            if (Count == 0)
            {
                _tail = null;
                Exception exception = new InvalidOperationException("Index is INVALID!!");
                throw exception;
            }
            else
            {
                dequeue = _head.Data;
                _head = _head.Next;
                --Count;
            }
            return dequeue;
        }
        public T Peek()
        {
            T see;
            if (_head == null)
            {
                Exception exception = new InvalidOperationException("Index is INVALID!!");
                throw exception;
            }
            else
            {
                see = _head.Data;
                return see;
            }
        }
        public void Reverse()
        {
           Node<T> previous = null;
            while (_head != null && _tail != null)
            {
                Node<T> Next = _head.Next;
                Node<T> Next2 = _tail.Next;

                //_head.Next = previous;
                //previous = _head;
                //_head = Next;

                //_tail.Next = previous;
                //previous = _tail;
                //_tail = Next2;

                _tail.Next = _head;
                _tail = _head;
                _head.Next = previous;
                _head = previous;

                _tail = Next;
                _head = Next2;
            }
            _head = previous;
            _tail = previous;
            
            
           

            //Node<T> previous2 = new Node<T>();
            //_tail.Next = previous2;
            //previous2 = _tail;
            //_tail = previous2.Next;
        }
    }
}
