using System;
using System.Diagnostics.Contracts;
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

        // Test 1 – Convert char array to int array
        // Given an array of char, phrase, convert each element to an
        // equivalent int value and place in an int array.
        // Return the int array
        public static int[] Test1(char[] phrase)
        {
            int[] answer = new int[phrase.Length];
            for (int ndx = 0; ndx < phrase.Length; ndx++)
            {
                answer[ndx] = phrase[ndx];
            }
            return answer;
        }

        // Test 2 - Array statistics
        // Given an array of double, data, find the smallest element, 
        // the largest element and the numeric mean (average). Store the 
        // results in an array (in that order: smallest, largest, mean).
        // Return the array
        public static double[] Test2(double[] data)
        {
            double[] stats = new double[3];
           double smallest = data[0];
            double largest = data[0];
            double average = 0;
            for (int cntr = 0; cntr < data.Length; cntr++)
            {
                if (data[cntr] < smallest)
                    smallest = data[cntr];
                else if (data[cntr] > largest)
                    largest = data[cntr];
                average += data[cntr];
            }
            stats[0] = smallest;
            stats[1] = largest;
            stats[2] = average / data.Length;
            return stats;
        }

        // Test 3 - Normalize an array (of double)
        // Given an array of double, numbers, normalize the array. To 
        // normalize an array:
        // 1) Find the largest element stored in the array
        // 2) Divide each element in the array by the largest value
        //    and replace each array element with the result of the 
        //    division.
        // Since the array's contents are being modified, there is 
        // nothing to return
        public static void Test3(double[] numbers)
        {
            double largest = numbers[0];
            for (int cntr = 1; cntr < numbers.Length; cntr++)
            {
                if(numbers[cntr] > largest)
                largest = numbers[cntr];
            }
            for (int ndx = 0; ndx < numbers.Length; ndx++)
            {
                numbers[ndx] /= largest;
            }
        }

        // Test 4 - Uniqueness
        // Given an array of string, names, verify that each name is unique
        // mean that none of the names are duplicated within the array.
        // If the array is unique, return true; otherwise, return false
        public static bool Test4(string [] names)
        {
            bool answer = true;
            for(int i = 0; i < names.Length; i++)
            {
                for(int j = i + 1; j < names.Length; j++)
                {
                    if(names[i] == names[j])
                    {
                        answer = false;
                    }
                }
            }
            return answer;
        }

        // Test 5 - Acronym
        // Given an array of string, words, create a string that is the 
        // acronym (first letter of each word). Return the string
        public static string Test5(string [] words)
        {
            string Acronym = "";
            foreach(string Word in words)
            {
                Acronym += Word[0] + "";
            }
            return Acronym;
        }

        // Test 6 - Array reverse
        // Given a char array, letters, create another array that has the
        // same elements but in reverse order. Return the array
        // 
        // You are not allowed to use Array.Reverse (or any existing
        // method) to reverse the array
        //
        public static char[] Test6(char[] letters)
        {
            char[] backward = new char[letters.Length];
            int left = 0;
            int right = letters.Length - 1;
            while (left < letters.Length)
            {
                backward[left] = letters[right];
                left++;
                right--;
            }
            return backward;
        }

        // Test 7 - Transpose array
        // Given a 2-Dimension array of int, table, create a new array that 
        // 'transposes' the original array. Transposing means that each row 
        // in the original array will be a column in the new array and each
        // column in the original array will be a row in the new array.
        // For example, given
        //   4   3   1   5
        //   2   7   0   8
        //
        // The transposed array would be
        //   4   2
        //   3   7
        //   1   0
        //   5   8
        //
        public static int[,] Test7(int [,] table)
        {
            int[,] xyz = new int[table.GetLength(1), table.GetLength(0)];
            for(int outer = 0; outer < table.GetLength(0); outer++)
            {
                for(int inner = 0; inner < table.GetLength(1); inner++)
                {
                    xyz[inner, outer] = table[outer, inner];
                }
            }
            return xyz;
        }

        // Test 8 – Return a 2D array
        // Given three arrays of the same type (int) and size, combine the 
        // arrays into a single 2D array. Return the 2D array
        // NOTE: This solution requires a single loop (not three)
        // 
        public static int [,] Test8(int [] mins, int [] maxes, int [] seeds)
        {
            int[,] answer = new int[3, mins.Length];
            for (int ndx = 0; ndx < mins.Length; ndx++)
            {
                answer[0, ndx] = mins[ndx];
                answer[1, ndx] = maxes[ndx];
                answer[2, ndx] = seeds[ndx];
            }
            return answer;
        }

        // Test 9 – Convert int array to char array
        // Given an array of int, ascii, convert each element to an
        // equivalent char value and place in a char array.
        // Return the char array
        public static char[] Test9(int[] ascii)
        {
            char[] charArray = new char[ascii.Length];
            for (int i = 0; i < ascii.Length; i++)
            {
                charArray[i] = (char)ascii[i];
            }
            return charArray;
        }

        // Test 10 – Modify an existing array
        // Given an array of char (all uppercase), modify the array so
        // that every other element will be lowercase (even indexes are 
        // upper, odd indexes are lower)
        public static void Test10(char[] word)
        {
            for (int i = 0; i < word.Length; ++i)
            {
                if (Char.IsUpper(word[i]) && i % 2 == 1)
                {
                    word[i] = Char.ToLower(word[i]);
                }
            }
        }
    }
}
