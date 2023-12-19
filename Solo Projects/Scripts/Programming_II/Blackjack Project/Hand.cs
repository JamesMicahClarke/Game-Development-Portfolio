using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ClassLibrary1
{
    public class Hand
    {
        public List<ICard> _cards = new List<ICard>();
        
         public virtual void AddCard(ICard aCard)
        {

            _cards.Add(aCard);
        }
        public virtual void Draw(int x, int y)
        {
            int save = x;
            for (int i = 0; i < _cards.Count; i++)
            {
                _cards[i].Draw(x, y);
                x += 5;
                if (i % 4 == 0 && i != 0)
                {
                    y += 5;
                    x = save;
                }


            }
        }
    }
}
