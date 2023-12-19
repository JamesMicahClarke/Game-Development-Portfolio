using System;
using System.Text;
using Lab_7A;

namespace FSPG1
{
    public class Submission
    {
        public static StringBuilder Test1(string[] names)
        {
            StringBuilder sb = new StringBuilder();
            string[] newString = names;
            for (int i = 0; i < newString.Length; i++)
            {
                sb.Append(newString[i][0]);
            }
            return sb;
        }

        public static object Test2(float x, float y, float radius)
        {

            Circle c1 = new Circle(x, y, radius);
            return c1;
        }
        public static object Test3(float x, float y, float radius)
        {
            Circle c1 = new Circle(x, y, radius);
            return c1;
        }

        public static object Test4(float x, float y, float radius)
        {
            Circle c1 = new Circle(x, y, radius);
            return c1;
        }

        public static object Test5(float x, float y, float radius)
        {
            Circle c1 = new Circle(x, y, radius);
            return c1;
        }

        public static int Test6(string str1, string str2, bool ignoreCase)
        {
            return String.Compare(str1, str2, ignoreCase);
        }

        public static string Test7(sbyte offset, string message)
        {
            TextCodec codec = new TextCodec(offset);
            string answer = codec.Encode(message);
            return answer;
        }

        public static string Test8(sbyte offset, string message)
        {
            TextCodec codec = new TextCodec(offset);
            string answer = codec.Decode(message);
            return answer;
        }
    }
}
