using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Class2_Startup
{
    public partial class SeedDialog : Form
    {
        public SeedDialog()
        {
            InitializeComponent();
        }
        public int Seed
        {
            get { return (int)numericUpDownRandom.Value; }
            set { numericUpDownRandom.Value = value; }
        }
        private void buttonSeedRand_Click(object sender, EventArgs e)
        {
            Random rnd = new Random();
            int number = rnd.Next(0,3001);
            numericUpDownRandom.Value = number;
        }
    }
}
