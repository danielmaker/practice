package solution.test;

import static org.junit.Assert.*;
import org.junit.Assert;
import org.junit.Test;

import solution.*;

public class QueenTest {

    @Test
    public void testKill() {

        Queen queen = new Queen(1, 1);

        Assert.assertTrue(queen.kill(0, 0));
        Assert.assertTrue(queen.kill(0, 1));
        Assert.assertTrue(queen.kill(0, 2));
        Assert.assertTrue(queen.kill(1, 0));
        Assert.assertTrue(queen.kill(1, 1));
        Assert.assertTrue(queen.kill(1, 2));
        Assert.assertTrue(queen.kill(2, 0));
        Assert.assertTrue(queen.kill(2, 1));
        Assert.assertTrue(queen.kill(2, 2));

        Assert.assertTrue(queen.kill(3, 3));
        Assert.assertTrue(queen.kill(1, 3));
        Assert.assertTrue(queen.kill(3, 1));
        Assert.assertTrue(queen.kill(4, 1));

        Assert.assertFalse(queen.kill(4, 2));
        Assert.assertFalse(queen.kill(4, 3));
        Assert.assertFalse(queen.kill(4, 5));

    }
}
