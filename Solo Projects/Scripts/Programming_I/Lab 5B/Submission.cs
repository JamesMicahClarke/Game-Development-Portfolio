using System;
using Tester;

namespace FSPG1
{
    class Submission
    {
        /*
         * This lab is NOT interactive - that means there should be no 
         * calls to the Console class (no Write/WriteLine/ReadLine/ReadKey)
         * 
         * You cannot use multiple return statements any of these methods. 
         * Additionally the use of var is not permitted
         * 
        */

        // Test 1 – How many multiples
        // Given three int's, start, end and factor, using a loop, count how 
        // multiples of factor occur between start and end(inclusive)
        public static int Test1(int start, int end, int factor)
        {
            int multiples = 0;
            for (int cntr = start; cntr <= end; cntr++)
            {
               if(cntr % factor == 0)
                {
                    multiples++;
                }
            }
            return multiples;
        }

        // Test 2 - Factorial
        // Given an int, number, calculate the factorial for number. A factorial 
        // is the result of multiplying all integers between 1 and the target 
        // (number) (so 3 factorial, 3!, is 3 X 2 X 1 = 6)
        public static int Test2(int number)
        {
            int factorial = 1;
            for (int cntr = number; cntr > 1; cntr--)
                factorial *= cntr;
            return factorial;
        }

        // Test 3 - Raise to a power
        // Given two int's, root and exponent, use a loop to raise root to 
        // exponent. You are not allowed to use Math.Pow to compute the answer – 
        // you must use a loop. Additionally, exponent will be greater than or 
        // equal to 0 (no negative exponents)
        public static int Test3(int root, int exponent)
        {
            int product = 1;
            for(int cntr = 1; cntr <= exponent; cntr++)
            {
                product = product * root;
            }

            return product;
        }

        // Test 4 - Consumable
        // Given two doubles (onHand and consume) that represent the amount of 
        // an on-hand resource (onHand) and the amount of the resource that is 
        // consumed per cycles (think a time period). You are to determine how 
        // many cycles (time periods), before the on-hand amount is used up. 
        // For example, if you have 1 gallon of milk (onHand)and use 1 quart 
        // (1/4 gallon) per day (consume), determine when you expect to run out 
        // of milk (4 days).  Return the number representing when the on-hand 
        // amount reaches 0 (or becomes negative)
        // You may find it necessary to use the Round method from the Math class 
        // to avoid floating-point errors. I'd suggest rounding the results of 
        // each computation to 3 decimal places.
        public static int Test4(double onHand, double consume)
        {
            int batches = 0;

        while (onHand >= consume)
            {
                batches++;
                onHand = Math.Round(onHand - consume, 3);
            }
            return batches;
        }

        // Test 5 - Prime number
        // Given an int, number, determine if number is a prime number. Recall 
        // prime numbers are numbers that are divisible on by 1 and themselves. 
        // By definition negative values, 0 and 1 are not prime numbers (2 is 
        // the smallest prime number). If number is prime, return true, 
        // otherwise return false.
        public static bool Test5(int number)
        {
            bool prime = true;
            int i = 2;
            if (number < i)
            {
                prime = false;
            }
            else if(number % i == 2)
            {
                prime = false;
            }
            else
            {
              while(i <= number / 2)
                {
                    if(number % i == 0)
                    {
                        prime = false;
                        break;
                    }
                    i++;
                }
            }
            return prime;
        }

        // Test 6 - Build a string
        // Given a char, starter, and an int, number, create a string the is made
        // up of starter the next number of characters (in order). For example, 
        // if starter is 'A' and number is 5, the string should be ABCDE (the
        // starting value of A followed by the next 4 letters, in order) 
        public static string Test6(char starter, int number)
        {
            string series = "";

            for (int cntr = 0; cntr < number; cntr++)
            {
                series += (char)(starter + cntr);
            }
            return series;
        }

        // Test 7 - Making change
        // Given a double, amount, that represents an amount of US money, 
        // determine the minimum number of coins required to equal that 
        // amount. Use on quarters, dimes, nickels and pennies. There are 
        // two approaches to this problem. The first uses modulo division 
        // and the second uses loops. You are not allowed to solve using
        // modulo division. For example, given 2.63, you would need 10 
        // quarters, 1 dime and 3 pennies, for a total of 14 coins.
        // You will probably find it necessary to use the Round method 
        // from the Math class to avoid floating-point errors. Since you 
        // are dealing with US currency/coins, I'd suggest rounding the 
        // results of each computation to 2 decimal places.
        public static int Test7(double amount)
        {
            int coins = 0;
            while (amount>= 0.25)
            {
                 coins++;
                amount = Math.Round(amount - 0.25, 2);
            }
            while (amount >= 0.1)
            {
                coins++;
                amount = Math.Round(amount - 0.1, 2);
            }
            while (amount >= 0.05)
            {
                coins++;
                amount = Math.Round(amount - 0.05, 2);
            }
            while (amount >= 0.01)
            {
                coins++;
                amount = Math.Round(amount - 0.01, 2);
            }
            return coins;
        }

        // Test 8 – Return the multiples
        // Given two int's factor and qty, find the first qty multiples of 
        // factor (including factor as the first multiple) and add each to 
        // a string (separate each multiple with a single space). For 
        // example, given 5 (factor) and 7 (qty), the resulting string 
        // would be 5 10 15 20 25 30 35
        public static string Test8(int factor, int qty)
        {
            string multiples = "";
            for(int cntr = 1; cntr <= qty; cntr++)
            {
                int answer = factor * cntr;
                multiples += answer + " ";
            }
            return multiples;
        }

        // Test 9 – Sum of values
        // Given two int's start and end, find the sum of all values between 
        // start and end (inclusive). For example, given 11 (start) and 19 
        // (end), the result is 135
        public static int Test9(int start, int end)
        {
            int sum = 0;
            for(int cntr = start;cntr <= end; cntr++)
            {
                sum = cntr + sum;
            }
            return sum;
        }

        // Test 10 – Sum of values
        // Given an instance of the Random class, gener, use it to generate 
        // qty random integers in the range min (inclusive) to max (exclusive).
        // Find the and return the sum of the random numbers you generate. For 
        // example, given gener, 3, 7, 5, you will generate 5 random numbers 
        // between 3 and 7 (actually 3 and 6 because 7 is excluded) and find 
        // the sum of those 5 numbers. Return the sum
        // NOTE: You are given the Random object (gener) so you should not 
        // declare/instantiate another Random object
        public static int Test10(Random gener, int min, int max, int qty)
        {
            int sum = 0;
            for (int cntr = 0; cntr < qty; cntr++)
                sum = sum + gener.Next(min, max);
            return sum;
        }
    }
}
