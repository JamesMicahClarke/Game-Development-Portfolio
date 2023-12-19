using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;

namespace Lab_3
{
    class Program
    {
        static void Main(string[] args)
        {
            string[] options = new string[] { "1. Bubble Sort", "2. Merge Sort", "3. Binary Search", "4. Exit" };
            int menuSelection = 0;
            string replace = "";
            int place = 0;
            while (menuSelection != 4)
            {
                ReadChoice("Menu:", options, out menuSelection);
                if (menuSelection == 1)
                {
                    Console.WriteLine("----------------------------------------------------Bubble Sort----------------------------------------------------");
                }
                else if (menuSelection == 2)
                {
                    Console.WriteLine("----------------------------------------------------Merge Sort----------------------------------------------------");
                }
                else if (menuSelection == 3)
                {
                    Console.WriteLine("----------------------------------------------------Binary Search----------------------------------------------------");
                }

                    List<string> load = new List<string>();
                Load(ref load);

                string first = "";
                
                for (int i = 0; i < load.Count; i++)
                {
                    first = load[i];



                    switch (menuSelection)
                    {
                        case 1:
                            bubbleSort(load);
                            Console.WriteLine(first);
                            break;
                        case 2:
                            MergeSort(load);
                            Console.WriteLine(first);
                            break;
                        case 3:
                            BinarySearch(load, replace, place, place);
                            Console.WriteLine(first);
                            break;
                        case 4:

                            break;
                    }
                }
            }
        }

        static List<string> Load(ref List<string> input2)
        {
            List<string> input = new List<string>();
            char[] delims = new char[] { ',', '\n', '\t', '\r' };
            string filePath = @"inputFile.csv";
            string inputFile = string.Empty;
            using (StreamReader sr = new StreamReader(filePath))
            {
                inputFile = sr.ReadToEnd();
            }

            input2 = inputFile.Split(delims).ToList();
            return input2;
        }
        static void bubbleSort(List<string> sort)
        {
            int length = sort.Count;
            bool swapped = true;
            while (swapped)
            {
                swapped = false;
                for (int i = 1; i <= length - 1; i++)
                {
                    int j = i;
                    //if (sort[i - 1] > sort[j])
                    //{

                    //    swapped = true;
                    //}
                    if (string.Compare(sort[i - 1], sort[j]) > 0)
                    {
                        Swap(sort, i - 1, j);

                        swapped = true;
                    }
                }
                length = length - 1;
            }
        }
        static void Swap(List<string> words, int i, int j)
        {
            string save = words[i];
            words[i] = words[j];
            words[j] = save;
        }


        static int BinarySearch(List<string> sort2, string search, int low, int high)
        {

            if (high < low)
            {
                return -1;

            }
            int mid = (low + high) / 2;
            if (string.Compare(sort2[mid], search) > 0)
            {
                return BinarySearch(sort2, search, low, mid - 1);
            }
            else if (string.Compare(sort2[mid], search) < 0)
            {
                return BinarySearch(sort2, search, mid + 1, high);
            }
            else
            {
                return mid;
            }
        }
        static List<string> MergeSort(List<string> merge)
        {
            if (merge.Count <= 1)
                return merge;

            List<string> right = new List<string>();

            List<string> left = new List<string>();

            for (int i = 0; i < merge.Count; i++)
            {

                if (i < (merge.Count / 2))
                {
                    left.Add(merge[i]);

                }
                else
                {
                    right.Add(merge[i]);

                }
            }

            left = MergeSort(left);
            right = MergeSort(right);

            return Merge(left, right);
        }

        static List<string> Merge(List<string> left, List<string> right)
        {
            List<string> result = new List<string>();


            while (left.Count != 0 && right.Count != 0)
            {
                if (string.Compare(left[0], right[0]) <= 0)
                {
                    result.Add(left[0]);
                    left.RemoveAt(0);
                }
                else
                {
                    result.Add(right[0]);
                    right.RemoveAt(0);
                }
            }
            while (left.Count != 0)
            {
                result.Add(left[0]);
                left.RemoveAt(0);
            }
            while (right.Count != 0)
            {
                result.Add(right[0]);
                right.RemoveAt(0);
            }
            return result;
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
