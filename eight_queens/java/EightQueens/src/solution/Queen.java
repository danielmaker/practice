package solution;

public class Queen implements Cloneable {
	
	protected int m_x;
	protected int m_y;
	
	public Queen() {
		m_x = 0;
		m_y = 0;
	}

	public Queen(int a, int b) {
		m_x = a;
		m_y = b;
	}
	
	public int x() { return m_x; }
    public int y() { return m_y; }

    /**
     * Check if the position will be killed by the queen
     * @return 
     *    true: if the queen will kill a chess at the position
     */
    public boolean kill(int a, int b)
    {
        return ( a == m_x ||
                 b == m_y ||
                 (m_x-a) == (m_y-b) ||
                 (m_x-a) == -(m_y-b) );
    }
    
    @Override
    public Queen clone() {
    	Queen cloned = new Queen(m_x, m_y);
    	return cloned;
    }
    
    @Override
    public String toString() {
    	return String.format("Queen(%d, %d)", m_x, m_y);
    }
}
