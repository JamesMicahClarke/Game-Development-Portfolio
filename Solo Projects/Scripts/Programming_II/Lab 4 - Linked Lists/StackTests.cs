using System;
using System.Collections.Generic;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using PG02_LinkedLists;

namespace PG02_LinkedLists_Tests
{
    [TestClass]
    public class StackTests
    {
        [TestMethod]
        public void PushPopTest()
        {
            int[] testValues = new int[5] { 10, 20, 30, 40, 50 };

            //TODO: change the class from Stack to PG2Stack
            //create the stack
            PG2Stack<int> testStack = new PG2Stack<int>();

            //add a test value to the stack
            foreach (var testValue in testValues)
            {
                testStack.Push(testValue);
            }
            //the order of items in the stack should be 5,4,3,2,1

            //test that the order of the items dequeued is 5,4,3,2,1
            for (int i = testValues.Length - 1; i >= 0; i--)
            {
                int itemPopped = testStack.Pop();
                Assert.AreEqual(testValues[i], itemPopped);
            }
        }


        /// <summary>
        /// Test that the Pop method will throw an InvalidOperationException if the queue is empty
        /// </summary>
        [TestMethod]
        public void PopExceptionTest()
        {
            //TODO: change the class from Stack to PG2Stack
            //create the stack
            PG2Stack<int> testStack = new PG2Stack<int>();

            //remove the item from the stack
            Assert.ThrowsException<InvalidOperationException>(() => { testStack.Pop(); });
        }

        [TestMethod]
        public void PeekTest()
        {
            int testValue = 5;

            //TODO: change the class from Stack to PG2Stack
            //create the stack
            PG2Stack<int> testStack = new PG2Stack<int>();

            //add a test value to the stack
            testStack.Push(testValue);

            //test that peek returns the testValue
            Assert.AreEqual(testValue, testStack.Peek());
        }


        /// <summary>
        /// Test that the Peek method will throw an InvalidOperationException if the queue is empty
        /// </summary>
        [TestMethod]
        public void PeekExceptionTest()
        {
            //TODO: change the class from Stack to PG2Stack
            //create the stack
            PG2Stack<int> testStack = new PG2Stack<int>();

            //remove the item from the stack
            Assert.ThrowsException<InvalidOperationException>(() => { testStack.Peek(); });
        }

        [TestMethod]
        public void CountTest()
        {
            int[] testValues = new int[5] { 10, 20, 30, 40, 50 };

            //TODO: change the class from Stack to PG2Stack
            //create the stack
            PG2Stack<int> testStack = new PG2Stack<int>();

            //add a test value to the stack
            foreach (var testValue in testValues)
            {
                testStack.Push(testValue);
            }

            //test that the count is correct
            Assert.AreEqual(testValues.Length, testStack.Count);
        }

        [TestMethod]
        public void ReverseTest()
        {
            int[] testValues = new int[5] { 10, 20, 30, 40, 50 };

            //TODO: change the class from Stack to PG2Stack
            //create the stack
            PG2Stack<int> testStack = new PG2Stack<int>();

            //add a test value to the stack
            foreach (var testValue in testValues)
            {
                testStack.Push(testValue);
            }
            //the order of items in the stack should be 50,40,30,20,10

            //TODO: call your reverse method
            testStack.Reverse();
            //the stack order should now be 10, 20, 30, 40, 50

            for (int i = 0; i < testValues.Length; i++)
            {
                int itemPopped = testStack.Pop();
                Assert.AreEqual(testValues[i], itemPopped);
            }
        }
    }
}
