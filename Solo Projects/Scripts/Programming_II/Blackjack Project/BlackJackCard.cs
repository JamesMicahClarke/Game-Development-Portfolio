using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ClassLibrary1
{
    class BlackJackCard : Card
    {
        public int Value { get; set; }
        public BlackJackCard(CardFace face, CardSuit suit) : base(face, suit)
        {
            switch (Face)
            {
                case CardFace.CardA:
                    Value = 1;
                    break;
                case CardFace.Card2:
                    Value = 2;
                    break;
                case CardFace.Card3:
                    Value = 3;
                    break;
                case CardFace.Card4:
                    Value = 4;
                    break;
                case CardFace.Card5:
                    Value = 5;
                    break;
                case CardFace.Card6:
                    Value = 6;
                    break;
                case CardFace.Card7:
                    Value = 7;
                    break;
                case CardFace.Card8:
                    Value = 8;
                    break;
                case CardFace.Card9:
                    Value = 9;
                    break;
                case CardFace.Card10:
                    Value = 10;
                    break;
                case CardFace.CardJ:
                    Value = 10;
                    break;
                case CardFace.CardQ:
                    Value = 10;
                    break;
                case CardFace.CardK:
                    Value = 10;
                    break;
            }
             

        }
    }
}
