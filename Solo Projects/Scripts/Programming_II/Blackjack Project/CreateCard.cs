using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ClassLibrary1
{
    public static class CardFactory
    {
        public static ICard CreateCard(CardFace face, CardSuit suit)
        {
            Card regCard = new Card(face, suit);
           
            return regCard;
        }
        public static ICard CreateBlackjackCard(CardFace face, CardSuit suit)
        {
            BlackJackCard bjc = new BlackJackCard(face,suit);

            return bjc;
        }
    }
    

    
}
