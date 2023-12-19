using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Lab_1
{
    class Program
    {
        static void Main(string[] args)
        {
            Console.WriteLine("Hello Full Sail!");
            Console.ReadLine();
            Console.WriteLine("What is your name?");
            string name = Console.ReadLine();
            Console.WriteLine("My name is " + name + ".");
            Console.ReadLine();
            Console.WriteLine("What is your age " + name + "?");
            string answer = Console.ReadLine(); 
            Console.WriteLine(name + " is " + answer + " years old.");
            Console.WriteLine("Welcome to Full Sail " + name + "! You are awesome for being " + answer + " years old!");
            Console.ReadKey();
            int x = 5;
            Add10(x);
            Console.Write(x);

        }
        static void Add10(int x)
        {
            x += 10;
        }
    }
}
