using System;
using System.Collections.Generic;
using System.Text;
using System.IO;
using System.IO.Pipes;
using FullSailAFI.GamePlaying.CoreAI;
using System.Security.Cryptography;

namespace FullSailAFI.GamePlaying
{
    public class StudentAI : Behavior
    {
        TreeVisLib treeVisLib;  // lib functions to communicate with TreeVisualization
        bool visualizationFlag = false;  // turn this on to use tree visualization (which you will have to implement via the TreeVisLib API)
                                         // WARNING: Will hang program if the TreeVisualization project is not loaded!

        public StudentAI()
        {
            if (visualizationFlag == true)
            {
                if (treeVisLib == null)  // should always be null, but just in case
                    treeVisLib = TreeVisLib.getTreeVisLib();  // WARNING: Creation of this object will hang if the TreeVisualization project is not loaded!
            }
        }

        //
        // This function starts the look ahead process to find the best move
        // for this player color.
        //
        public ComputerMove Run(int _nextColor, Board _board, int _lookAheadDepth)
        {

            ComputerMove nextMove = GetBestMove(_nextColor, _board, _lookAheadDepth);

            return nextMove;
        }

        //
        // This function uses look ahead to evaluate all valid moves for a
        // given player color and returns the best move it can find. This
        // method will only be called if there is at least one valid move
        // for the player of the designated color.
        //
        private ComputerMove GetBestMove(int color, Board board, int depth, double alpha = Double.NegativeInfinity, double beta = Double.PositiveInfinity)
        {
            //TODO: the lab
            ComputerMove best = null;
            Board state = new Board();
            List<ComputerMove> valid = new List<ComputerMove>();

            // defines list
            if (!state.HasAnyValidMove(color))
            {
                for (int i = 0; i < 8; i++)
                {

                    for (int j = 0; j < 8; j++)
                    {
                        if (board.IsValidMove(color, i, j))
                        {
                            ComputerMove tempMove = new ComputerMove(i, j);
                            valid.Add(tempMove);
                        }
                    }

                }
            }

            foreach (ComputerMove move in valid)
            {
                ComputerMove moveCopy = move;
                state.Copy(board);
                state.MakeMove(color, moveCopy.row, moveCopy.col);

                //evaluates next move
                if (state.IsTerminalState() || depth == 0)
                {
                    moveCopy.rank = Evaluate(state);
                }
                else
                {
                    moveCopy.rank = GetBestMove(GetNextPlayer(color, state), state, depth - 1).rank;
                }

                //if low, then good player, if high, good cpu
                if (best != null)
                {


                    if (color == 1)
                    {
                        if (moveCopy.rank > best.rank)// or if move is better than best move
                        {
                            best = moveCopy;
                        } 
                        if (best.rank < beta)
                        {
                            beta = best.rank;
                        }

                    }
                    else if (color == -1)
                    {

                        if (moveCopy.rank < best.rank)
                        {
                            best = moveCopy;
                        }
                        if (best.rank > alpha)
                        {
                            alpha = best.rank;
                        }
                    }
                    if (alpha >= beta)
                        break;
                }
                else
                {
                    best = moveCopy;
                }
            }
            return best;
        }

        #region Recommended Helper Functions

        private int Evaluate(Board mBoard)
        {
            //TODO: determine score based on position of pieces
            //int score = 0;

            //for (int i = 0; i < 8; i++)// row
            //{
            //    for (int j = 0; j < 8; j++) //column
            //    {
            //        int color = mBoard.GetSquareContents(i, j);

            //        if ((i == 0 && j == 0) || (i == 7 && j == 0) || (i == 0 && j == 7) || (i == 7 && j == 7))
            //        {
            //            score += color * 100;
            //        }
            //        else if (i == 0 || i == 7 || j == 0 || j == 7)
            //        {
            //            score += color * 10;
            //        }
            //        else
            //        {
            //            score += color;
            //        }
            //    }
            //}

            //if (mBoard.IsTerminalState())
            //{
            //    if (score > 0)
            //        score += 1000;
            //    else
            //        score -= 1000;
            //}

            //return score;
            return ExampleAI.MinimaxAFI.EvaluateTest(mBoard); // TEST WITH THIS FIRST, THEN IMPLEMENT YOUR OWN EVALUATE
        }

        int GetNextPlayer(int player, Board gameState)
        {
            if (gameState.HasAnyValidMove(-player))
            {
                return -player;
            }
            else
            {
                return player;
            }
        }

        #endregion

    }
}
