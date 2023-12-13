using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace James_Clarke_Programmers_Choice
{
    class Program
    {
        static int playerHealth = 100;
        static int playerAttack = 4;
        static string playerName;
        static string playerChoice1;
        static string playerChoice2;

        static int wolfHealth = 12;
        static int wolfAttack = 25;
        static void Main(string[] args)
        {
            bool run = false;
            while (run != true)
            {
                start();
                Console.Clear();
                playerHealth = 100;
                wolfHealth = 12;
            }
        }
        private static void start()
        {
            Console.WriteLine("Welcome to The World of Joe!");
            Console.WriteLine("\nSelect your name");
            playerName = Console.ReadLine();
            Console.WriteLine(playerName + " approaches a lonely house in the woods");
            Console.WriteLine("\npress enter to continue"); Console.ReadLine();
            Console.Clear();
            Console.WriteLine("Go towards the house or turn back into the woods? (Press 'w' or 'h' to choose)");
            playerChoice1 = Console.ReadLine(); Console.WriteLine();
            if (playerChoice1 == "w")
            {
                FightingLoop();
            }
            if (playerChoice1 == "h")
            {
                Console.WriteLine();
            }
        }
        private static void FightingLoop()
        {
            bool ok = true;
            while (ok)
            {
                Console.WriteLine("A lone wolf attempts to attack you from behind!");
                Random surprise = new Random();
                int assassinate = (surprise.Next(0, 5) * wolfAttack);
                playerHealth -= assassinate;
                Console.WriteLine("The wolf's attack does " + assassinate + " damage!");
                if (assassinate < 100)
                {
                    Console.WriteLine("\nBattle engaged!");
                }
                ok = false;
            }
            while (playerHealth > 0 && wolfHealth > 0)
            {
                Console.WriteLine("\nYou have " + playerHealth + " health left");
                Console.WriteLine("The wolf has " + wolfHealth + " health left");
                Console.WriteLine("Will you (A)ttack or (D)efend");
                playerChoice2 = Console.ReadLine(); Console.WriteLine();
                Random rand = new Random();
                if (playerChoice2 == "a")
                {
                    int attackDmg = rand.Next(0, 2) * playerAttack;
                    wolfHealth -= attackDmg;
                    Console.WriteLine("You hit the wolf for " + attackDmg + " damage");
                    Console.ReadLine();

                    int[] decide = new int[] { rand.Next(15, 55) };
                    Random chance = new Random();

                    for (int i = 0; i < decide.Length; i++)
                    {

                        if (wolfHealth > 0)
                        {
                            Console.WriteLine("The wolf attacks!");
                            int c = chance.Next(decide[0]);
                            if (c > chance.Next(20) && c < chance.Next(50))
                            {
                                Random and = new Random();
                                int wolfDmg = and.Next(0, 2) * wolfAttack;
                                playerHealth -= wolfDmg;
                                Console.WriteLine("\nThe wolf hits you for " + wolfDmg + " damage!");
                            }
                            else
                            {
                                Console.WriteLine("the wolf missed you with it's attack!");
                            }
                        }
                    }
                }
                else if (playerChoice2 == "d")
                {
                    Console.WriteLine("The wolf attacks!");

                    int wolfDmg = rand.Next(0, 2) * wolfAttack;
                    if (wolfDmg > 0)
                    {
                        playerHealth -= wolfDmg;
                        Console.WriteLine("The wolf overpowers you and bites you for " + wolfDmg + " damage");
                        Console.ReadLine();
                        
                    }
                    else
                    {
                        Console.WriteLine("You fended off the wolf's viscious attack!");
                        Console.WriteLine("The wolf does " + wolfDmg + " damage");
                    }
                }
                else
                {
                    Console.WriteLine("Please choose keys 'a' or 'd'");
                }
            } 

            while (playerHealth == 0 || wolfHealth == 0)
            {

                if (playerHealth == 0)
                {
                    Console.WriteLine("You perish at the fangs of the wolf!");
                    Console.ReadLine();
                    break;
                }
                else if (wolfHealth == 0)
                {
                    Console.WriteLine("You have slain the wolf and obtained nothing! Nice job!");
                    Console.ReadLine();
                    break;
                }
            }
        }
    }
    
   // public static class Situation1
    //{
      //  public static string choice1(string option)
       // {
         //   string answer = "";
          //  if (option == "Y")
          //  {
           ///     answer = "Welcome to our Home! Would you like something to eat?";
          //  }
          //  else if (option == "W")
           //     answer = "You decide to turn back into the woods, but as soon as you do a wolf jumps onto you!";
           // else
           //     answer = "You must choose by pressing 'H' or 'W'";
           // return answer;
        //}
        
   //}
   
}
