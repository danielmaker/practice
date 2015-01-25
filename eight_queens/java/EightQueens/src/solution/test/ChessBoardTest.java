package solution.test;

import static org.junit.Assert.*;
import org.junit.Assert;
import org.junit.Test;

import solution.*;


public class ChessBoardTest {

	@Test
	public void testAdd() {
        {
            ChessBoard board = new ChessBoard(8);
            Assert.assertFalse( board.add(new Queen(8, 8)) );
            Assert.assertFalse( board.add(new Queen(-1, -1)) );

            Assert.assertTrue( board.add(new Queen(0, 0)) );
        }

        {
            ChessBoard board = new ChessBoard(8);
            Assert.assertTrue( board.add(new Queen(0, 0)) );
            Assert.assertFalse( board.add(new Queen(0, 0)) );
            Assert.assertFalse( board.add(new Queen(1, 1)) );

            Assert.assertTrue( board.add(new Queen(2, 1)) );
        }
	}

}
