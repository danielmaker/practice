#!/usr/bin/python

import unittest
import copy


class Queen:
    def __init__(self, _x, _y):
        self.x = _x
        self.y = _y

    def __str__(self):
        return "Queen(%d,%d)" % (self.x, self.y)

    def copy(self):
        return copy.deepcopy(self)

    # Check if the position will be killed by the queen
    # @return true: if the queen will kill a chess at the position
    def kill(self, a, b):
        return ( a == self.x or
                 b == self.y or
                 (self.x-a) == (self.y-b) or
                 (self.x-a) == -(self.y-b) )


class QueenTest(unittest.TestCase):

    def test_kill(self):
        queen = Queen(1,1)

        self.assertTrue( queen.kill(0, 0))
        self.assertTrue( queen.kill(0, 1))
        self.assertTrue( queen.kill(0, 2))
        self.assertTrue( queen.kill(1, 0))
        self.assertTrue( queen.kill(1, 1))
        self.assertTrue( queen.kill(1, 2))
        self.assertTrue( queen.kill(2, 0))
        self.assertTrue( queen.kill(2, 1))
        self.assertTrue( queen.kill(2, 2))

        self.assertTrue( queen.kill(3, 3))
        self.assertTrue( queen.kill(1, 3))
        self.assertTrue( queen.kill(3, 1))
        self.assertTrue( queen.kill(4, 1))

        self.assertFalse( queen.kill(4, 2))
        self.assertFalse( queen.kill(4, 3))
        self.assertFalse( queen.kill(4, 5))



class ChessBoard:
    def __init__(self, _boardSize):
        self.size = _boardSize
        self.queens = []

    def __str__(self):
        str = "ChessBoard(size=%d, queens=%d): " % (self.size, len(self.queens))
        for qn in self.queens:
            str += "(%d, %d), " % (qn.x, qn.y)
        return str

    def copy(self):
        return copy.deepcopy(self)

    # Check if the input position is safe
    # @return true: if the position is safe
    def check(self, x, y):
        if(0 > x or x >= self.size or 0 > y or y >= self.size):
            return False

        bKill = False
        for qn in self.queens:
            if( qn.kill(x, y)):
                bKill = True
        return not bKill

    # Add a queen to the ChessBoard
    # @return
    #    true: if the ChessBoard accepts the queen
    #          false: if the ChessBoard rejects the queen
    def add(self, queen):
        if( self.check(queen.x, queen.y) ):
            self.queens.append(queen.copy())
            return True
        else:
            return False


class ChessBoardTest(unittest.TestCase):

    def test_add(self):
        board = ChessBoard(8)
        self.assertFalse( board.add( Queen(8, 8)) )
        self.assertFalse( board.add( Queen(-1, -1)) )
        self.assertTrue( board.add( Queen(0, 0)) )


        board2 = ChessBoard(8)
        self.assertTrue( board2.add( Queen(0, 0)) )
        self.assertFalse( board2.add( Queen(0, 0)) )
        self.assertFalse( board2.add( Queen(1, 1)) )
        self.assertTrue( board2.add( Queen(2, 1)) )


# starts from start_x to search for a position to to put a queen on the position in the row j
def try_to_put_queen(board, start_x, j):
    bSafe = False;
    for i in range(start_x, board.size):
        bSafe = board.add( Queen(i, j) );
        if bSafe:
            break;
    return bSafe

# solve n-queen problem by backtracking algorithm
def solve_n_queens(num_of_queens):

    steps = []
    board = ChessBoard(num_of_queens)

    next_x = 0
    next_y = 0

    while 1:
        # try to put a queen on the row next_y
        bAdded = try_to_put_queen(board, next_x, next_y)
        if bAdded:
            # successfully add a queen to the ChessBoard
            print board
            steps.append(board.copy())

            # move to the next row
            next_x = 0;
            next_y = len(board.queens)

            if len(board.queens) >= num_of_queens :
                print "Solved"
                print board
                return
        else:
            # cannot find a position to put the next queen

            if len(steps) >0 and len(steps[-1].queens) >0:
                last_queen = steps[-1].queens[-1]
                next_x = last_queen.x + 1;
                next_y = last_queen.y;

                steps.pop()
                if len(steps) >0:
                    board = steps[-1].copy()
                else:
                    board = ChessBoard(num_of_queens)
                    if next_x >= num_of_queens:
                        print "Cannot solve\n"
                        return
            else:
                print "Error! Should not reach here\n"
                return


if __name__=='__main__':

    #unittest.main()

    solve_n_queens(8)

