using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.IO;

namespace Class2_Startup
{
    public partial class Form1 : Form
    {
        // The universe array
        bool[,] universe = new bool[10, 10];

        //scracthpad array
        bool[,] scratchPad = new bool[10, 10];

        // Drawing colors
        Color gridColor = Color.Black;
        Color cellColor = Color.Gray;

        // The Timer class
        Timer timer = new Timer();

        // Generation count
        int generations = 0;
        //Living count
        int living = 0;
        //Grid Toggle
        bool IsGridVisible = true;
        //Neighbor count Toggle
        bool IsNeighborVisible = false;

        public Form1()
        {
            InitializeComponent();

            // Setup the timer
            timer.Interval = 100; // milliseconds
            timer.Tick += Timer_Tick;
            timer.Enabled = false; // start timer running

            graphicsPanel1.BackColor = Properties.Settings.Default.PanelColor;
            cellColor = Properties.Settings.Default.CellColor;
            gridColor = Properties.Settings.Default.GridColor;

        }

        // Calculate the next generation of cells
        private void NextGeneration()
        {
            for (int y = 0; y < universe.GetLength(1); y++)
            {
                for (int x = 0; x < universe.GetLength(0); x++)
                {
                    int count;

                    //toggles Toroidal and Finite
                    if (toroidalToolStripMenuItem.Checked == true)
                    {
                        count = CountNeighborsToroidal(x, y);
                        finiteToolStripMenuItem.Checked = false;
                    }
                    else if(finiteToolStripMenuItem.Checked == true)
                    {
                        count = CountNeighborsFinite(x, y);
                        toroidalToolStripMenuItem.Checked = false;
                    }
                    else
                    {
                        count = CountNeighborsToroidal(x, y);
                    }
                     //CountNeighborsFinite(x, y);
                    // !!!
                    //apply rules
                    scratchPad[x, y] = false;
                    if (universe[x, y] == true)
                    {
                        //Living cells with less than 2 living neighbors die in the next generation.
                        if (count < 2)
                        {
                            scratchPad[x, y] = false;
                        }
                        //Living cells with more than 3 living neighbors die in the next generation.
                        if (count > 3)
                        {
                            scratchPad[x, y] = false;
                        }
                        //Living cells with 2 or 3 living neighbors live in the next generation.
                        if (count == 2 || count == 3)
                        {
                            scratchPad[x, y] = true;
                        }

                    }
                    //Dead cells with exactly 3 living neighbors live in the next generation.
                    else if (universe[x, y] == false)
                    {
                        if (count == 3)
                            scratchPad[x, y] = true;
                    }


                    //turn cells on or off in scratchPad array
                    //scratchPad[x, y] = !scratchPad[x, y];
                }
            }

            //copy scratchPad in universe
            bool[,] temp = universe;
            universe = scratchPad;
            scratchPad = temp;

            // Increment generation count
            generations++;

            // Update status strip generations
            toolStripStatusLabelGenerations.Text = "Generations = " + generations.ToString();
            LivingCells();

            //Invalidate
            graphicsPanel1.Invalidate();

        }

        // The event called by the timer every Interval milliseconds.
        private void Timer_Tick(object sender, EventArgs e)
        {
            NextGeneration();
        }

        private void graphicsPanel1_Paint(object sender, PaintEventArgs e)
        {
            //DO NOT CALL INVALIDATE!!!
            // Calculate the width and height of each cell in pixels
            // CELL WIDTH = WINDOW WIDTH / NUMBER OF CELLS IN X
            int cellWidth = graphicsPanel1.ClientSize.Width / universe.GetLength(0);
            // CELL HEIGHT = WINDOW HEIGHT / NUMBER OF CELLS IN Y
            int cellHeight = graphicsPanel1.ClientSize.Height / universe.GetLength(1);

            // A Pen for drawing the grid lines (color, width)
            Pen gridPen = new Pen(gridColor, 1);

            // A Brush for filling living cells interiors (color)
            Brush cellBrush = new SolidBrush(cellColor);

            // Iterate through the universe in the y, top to bottom
            for (int y = 0; y < universe.GetLength(1); y++)
            {
                // Iterate through the universe in the x, left to right
                for (int x = 0; x < universe.GetLength(0); x++)
                {
                    // A rectangle to represent each cell in pixels
                    Rectangle cellRect = Rectangle.Empty;
                    cellRect.X = x * cellWidth;
                    cellRect.Y = y * cellHeight;
                    cellRect.Width = cellWidth;
                    cellRect.Height = cellHeight;

                    // Fill the cell with a brush if alive
                    if (universe[x, y] == true)
                    {
                        e.Graphics.FillRectangle(cellBrush, cellRect);
                    }

                    Font font = new Font("Arial", 20f);

                    StringFormat stringFormat = new StringFormat();
                    stringFormat.Alignment = StringAlignment.Center;
                    stringFormat.LineAlignment = StringAlignment.Center;

                    int neighbors = CountNeighborsToroidal(x, y); //CountNeighborsFinite(x,y);

                    if (IsNeighborVisible == true)
                    {
                        if (neighbors > 0)
                            e.Graphics.DrawString(neighbors.ToString(), font, Brushes.Black, cellRect, stringFormat);
                    }

                    if (IsGridVisible == true)
                    {
                        // Outline the cell with a pen
                        e.Graphics.DrawRectangle(gridPen, cellRect.X, cellRect.Y, cellRect.Width, cellRect.Height);
                    }
                }
            }



            // Cleaning up pens and brushes
            gridPen.Dispose();
            cellBrush.Dispose();
        }

        private void graphicsPanel1_MouseClick(object sender, MouseEventArgs e)
        {
            // If the left mouse button was clicked
            if (e.Button == MouseButtons.Left)
            {
                // Calculate the width and height of each cell in pixels
                int cellWidth = graphicsPanel1.ClientSize.Width / universe.GetLength(0);
                int cellHeight = graphicsPanel1.ClientSize.Height / universe.GetLength(1);

                // Calculate the cell that was clicked in
                // CELL X = MOUSE X / CELL WIDTH
                int x = e.X / cellWidth;
                // CELL Y = MOUSE Y / CELL HEIGHT
                int y = e.Y / cellHeight;

                // Toggle the cell's state
                universe[x, y] = !universe[x, y];

                // Tell Windows you need to repaint
                graphicsPanel1.Invalidate();
            }
        }

        //exit 
        private void exitToolStripMenuItem_Click(object sender, EventArgs e)
        {
            this.Close();//closes the form
        }

        private void newToolStripMenuItem_Click(object sender, EventArgs e)
        {
            for (int y = 0; y < universe.GetLength(1); y++)
            {
                for (int x = 0; x < universe.GetLength(0); x++)
                {
                    universe[x, y] = false;
                }
            }
            graphicsPanel1.Invalidate();
        }

        //Finite Method
        private int CountNeighborsFinite(int x, int y)
        {
            int count = 0;
            int xLen = universe.GetLength(0);
            int yLen = universe.GetLength(1);
            for (int yOffset = -1; yOffset <= 1; yOffset++)
            {
                for (int xOffset = -1; xOffset <= 1; xOffset++)
                {
                    int xCheck = x + xOffset;
                    int yCheck = y + yOffset;
                    // if xOffset and yOffset are both equal to 0 then continue
                    if (xOffset == 0 && yOffset == 0)
                        continue;
                    // if xCheck is less than 0 then continue
                    if (xCheck < 0)
                        continue;
                    // if yCheck is less than 0 then continue
                    if (yCheck < 0)
                        continue;
                    // if xCheck is greater than or equal too xLen then continue
                    if (xCheck >= xLen)
                        continue;
                    // if yCheck is greater than or equal too yLen then continue
                    if (yCheck >= yLen)
                        continue;

                    if (universe[xCheck, yCheck] == true) count++;
                }
            }
            return count;
        }

        //Toroidal Method
        private int CountNeighborsToroidal(int x, int y)
        {
            int count = 0;
            int xLen = universe.GetLength(0);
            int yLen = universe.GetLength(1);
            for (int yOffset = -1; yOffset <= 1; yOffset++)
            {
                for (int xOffset = -1; xOffset <= 1; xOffset++)
                {
                    int xCheck = x + xOffset;
                    int yCheck = y + yOffset;
                    // if xOffset and yOffset are both equal to 0 then continue
                    if (xOffset == 0 && yOffset == 0)
                        continue;
                    // if xCheck is less than 0 then set to xLen - 1
                    if (xCheck < 0)
                        xCheck = xLen - 1;
                    // if yCheck is less than 0 then set to yLen - 1
                    if (yCheck < 0)
                        yCheck = yLen - 1;
                    // if xCheck is greater than or equal too xLen then set to 0
                    if (xCheck >= xLen)
                        xCheck = 0;
                    // if yCheck is greater than or equal too yLen then set to 0
                    if (yCheck >= yLen)
                        yCheck = 0;

                    if (universe[xCheck, yCheck] == true) count++;
                }
            }
            return count;
        }

        //start button
        private void toolStripButton1_Click(object sender, EventArgs e)
        {
            this.timer.Start();
        }

        //pause button
        private void toolStripButton2_Click(object sender, EventArgs e)
        {
            this.timer.Stop();
        }

        //next button
        private void toolStripButton3_Click(object sender, EventArgs e)
        {
            NextGeneration();
        }

        //clear button
        private void toolStripButton4_Click(object sender, EventArgs e)
        {
            timer.Stop();
            for (int y = 0; y < universe.GetLength(1); y++)
            {
                for (int x = 0; x < universe.GetLength(0); x++)
                {

                    scratchPad[x, y] = false;
                }
            }

            bool[,] temp = universe;
            universe = scratchPad;
            scratchPad = temp;
            graphicsPanel1.Invalidate();



        }

        //Living cells
        private void LivingCells()
        {
            living = 0;
            for (int y = 0; y < universe.GetLength(1); y++)
            {
                for (int x = 0; x < universe.GetLength(0); x++)
                {

                    if (universe[x, y] == true)
                    {
                        living++;

                    }

                }
            }
            toolStripStatusLabel3.Text = "Living = " + living;
        }

        //Randomize(time)
        private void timeToolStripMenuItem_Click(object sender, EventArgs e)
        {
            
            Random rand = new Random();

            for (int y = 0; y < universe.GetLength(1); y++)
            {
                for (int x = 0; x < universe.GetLength(0); x++)
                {
                    int num = rand.Next(0, 2);

                    if (num == 0)
                    {
                        scratchPad[x, y] = true;
                    }
                    else
                    {
                        scratchPad[x, y] = false;
                    }
                }
            }
            bool[,] temp = universe;
            universe = scratchPad;
            scratchPad = temp;
            graphicsPanel1.Invalidate();
        }

        //Randomize(seed)
        private void seedToolStripMenuItem_Click(object sender, EventArgs e)
        {
            SeedDialog dlg = new SeedDialog();
            if (DialogResult.OK == dlg.ShowDialog())
            {
                Random rand = new Random(dlg.Seed);

                for (int y = 0; y < universe.GetLength(1); y++)
                {
                    for (int x = 0; x < universe.GetLength(0); x++)
                    {
                        int num = rand.Next(0, 2);

                        if (num == 0)
                        {
                            scratchPad[x, y] = true;
                        }
                        else
                        {
                            scratchPad[x, y] = false;
                        }
                    }
                }
                bool[,] temp = universe;
                universe = scratchPad;
                scratchPad = temp;
            }
            graphicsPanel1.Invalidate();
        }

        //Save As
        private void saveToolStripMenuItem_Click(object sender, EventArgs e)
        {
            SaveFileDialog dlg = new SaveFileDialog();
            dlg.Filter = "All Files|*.*|Cells|*.cells";
            dlg.FilterIndex = 2; dlg.DefaultExt = "cells";


            if (DialogResult.OK == dlg.ShowDialog())
            {
                StreamWriter writer = new StreamWriter(dlg.FileName);

                // Write any comments you want to include first.
                // Prefix all comment strings with an exclamation point.
                // Use WriteLine to write the strings to the file. 
                // It appends a CRLF for you.
                writer.WriteLine("!Saved at : " + DateTime.Now);

                // Iterate through the universe one row at a time.
                for (int y = 0; y < universe.GetLength(1); y++)
                {
                    // Create a string to represent the current row.
                    String currentRow = string.Empty;

                    // Iterate through the current row one cell at a time.
                    for (int x = 0; x < universe.GetLength(0); x++)
                    {
                        // If the universe[x,y] is alive then append 'O' (capital O)
                        // to the row string.
                        if (universe[x, y] == true)
                        {
                            currentRow += 'O';
                        }
                        // Else if the universe[x,y] is dead then append '.' (period)
                        // to the row string.
                        else if (universe[x, y] == false)
                        {
                            currentRow += '.';
                        }
                    }

                    // Once the current row has been read through and the 
                    // string constructed then write it to the file using WriteLine.
                    writer.WriteLine(currentRow);
                }

                // After all rows and columns have been written then close the file.
                writer.Close();
            }
        }

        //Open
        private void openToolStripMenuItem_Click(object sender, EventArgs e)
        {
            OpenFileDialog dlg = new OpenFileDialog();
            dlg.Filter = "All Files|*.*|Cells|*.cells";
            dlg.FilterIndex = 2;

            if (DialogResult.OK == dlg.ShowDialog())
            {
                StreamReader reader = new StreamReader(dlg.FileName);

                // Create a couple variables to calculate the width and height
                // of the data in the file.
                int maxWidth = 0;
                int maxHeight = 0;

                // Iterate through the file once to get its size.
                while (!reader.EndOfStream)
                {
                    // Read one row at a time.
                    string row = reader.ReadLine();

                    // If the row begins with '!' then it is a comment
                    // and should be ignored.
                    if (row[0].ToString() == "!")
                    {
                        continue;
                    }
                    // If the row is not a comment then it is a row of cells.
                    // Increment the maxHeight variable for each row read.
                    if (row[0].ToString() != "!")
                    {
                        maxHeight++;
                    }
                    // Get the length of the current row string
                    // and adjust the maxWidth variable if necessary.
                    maxWidth = row.Length;
                }

                // Resize the current universe and scratchPad
                // to the width and height of the file calculated above.
                universe = new bool[maxWidth, maxHeight];
                scratchPad = new bool[maxWidth, maxHeight];

                // Reset the file pointer back to the beginning of the file.
                reader.BaseStream.Seek(0, SeekOrigin.Begin);

                int yPos = 0;
                // Iterate through the file again, this time reading in the cells.
                while (!reader.EndOfStream)
                {
                    // Read one row at a time.
                    string row = reader.ReadLine();

                    // If the row begins with '!' then
                    // it is a comment and should be ignored.
                    if (row[0].ToString() == "!")
                    {
                        continue;
                    }
                    // If the row is not a comment then 
                    // it is a row of cells and needs to be iterated through.
                    if (row[0].ToString() != "!")
                    {
                        for (int xPos = 0; xPos < row.Length; xPos++)
                        {

                            // If row[xPos] is a 'O' (capital O) then
                            // set the corresponding cell in the universe to alive.
                            if (row[xPos] == 'O')
                            {
                                universe[xPos, yPos] = true;
                            }
                            // If row[xPos] is a '.' (period) then
                            // set the corresponding cell in the universe to dead.

                            if (row[xPos] == '.')
                            {
                                universe[xPos, yPos] = false;
                            }
                        }

                    }
                    yPos++;
                    graphicsPanel1.Invalidate();
                }

                // Close the file.
                reader.Close();
            }
        }

        //Neighbors toggle
        private void neighborsToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (neighborsToolStripMenuItem.Checked == true)
            {
                IsNeighborVisible = true;
                graphicsPanel1.Invalidate();
            }
            else
            {
                IsNeighborVisible = false;
                graphicsPanel1.Invalidate();
            }

        }

        //Grid Toggle
        private void gridToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (gridToolStripMenuItem.Checked == true)
            {
                IsGridVisible = false;
                gridToolStripMenuItem2.Checked = true;
            }
            else
            {
                IsGridVisible = true;
                gridToolStripMenuItem2.Checked = false;
            }
            graphicsPanel1.Invalidate();
        }

        //Universe Speed (Intervals)
        private void speedSizeToolStripMenuItem_Click(object sender, EventArgs e)
        {
            SettingsDialog dlg = new SettingsDialog();
            dlg.NumberI = timer.Interval;
            if (DialogResult.OK == dlg.ShowDialog())
            {
                timer.Interval = dlg.NumberI;
                universe = new bool[dlg.NumberW, dlg.NumberH];
                scratchPad = new bool[dlg.NumberW, dlg.NumberH];
                
            }
            graphicsPanel1.Invalidate();
        }

        //Color save when exit
        private void Form1_FormClosed(object sender, FormClosedEventArgs e)
        {
            Properties.Settings.Default.PanelColor = graphicsPanel1.BackColor;
            Properties.Settings.Default.CellColor = cellColor;
            Properties.Settings.Default.GridColor = gridColor;

            Properties.Settings.Default.Save();
        }

        //Background color 
        private void backgroundToolStripMenuItem_Click(object sender, EventArgs e)
        {
            ColorDialog dlg = new ColorDialog();

            dlg.Color = graphicsPanel1.BackColor;
            if (dlg.ShowDialog() == DialogResult.OK)
            {
                graphicsPanel1.BackColor = dlg.Color;
            }
        }

        //Reset Color
        private void resetToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Properties.Settings.Default.Reset();
            graphicsPanel1.BackColor = Properties.Settings.Default.PanelColor;
            cellColor = Properties.Settings.Default.CellColor;
            gridColor = Properties.Settings.Default.GridColor;

            graphicsPanel1.Invalidate();
        }

        //Reload Color
        private void reloadToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Properties.Settings.Default.Reload();
            graphicsPanel1.BackColor = Properties.Settings.Default.PanelColor;
            cellColor = Properties.Settings.Default.CellColor;
            gridColor = Properties.Settings.Default.GridColor;

            graphicsPanel1.Invalidate();
        }

        //Cell Color
        private void cellToolStripMenuItem_Click(object sender, EventArgs e)
        {
            
            ColorDialog dlg = new ColorDialog();

            dlg.Color = cellColor;
            if (dlg.ShowDialog() == DialogResult.OK)
            {
                 cellColor = dlg.Color;
            }
            graphicsPanel1.Invalidate();
        }

        //Grid Color
        private void gridToolStripMenuItem1_Click(object sender, EventArgs e)
        {
            ColorDialog dlg = new ColorDialog();

            dlg.Color = gridColor;
            if (dlg.ShowDialog() == DialogResult.OK)
            {
                gridColor = dlg.Color;
            }
            graphicsPanel1.Invalidate();
        }

        //Grid Toggle (Context menu)
        private void gridToolStripMenuItem2_Click(object sender, EventArgs e)
        {
            if (gridToolStripMenuItem2.Checked == true)
            {
                IsGridVisible = false;
                gridToolStripMenuItem.Checked = true;
            }
            else
            {
                IsGridVisible = true;
                gridToolStripMenuItem.Checked = false;
            }
            graphicsPanel1.Invalidate();
        }

        //Neighbors Toggle (Context menu)
        private void neighborsToolStripMenuItem1_Click(object sender, EventArgs e)
        {
            if (neighborsToolStripMenuItem1.Checked == true)
            {
                IsNeighborVisible = true;
                graphicsPanel1.Invalidate();
                neighborsToolStripMenuItem.Checked = true;
            }
            else
            {
                IsNeighborVisible = false;
                graphicsPanel1.Invalidate();
                neighborsToolStripMenuItem.Checked = false;
            }
        }
    }


}
