using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ClassLibrary1
{
    public class BlackJackHand : Hand
    {
        public int Score { get; private set; }
        bool IsDealer { get; set; } = false;

        public BlackJackHand(bool isDealer = false)
        {
            if (isDealer)
            {
                isDealer = true;
            }
            IsDealer = isDealer;
        }
        public override void AddCard(ICard aCard)
        {
            base.AddCard(aCard);
            Score = 0;
            int AceCnt = 0;
            for(int i = 0; i < _cards.Count; i++)
            {
                BlackJackCard current = (BlackJackCard)_cards[i];
                if(current.Face == CardFace.CardA)
                {
                    AceCnt += 1;
                }
                else
                {
                    Score += current.Value;
                }
            }
            for(int i = 0; i < AceCnt; i++)
            {
                if(11 + Score > 21)
                {
                    Score += 1;
                }
                else
                {
                    Score += 11;
                }
            }
        }
        public override void Draw(int x, int y)
        {
            if (IsDealer)
            {
                //draw a single blank card
                // color
                Console.BackgroundColor = ConsoleColor.White;
                // spaces
                Console.WriteLine("                                ");
                // position
                x += 5;
                Console.ResetColor();
                for(int i = 1; i < _cards.Count; i++)
                {
                    _cards[i].Draw(x, y);
                    x += 5;
                    Console.WriteLine($"{Score}");
                }
            }
            else
            {
                Console.Clear();
                base.Draw(x, y);
                
            }
        }
    }
}
