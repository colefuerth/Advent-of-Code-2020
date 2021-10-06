import java.util.*;

public class Tile {
    public boolean[][] arr; // tile contents
    public Tile[] adjTilesFinal;
    /** tiles on corners in final configuration */
    public int name; // name of tile
    private int size;
    private static final char[] sideChars = "urdl".toCharArray();

    // each tile has a set of strings, each string is an adjacency string and a
    // number of left rotations to duplicate that adjacency
    // public Map<Tile, Set<String>> adjacents;
    public Set<Tile> adjacents;

    /** a map of all adjacent tiles, and their adjacency strings */

    public Tile(int name, String[] tilestr) {
        this.name = name;
        this.size = tilestr.length;
        this.adjacents = new HashSet<>();
        this.adjTilesFinal = new Tile[4];
        // should already be null, but need to be sure
        for (int i = 0; i < adjTilesFinal.length; i++) {
            adjTilesFinal[i] = null;
        }
        arr = new boolean[size][size];
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                if (tilestr[i].charAt(j) == '#') {
                    arr[i][j] = true;
                } else {
                    arr[i][j] = false;
                }
            }
        }
        return;
    }

    /**
     * copy of this tile
     */
    public Tile(Tile other) {
        this(other.name, other.toString().split("\n"));
    }

    /**
     * Return a clone of this tile
     */
    public Tile clone() {
        return new Tile(this);
    }

    /**
     * Constructs a new hashmap to use for adjacents, in preparation for next scan
     */
    /*
    public void clearAdjacents() {
        this.adjacents = new HashSet<>();
    }*/

    public int numberFinalAdjacents() {
        int count = 0;
        for (int i = 0; i < adjTilesFinal.length; i++) {
            if (adjTilesFinal[i] != null) {
                count++;
            }
        }
        return count;
    }

    public boolean[][] rotateLeft(int times) {
        if (times >= 4) {
            return rotateLeft(times % 4);
        }
        boolean[][] temp;
        temp = this.arr.clone();

        for (int x = 0; x < times; x++) {
            for (int i = 0; i < size; i++) {
                for (int j = 0; j < size; j++) {
                    temp[i][j] = arr[j][size - i - 1];
                }
            }
        }
        return temp;
    }

    public boolean[][] fliphorizontal() {
        boolean[][] temp = this.arr.clone();
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                temp[i][j] = arr[i][size - j - 1];
            }
        }
        return temp;
    }

    public boolean[][] flipvertical() {
        boolean[][] temp = this.arr.clone();
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                temp[i][j] = arr[size - i - 1][j];
            }
        }
        return temp;
    }

    /**
     * checks that this left edge and that right edge are the same
     */
    public boolean adjL(Tile that) {
        // need to ensure lower edge is not already occupied on that tile
        if (that.adjTilesFinal[sideIndex('l')] != null)
            return false;
        for (int i = 0; i < size; i++) {
            if (this.arr[i][0] != that.arr[i][size - 1]) {
                return false;
            }
        }
        return true;
    }

    /**
     * checks that this right edge and that left edge are the same
     */
    public boolean adjR(Tile that) {
        // need to ensure lower edge is not already occupied on that tile
        if (that.adjTilesFinal[sideIndex('r')] != null)
            return false;
        for (int i = 0; i < size; i++) {
            if (this.arr[i][size - 1] != that.arr[i][0]) {
                return false;
            }
        }
        return true;
    }

    /**
     * checks that this top edge and that bottom edge are the same
     */
    public boolean adjU(Tile that) {
        // need to ensure lower edge is not already occupied on that tile
        if (that.adjTilesFinal[sideIndex('u')] != null)
            return false;
        for (int i = 0; i < size; i++) {
            if (this.arr[0][i] != that.arr[size - 1][i]) {
                return false;
            }
        }
        return true;
    }

    /**
     * checks that this bottom edge and that top edge are the same
     */
    public boolean adjD(Tile that) {
        // need to ensure lower edge is not already occupied on that tile
        if (that.adjTilesFinal[sideIndex('d')] != null)
            return false;
        for (int i = 0; i < size; i++) {
            if (this.arr[size - 1][i] != that.arr[0][i]) {
                return false;
            }
        }
        return true;
    }

    /**
     * Returns index of side corresponding to passed character
     */
    public static int sideIndex(char in) {
        for (int i = 0; i < sideChars.length; i++) {
            if (sideChars[i] == in)
                return i;
        }
        return -1;
    }

    /**
     * Returns a string of characters of which edges are adjacent for tiles in
     * current config 'l': left edge 'r': right edge 'u': upper edge 'd': bottom
     * edge
     * 
     * @return null if no edges match
     */
    public String adjacentEdges(Tile that) {
        String adj = "";
        // ensure that edges are unpopulated before checking each one
        if (adjTilesFinal[sideIndex('l')] != null && adjL(that)) {
            adj += 'l';
        }
        if (adjTilesFinal[sideIndex('r')] != null && adjR(that)) {
            adj += 'r';
        }
        if (adjTilesFinal[sideIndex('u')] != null && adjU(that)) {
            adj += 'u';
        }
        if (adjTilesFinal[sideIndex('d')] != null && adjD(that)) {
            adj += 'd';
        }
        if (adj.equals(""))
            return null;
        return adj;
    }

    @Override
    public String toString() {
        String str = "";
        for (boolean[] x : this.arr) {
            for (boolean y : x) {
                if (y) {
                    str += "#";
                } else {
                    str += ".";
                }
            }
            str += "\n";
        }
        return str.substring(0, str.length() - 1); // cut off last \n
    }
}
