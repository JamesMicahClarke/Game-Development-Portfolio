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
    public partial class SettingsDialog : Form
    {
        public SettingsDialog()
        {
            InitializeComponent();
        }
        public int NumberI
        {
            get { return (int)numericUpDownI.Value; }
            set { numericUpDownI.Value = value; }
        }
        public int NumberW
        {
            get { return (int)numericUpDownW.Value; }
            set { numericUpDownW.Value = value; }
        }
        public int NumberH
        {
            get { return (int)numericUpDownH.Value; }
            set { numericUpDownH.Value = value; }
        }
    }
}
