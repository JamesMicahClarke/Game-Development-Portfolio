using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Newtonsoft.Json;

namespace Lab1
{
    class Program
    {
        static void Main(string[] args)
        { //Not finished
            string[] see = new string[] { };
            string pass = Console.ReadLine();
            string filePath = @"speech.csv";
            int read = 0;
           Dictionary<string, int> words = new Dictionary<string, int>(StringComparer.CurrentCultureIgnoreCase);
            //ReadInteger(pass, read, read);
            //ReadString(pass, ref pass);

            //GetSpeech();
            GetSpeechFromFile();

            char[] breaks = new char[] { ',', '.', ' ', '!', ';', ':', '-', '\n', '\t', '\r' };
            string[] values = GetSpeechFromFile().Split(breaks, StringSplitOptions.RemoveEmptyEntries);
            List<string> speech = new List<string>(values);

            for (int i = 0; i < speech.Count; i++)
            {
                bool inDiction = words.TryGetValue(speech[i], out int wcount);
                if (inDiction)
                {
                    words[speech[i]]++;
                }
                else
                {
                    words.Add(speech[i], wcount);
                }

            }

            foreach (KeyValuePair<string, int> form in words)
            {
                Console.Write(form.Value);
                Console.Write(form.Key);
                Console.CursorLeft = 20;
                Console.BackgroundColor = ConsoleColor.Green;
                for (int s = 0; s < words.Count; s++)
                {
                    Console.Write(speech[s]);
                }
                Console.BackgroundColor = ConsoleColor.Black;
            }

            string newprompt = "What word are you looking for?";
            ReadString("Word: ", ref newprompt);
            /*if ()
            {

            }
            */

            string menuselection = Console.ReadLine();
           while(menuselection != "exit")
            {
                ReadChoice(pass, see, out read);
                switch (menuselection)
                {
                    case "1":
                        
                        Console.WriteLine("What would you like to name the file?");
                        string fileName = Console.ReadLine();
                        ReadString("File name:", ref fileName);

                        filePath = Path.ChangeExtension(filePath, ".json");
                        using (StreamWriter sw = new StreamWriter(filePath))
                        {
                            using (JsonTextWriter jtw = new JsonTextWriter(sw))
                            {
                                JsonSerializer cereal = new JsonSerializer();
                                cereal.Serialize(jtw, words);
                            }
                        }
                            continue;
                    case "2":
                        Console.WriteLine("Please enter the name of the file you wish to load");
                        fileName = Console.ReadLine();
                        ReadString("Load file:", ref fileName);

                        if (File.Exists(filePath))
                        {
                            string jsonText = File.ReadAllText(filePath);
                            try
                            {
                                words = JsonConvert.DeserializeObject<Dictionary<string, int>>(jsonText);
                            }
                            catch (Exception)
                            {
                                Console.WriteLine("There was an Exception problem");
                            }
                        }
                        else
                            Console.WriteLine("It seems the name of that File does not exist");
                        continue;
                    case "3":
                        Console.WriteLine("Please choose a word to remove");
                        string wordRemove = Console.ReadLine();
                        ReadString("Remove:", ref wordRemove);
                        bool removal = words.Remove(wordRemove);
                        if (removal != true)
                        {
                            Console.WriteLine($"{wordRemove} is not found");
                        }
                        continue;
                    case "exit":
                        break;
                }
            }
        }
        #region Part A
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

        #endregion
        #region Part B
        public static string GetSpeech()
        { //Not finished
            string text = "I say to you today, my friends, so even though we face the difficulties of today and tomorrow, I still have a dream. It is a dream deeply rooted in the American dream. " +
            "I have a dream that one day this nation will rise up and live out the true meaning of its creed: We hold these truths to be self-evident: that all men are created equal. " +
            "I have a dream that one day on the red hills of Georgia the sons of former slaves and the sons of former slave owners will be able to sit down together at the table of brotherhood. " +
            "I have a dream that one day even the state of Mississippi, a state sweltering with the heat of injustice, sweltering with the heat of oppression, will be transformed into an oasis of freedom and justice. " +
            "I have a dream that my four little children will one day live in a nation where they will not be judged by the color of their skin but by the content of their character. " +
            "I have a dream today. I have a dream that one day, down in Alabama, with its vicious racists, with its governor having his lips dripping with the words of interposition and nullification; one day right there in Alabama, little black boys and black girls will be able to join hands with little white boys and white girls as sisters and brothers. " +
            "I have a dream today. I have a dream that one day every valley shall be exalted, every hill and mountain shall be made low, the rough places will be made plain, and the crooked places will be made straight, and the glory of the Lord shall be revealed, and all flesh shall see it together. " +
            "This is our hope. This is the faith that I go back to the South with. With this faith we will be able to hew out of the mountain of despair a stone of hope. With this faith we will be able to transform the jangling discords of our nation into a beautiful symphony of brotherhood. " +
            "With this faith we will be able to work together, to pray together, to struggle together, to go to jail together, to stand up for freedom together, knowing that we will be free one day. " +
            "This will be the day when all of God's children will be able to sing with a new meaning, My country, 'tis of thee, sweet land of liberty, of thee I sing. Land where my fathers died, land of the pilgrim's pride, from every mountainside, let freedom ring. " +
            "And if America is to be a great nation this must become true. So let freedom ring from the prodigious hilltops of New Hampshire. Let freedom ring from the mighty mountains of New York. Let freedom ring from the heightening Alleghenies of Pennsylvania! " +
            "Let freedom ring from the snowcapped Rockies of Colorado! Let freedom ring from the curvaceous slopes of California! But not only that; let freedom ring from Stone Mountain of Georgia! " +
            "Let freedom ring from Lookout Mountain of Tennessee! Let freedom ring from every hill and molehill of Mississippi. From every mountainside, let freedom ring. " +
            "And when this happens, when we allow freedom to ring, when we let it ring from every village and every hamlet, from every state and every city, we will be able to speed up that day when all of God's children, black men and white men, Jews and Gentiles, Protestants and Catholics, will be able to join hands and sing in the words of the old Negro spiritual, Free at last! free at last! thank God Almighty, we are free at last!";
           
            return text;
        }
        #endregion
        #region Part C
        public static string GetSpeechFromFile()
        {
            char[] delims = new char[] { ',', '.', ' ', '!', ';', ':', '-', '\n', '\t', '\r' };
            string filePath = @"speech.csv";
            string speech = string.Empty;
            using (StreamReader sr = new StreamReader(filePath))
            {
                speech = sr.ReadToEnd();
            }
            return speech;
        }
        #endregion
    }
}
