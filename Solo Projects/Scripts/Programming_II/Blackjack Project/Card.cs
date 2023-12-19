using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ClassLibrary1
{
    public class Card : ICard
    {
        public CardFace Face { get; private set; }
        public CardSuit Suit { get; private set; }
        public void Draw(int x, int y)
        {// color
            
            Console.CursorLeft = x;
            Console.CursorTop = y;

            Console.BackgroundColor = ConsoleColor.White;
            Console.ForegroundColor = ConsoleColor.Black;
            switch (Face)
            {
                case CardFace.CardA:
                    Console.Write("A");
                    break;
                case CardFace.Card2:
                    Console.Write("2");
                    break;
                case CardFace.Card3:
                    Console.Write("3");
                    break;
                case CardFace.Card4:
                    Console.Write("4");
                    break;
                case CardFace.Card5:
                    Console.Write("5");
                    break;
                case CardFace.Card6:
                    Console.Write("6");
                    break;
                case CardFace.Card7:
                    Console.Write("7");
                    break;
                case CardFace.Card8:
                    Console.Write("8");
                    break;
                case CardFace.Card9:
                    Console.Write("9");
                    break;
                case CardFace.Card10:
                    Console.Write("10");
                    break;
                case CardFace.CardJ:
                    Console.Write("J");
                    break;
                case CardFace.CardQ:
                    Console.Write("Q");
                    break;
                case CardFace.CardK:
                    Console.Write("K");
                    break;
            }

            switch (Suit)
            {
                case CardSuit.Spades:
                    Console.Write("♠");
                    break;
                case CardSuit.Hearts:
                    Console.ForegroundColor = ConsoleColor.Red;
                    Console.Write("♥");
                    break;
                case CardSuit.Clubs:
                    Console.Write("♣");
                    break;
                case CardSuit.Diamonds:
                    Console.ForegroundColor = ConsoleColor.Red;
                    Console.Write("♦");
                    break;
                    
            }
            Console.BackgroundColor = ConsoleColor.Black;
            Console.ForegroundColor = ConsoleColor.White;
        }

        public Card(CardFace face, CardSuit suit)
        {
            Face = face;
            Suit = suit;
        }

    }
}
