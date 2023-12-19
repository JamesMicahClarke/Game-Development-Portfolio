using System;
using System.Collections.Generic;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using PG02_LinkedLists;

namespace PG02_LinkedLists_Tests
{
    [TestClass]
    public class QueueTests
    {
        [TestMethod]
        public void EnqueueDequeueTest()
        {
            int[] testValues = new int[5] { 10, 20, 30, 40, 50 };

            //TODO: change the class from Queue to PG2Queue
            //create the Queue
            PG2Queue<int> testQueue = new PG2Queue<int>();

            //add a test value to the Queue
            foreach (var testValue in testValues)
            {
                testQueue.Enqueue(testValue);
            }
            //final order of items in the Queue should be 1,2,3,4,5

            //test that the order of the items dequeued is 1,2,3,4,5
            for (int i = 0; i < testValues.Length; i++)
            {
                int itemPopped = testQueue.Dequeue();
                Assert.AreEqual(testValues[i], itemPopped);
            }
        }

        /// <summary>
        /// Test that the Dequeue method will throw an InvalidOperationException if the queue is empty
        /// </summary>
        [TestMethod]
        public void DequeueExceptionTest()
        {
            //TODO: change the class from Queue to PG2Queue
            //create the Queue
            PG2Queue<int> testQueue = new PG2Queue<int>();

            //remove the item from the Queue
            Assert.ThrowsException<InvalidOperationException>(() => { testQueue.Dequeue(); });
        }

        [TestMethod]
        public void PeekTest()
        {
            int testValue = 5;

            //TODO: change the class from Queue to PG2Queue
            //create the Queue
            PG2Queue<int> testQueue = new PG2Queue<int>();

            //add a test value to the Queue
            testQueue.Enqueue(testValue);

            //test that peek returns the testValue
            Assert.AreEqual(testValue, testQueue.Peek());
        }


        /// <summary>
        /// Test that the Peek method will throw an InvalidOperationException if the queue is empty
        /// </summary>
        [TestMethod]
        public void PeekExceptionTest()
        {
            //TODO: change the class from Queue to PG2Queue
            //create the Queue
            PG2Queue<int> testQueue = new PG2Queue<int>();

            //remove the item from the Queue
            Assert.ThrowsException<InvalidOperationException>(() => { testQueue.Peek(); });
        }

        [TestMethod]
        public void CountTest()
        {
            int[] testValues = new int[5] { 10, 20, 30, 40, 50 };

            //TODO: change the class from Queue to PG2Queue
            //create the Queue
            PG2Queue<int> testQueue = new PG2Queue<int>();

            //add a test value to the Queue
            foreach (var testValue in testValues)
            {
                testQueue.Enqueue(testValue);
            }

            //test that the count is correct
            Assert.AreEqual(testValues.Length, testQueue.Count);
        }

        [TestMethod]
        public void ReverseTest()
        {
            int[] testValues = new int[5] { 10, 20, 30, 40, 50 };

            //TODO: change the class from Queue to PG2Queue
            //create the Queue
            PG2Queue<int> testQueue = new PG2Queue<int>();

            //add a test value to the Queue
            foreach (var testValue in testValues)
            {
                testQueue.Enqueue(testValue);
            }
            //the order of items in the Queue should be 10, 20, 30, 40, 50

            //TODO: call your reverse method
            testQueue.Reverse();
            //the Queue order should now be 50,40,30,20,10

            for (int i = testValues.Length - 1; i >= 0; i--)
            {
                int itemPopped = testQueue.Dequeue();
                Assert.AreEqual(testValues[i], itemPopped);
            }
        }
    }
}
