import java.util.Stack;

import solution.*;

public class Main {
	public static void main(String[] args) {
		solve_n_queens(8);
	}

	final private static boolean try_to_put_queen(ChessBoard board,
			int start_x, int j) {
		boolean safe = false;
		for (int i = start_x; i < board.size(); ++i) {
			safe = board.add(new Queen(i, j));
			if (safe) {
				break;
			}
		}
		return safe;
	}

	// solve n-queen problem by backtracking algorithm
	public static void solve_n_queens(int num_of_queens) {

		Stack<ChessBoard> steps = new Stack<ChessBoard>();
		ChessBoard board = new ChessBoard(num_of_queens);

		// the staring position to try for the next queen
		int next_x = 0;
		int next_y = 0;

		while (true) {
			
			// try to put a queen on the row next_y
			boolean bAdded = try_to_put_queen(board, next_x, next_y);
			if (bAdded) {
				
				// successfully add a queen to the ChessBoard				
				System.out.println(board.toString());
					steps.push(board.clone());

				// move to the next row
				next_x = 0;
				next_y = board.numOfQueens();

				if (board.numOfQueens() >= num_of_queens) {
					System.out.println("Solved!");
					System.out.println(board.toString());
					return;
				}
				
			} else {
				if (!steps.empty() && steps.peek().numOfQueens() > 0) {
					Queen last_queen = steps.peek().getLastQueen();
					next_x = last_queen.x() + 1;
	                next_y = last_queen.y();

					// backtrace to the previous step
					steps.pop();
					if (!steps.empty()) {
						board = steps.peek().clone();
					} else {
						board = new ChessBoard(num_of_queens);
						if (next_x >= num_of_queens) {
							System.out.println("Cannot solve\n");
							return;
						}						
					}
					
				} else {
					System.out.println("Error! Should not reach here\n");
	                return;
				}
			}
		} // while

	}
}
