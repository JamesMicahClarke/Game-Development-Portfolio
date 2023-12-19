using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace PG02_LinkedLists
{
    public class PG2Stack<T>
    {
        public int Count { get; private set; }
        
        Node<T> _head = null;

        public void Push(T data)
        {
            Node<T> node2 = new Node<T>() { Data = data };
            node2.Next = _head;
            _head = node2;
            ++Count;
        }
        public T Pop()
        {
            T removed;
            if (Count == 0)
            {
                Exception exception = new InvalidOperationException("Index is INVALID!!");
                throw exception;
            }
            else
            {
                removed = _head.Data;
                _head = _head.Next;
                --Count;
            }
            
            return removed;
        }
        public T Peek()
        {
            T see;
            if (Count == 0)
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
            
            while (_head != null)
            {
                Node<T> Next = _head.Next;
                _head.Next = previous;
                previous = _head;
                _head = Next;
            }
            _head = previous;
        }
    }
}
