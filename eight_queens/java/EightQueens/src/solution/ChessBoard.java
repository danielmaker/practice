package solution;

import java.util.ArrayList;
import java.util.List;

public class ChessBoard {
	
	protected int boardSize;
	protected List<Queen> queens = new ArrayList<Queen>();
	
	
	public ChessBoard(int _boardSize) {
		boardSize = _boardSize;
	}

    public int size() { return boardSize; }
    
    public int numOfQueens() {
    	return queens.size();
    }
    
	public Queen getLastQueen() {
		if (queens.size() > 0) {
			int last = queens.size() - 1;
			return queens.get(last);
		}
		return null;
	}
    
    List<Queen> getQueens() {
    	return queens;
    }
    
    /**
     * Check if the input position is safe
     * @return 
     *    true: if the position is safe
     */
	public boolean check(int x, int y) {
		if (0 > x || x >= boardSize || 0 > y || y >= boardSize) {
			return false;
		}

		boolean kill = false;
		for (int i = 0; i < queens.size(); ++i) {
			if (queens.get(i).kill(x, y)) {
				kill = true;
				break;
			}
		}

		return !kill;
	}

    /// Add a queen to the ChessBoard
    /// @ return  true: if the ChessBoard accepts the queen
    ///           false: if the ChessBoard rejects the queen
	public boolean add(Queen queen) {
		if (check(queen.x(), queen.y())) {
			queens.add(queen.clone());
			return true;
		}
		return false;
	}
	
	@Override
	public ChessBoard clone() {
		ChessBoard cloned = new ChessBoard(boardSize);
		cloned.queens = new ArrayList<Queen>(queens.size());
		for (int i = 0; i < queens.size(); ++i) {
			cloned.queens.add((Queen)queens.get(i).clone());
		}
		return cloned;
	}
	
    @Override
    public String toString() {
    	String str = String.format("ChessBoard(size=%d, queens=%d): ", boardSize, queens.size());
    	for (int i = 0; i < queens.size(); ++i) {
    		Queen qn = queens.get(i);
    		str += String.format("(%d, %d), ", qn.x(), qn.y());  
    	}    	
    	return str;
    }    
}
