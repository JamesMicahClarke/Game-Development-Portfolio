using Microsoft.VisualStudio.TestTools.UnitTesting;
using ClassLibrary1;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ClassLibrary1.Tests
{
    [TestClass()]
    public class BlackJackHandTests
    {
        [TestMethod()]
        public void BlackJackHandTest()
        {
            BlackJackHand scoreTest = new BlackJackHand();

            scoreTest.AddCard(CardFactory.CreateBlackjackCard(CardFace.CardA, CardSuit.Clubs));
            scoreTest.AddCard(CardFactory.CreateBlackjackCard(CardFace.Card8, CardSuit.Clubs));
            Assert.AreEqual(19, scoreTest.Score);
            scoreTest.AddCard(CardFactory.CreateBlackjackCard(CardFace.Card10, CardSuit.Clubs));
            Assert.AreEqual(19, scoreTest.Score);
        }
    }
}