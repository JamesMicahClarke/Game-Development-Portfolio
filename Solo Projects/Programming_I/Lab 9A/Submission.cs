using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Lab_9A
{
    public class Submission
    {
        public static Student[] enrollment = new Student[0];
        public static Student Test1(string last, string first, int idNo)
        {
            Student mark = new Student(last, first, idNo);
            return mark;
        }

        public static Student Test2()
        {
            Student got = new Student();
            return got;
        }

        public static bool Test3(Student enrolled)
        {
            bool pass = false;
            for(int indx = 0; indx < enrollment.Length; indx++)
            if(enrollment[indx] == null)
            {
                enrollment[indx] = enrolled;
                    pass = true;
                    break;
            }
            return pass;
        }

        public static bool Test4(int idNumber)
        {
            Student get = new Student();
            bool correct = false;
            for (int indx = 0; indx < enrollment.Length; indx++)
            {
                if (enrollment[indx] != null && enrollment[indx].GetIDNumber() == idNumber)
                {
                        enrollment[indx] = null;
                        correct = true;
                        break;
                   
                }
            }
            return correct;
        }

        public static Student Test5(int idNumber)
        {
            Student retrieve = null;
                foreach(Student element in enrollment)
                {
                if (element != null && element.GetIDNumber() == idNumber)
                {
                    retrieve = element;
                    break;

                }
                    
                }
            

            return retrieve;
        }
    }
}
