using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ClassLibrary1
{
    public class Deck
    {
        public List<ICard> _cards = new List<ICard>();

       public Deck()
        {
            for(int s = 0; s < 4; s++)
            {
                for(int c = 0; c < 13; c++)
                {

                    _cards.Add(CardFactory.CreateBlackjackCard((CardFace)c, (CardSuit)s));
                }
            }
            Shuffle();
        }
         public ICard Deal()
        {
            if (_cards.Count == 0)
            {
                for (int s = 0; s < 4; s++)
                {
                    for (int c = 0; c < 13; c++)
                    {
                        _cards.Add(CardFactory.CreateBlackjackCard((CardFace)c, (CardSuit)s));
                    }
                }
                Shuffle();
            }
                ICard topCard = _cards[0];
                _cards.Remove(topCard);

            return topCard;
        }
        public void Shuffle()
        {
            for(int shuf = 0; shuf < _cards.Count; shuf++)
            {
                Random rand = new Random();
                int cardshuf = rand.Next(52);
                ICard ruffleshuff = _cards[cardshuf];//new instance = _cards[cardshuf]
                _cards[cardshuf] = _cards[shuf];
                _cards[shuf] = ruffleshuff;
            }
        }
       public void Draw(int x, int y)
        {
            int save = x;
            for (int i = 0; i < _cards.Count; i++)
            {
                _cards[i].Draw(x, y);
                x += 5;
                if (i % 4 == 0)
                {
                    y += 5;
                    x = save;
                }


            }
        }
    }
}
