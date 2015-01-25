#include <stdio.h>
#include <vector>
#include <stack>

#include <gtest/gtest.h>

//------------------------------------------------------------------------------

class Queen
{
public:
    Queen() : m_x(0), m_y(0) {}
    Queen(int a, int b) : m_x(a), m_y(b) {}

    int x() const { return m_x; }
    int y() const { return m_y; }

    /// Check if the position will be killed by the queen
    /// @return true: if the queen will kill a chess at the position
    bool Kill(int a, int b) const
    {
        return ( a == m_x ||
                 b == m_y ||
                 (m_x-a) == (m_y-b) ||
                 (m_x-a) == -(m_y-b) );
    }

protected:
    int m_x;
    int m_y;
};


class ChessBoard
{
public:
    ChessBoard(size_t board_size) : m_BoardSize(board_size) {}

    size_t Size() const { return m_BoardSize; }

    /// Check if the input position is safe
    /// @return true: if the position is safe
    bool Check(int x, int y) const
    {
        if(x >= m_BoardSize || y >= m_BoardSize) {
            return false;
        }

        bool bKill = false;
        for(size_t i=0; i<m_Queens.size(); ++i)
        {
            if(m_Queens[i].Kill(x, y))
            {
                bKill = true;
                break;
            }
        }

        return !bKill;
    }

    /// Add a queen to the ChessBoard
    /// @ return  true: if the ChessBoard accepts the queen
    ///           false: if the ChessBoard rejects the queen
    bool Add(const Queen& queen)
    {
        if( Check(queen.x(), queen.y()) )
        {
            m_Queens.push_back(queen);
            return true;
        }

        return false;
    }

    size_t numOfQueens() const { return m_Queens.size(); }

    const std::vector<Queen>& Queens() const { return m_Queens; }


    void PrintSelf()
    {
        printf("ChessBoard(size=%lu, queens=%lu): ", m_BoardSize, m_Queens.size());
        for(size_t i=0; i<m_Queens.size(); ++i)
        {
            printf("(%d, %d), ", m_Queens[i].x(), m_Queens[i].y());
        }
        printf("\n");
    }

protected:
    size_t m_BoardSize;
    std::vector<Queen> m_Queens;
};

//------------------------------------------------------------------------------
// unit tests

TEST(QueenTestCase, Kill)
{
    Queen queen(1, 1);

    EXPECT_TRUE(queen.Kill(0, 0));
    EXPECT_TRUE(queen.Kill(0, 1));
    EXPECT_TRUE(queen.Kill(0, 2));
    EXPECT_TRUE(queen.Kill(1, 0));
    EXPECT_TRUE(queen.Kill(1, 1));
    EXPECT_TRUE(queen.Kill(1, 2));
    EXPECT_TRUE(queen.Kill(2, 0));
    EXPECT_TRUE(queen.Kill(2, 1));
    EXPECT_TRUE(queen.Kill(2, 2));

    EXPECT_TRUE(queen.Kill(3, 3));
    EXPECT_TRUE(queen.Kill(1, 3));
    EXPECT_TRUE(queen.Kill(3, 1));
    EXPECT_TRUE(queen.Kill(4, 1));


    EXPECT_FALSE(queen.Kill(4, 2));
    EXPECT_FALSE(queen.Kill(4, 3));
    EXPECT_FALSE(queen.Kill(4, 5));
}

TEST(ChessBoardTestCase, Add)
{
    {
        ChessBoard board(8);
        EXPECT_FALSE( board.Add(Queen(8, 8)) );
        EXPECT_FALSE( board.Add(Queen(-1, -1)) );

        EXPECT_TRUE( board.Add(Queen(0, 0)) );
    }

    {
        ChessBoard board(8);
        EXPECT_TRUE( board.Add(Queen(0, 0)) );
        EXPECT_FALSE( board.Add(Queen(0, 0)) );
        EXPECT_FALSE( board.Add(Queen(1, 1)) );

        EXPECT_TRUE( board.Add(Queen(2, 1)) );
    }
}

//------------------------------------------------------------------------------

/// starts from start_x to search for a position to to put a queen on the position in the row j
/// @param board : the ChessBoard
/// @param start_x : starts from start_x to search
/// @param j : the row to put a queen
/// @return true  : if successfully add a queen to the ChessBoard
///         false : if cannot find a position to put the next queen in the row j
inline bool try_to_put_queen(ChessBoard& board, size_t start_x, size_t j)
{
    bool bSafe = false;
    for (size_t i = start_x; i < board.Size(); ++i)
    {
        bSafe = board.Add( Queen(i, j) );
        if(bSafe) {
            break;
        }
    }
    return bSafe;
}

// solve n-queen problem by backtracking algorithm
void solve_n_queens(size_t num_of_queens)
{
    std::stack<ChessBoard> steps;
    ChessBoard board(num_of_queens);

    // the staring position to try for the next queen
    size_t next_x = 0;
    size_t next_y = 0;

    while(1)
    {
        // try to put a queen on the row next_y
        bool bAdded = try_to_put_queen(board, next_x, next_y);
        if (bAdded)
        {
            // successfully add a queen to the ChessBoard
            board.PrintSelf();
            steps.push(board);

            // move to the next row
            next_x = 0;
            next_y = board.numOfQueens();

            if (board.numOfQueens() >= num_of_queens)
            {
                printf("Solved!\n");
                board.PrintSelf();
                return;
            }
        }
        else
        {
            // cannot find a position to put the next queen

            if (!steps.empty() && !steps.top().Queens().empty())
            {
                const Queen& last_queen = steps.top().Queens().back();
                next_x = last_queen.x() + 1;
                next_y = last_queen.y();

                // backtrace to the previous step
                steps.pop();
                if (!steps.empty())
                {
                    board = steps.top();
                }
                else
                {
                    board = ChessBoard(num_of_queens);
                    if (next_x >= num_of_queens)
                    {
                        printf("Cannot solve\n");
                        return;
                    }
                }
            }
            else
            {
                printf("Error! Should not reach here\n");
                return;
            }
        }
    }
}

//------------------------------------------------------------------------------

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);

    bool test_result = RUN_ALL_TESTS();

    if(0 == test_result)
    {
        solve_n_queens(8);
    }

    return test_result;
}
