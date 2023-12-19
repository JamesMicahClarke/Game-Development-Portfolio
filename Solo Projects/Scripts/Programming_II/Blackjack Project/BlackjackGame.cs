using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ClassLibrary1
{
    public class BlackjackGame
    {
        BlackJackHand _dealer;
        BlackJackHand _player;
        Deck _deck;
        public void PlayRound()
        {
            _dealer = new BlackJackHand();
            _player = new BlackJackHand();
            _deck = new Deck();
            DealInitialCards();
            if (_player.Score != 21 || _dealer.Score != 21)
            {
                PlayersTurn();
                DealersTurn();

            }
            DeclareWinner();
        }
        public void DealInitialCards()
        {
            _player.AddCard(_deck.Deal());
            _dealer.AddCard(_deck.Deal());
            _player.AddCard(_deck.Deal());
            _dealer.AddCard(_deck.Deal());
        }
        public void PlayersTurn()
        {
            while (_player.Score < 21)
            {
                _player.Draw(0, 7);
                Console.CursorLeft = 0;
                Console.CursorTop = 1;
                Console.WriteLine(" Would you like to hit or stand?");
                string[] options = new string[] { "1. Hit", "2. Stand" };
                int playerSelection = 0;

                ReadChoice("Menu:", options, out playerSelection);

                switch (playerSelection)
                {
                    case 1:
                        _player.AddCard(_deck.Deal());
                        _player.Draw(0, 2);
                        Console.CursorTop = 0;
                        Console.CursorLeft = 0;
                        Console.WriteLine("player cards:");
                        Console.ReadLine();
                        Console.Clear();
                        break;
                    case 2:
                        
                        return;


                }

            }
        }
        public void DealersTurn()
        {
            Console.Clear();
             _dealer.Draw(0, 8);
            Console.CursorTop = 5;
            Console.CursorLeft = 0;
            Console.WriteLine("Dealer's cards:");
            

            while (_dealer.Score < 17)
            {
                _dealer.AddCard(_deck.Deal());
                _dealer.Draw(0, 8);
            }
        }
        public void DeclareWinner()
        {
            
            Console.CursorLeft = 0;
            Console.CursorTop = 9;
            if (_player.Score > 21)
            {
                Console.WriteLine("Dealer wins!");
            }
            else if (_player.Score < _dealer.Score && _dealer.Score <= 21)
            {
                Console.WriteLine("Dealer wins!");
            }
            else if (_dealer.Score > 21)
            {
                Console.WriteLine("Player wins!");
            }
            else if (_player.Score > _dealer.Score && _player.Score <= 21)
            {
                Console.WriteLine("Player wins!");
            }
            else if (_player.Score == _dealer.Score)
            {
                Console.WriteLine("Tie game!");
            }
            else
            {
                Console.WriteLine("Dealer wins!");
            }
        }
        private static int ReadInteger(string prompt, int min, int max)
        {
            string[] maximum = new string[] { };
            prompt = "Please input a number";
            Console.WriteLine(prompt);
            string response = Console.ReadLine();
            bool corrected = int.TryParse(response, out int number);
            while (corrected == false || number < min || number > max)
            {
                Console.WriteLine("Your response was not accepted... Please use a valid input this time.");
                response = Console.ReadLine();
                corrected = int.TryParse(response, out number);
                if (corrected == true && number > min && number < max)
                {
                    break;
                }

            }
            return number;
        }
        public static void ReadString(string prompt2, ref string value)
        {
            prompt2 = "";
            Console.WriteLine("Write something...");
            string response2 = Console.ReadLine();
            while (String.IsNullOrWhiteSpace(response2))
            {
                Console.WriteLine("You need to write a letter, word, or phrase here!");
                response2 = Console.ReadLine();
            }
            value = response2;
        }
        private static void ReadChoice(string prompt3, string[] options, out int selection)
        {

            for (int i = 0; i < options.Length; i++)
            {
                Console.WriteLine(options[i]);
            }
            selection = ReadInteger(prompt3, 0, options.Length);

        }
    }

}
