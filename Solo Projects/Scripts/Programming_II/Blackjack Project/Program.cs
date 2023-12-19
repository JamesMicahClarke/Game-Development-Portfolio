using ClassLibrary1;
using System;

namespace Lab_2
{
    class Program
    {
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
        static void Main(string[] args)
        {
            Console.OutputEncoding = System.Text.Encoding.UTF8;

            string[] options = new string[] { "\n1. Play Blackjack", "2. Shuffle & Show Deck", "3. Exit" };
            int menuSelection = 0;
            while (menuSelection != 3)
            {
                Console.Clear();
                ReadChoice("Menu:",options,out menuSelection);
       
                switch (menuSelection)
                {
                    case 1:
                        BlackjackGame playGame = new BlackjackGame();
                        bool playing = true;
                        while (playing)
                        {
                            Console.Clear();
                            playGame.PlayRound();
                            
                            Console.CursorLeft = 0;
                            Console.CursorTop = 0;
                            Console.WriteLine("Would you like to play again?");
                            string[] playOption = new string[] { "1. Yes", "2. No" };
                            int playSelect = 0;

                            ReadChoice("Menu:", playOption, out playSelect);
                            switch (playSelect)
                            {
                                case 1:
                                    Console.Clear();
                                    break;
                                case 2:
                                    playing = false;
                                    
                                    break;
                            }
                            Console.Clear();
                            
                        }
                        break;
                    case 2:
                        Deck drawDeck = new Deck();
                        drawDeck.Draw(4,5);
                        Console.ReadLine();
                        break;
                    case 3:

                        break;

                }
            }
        }
    }
}
