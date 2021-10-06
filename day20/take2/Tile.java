import java.util.*;

public class Tile {
    // public boolean[][] arr; // tile contents
    public String[] tileStrings;
    public Set<String> sides;
    public int name; // name of tile
    private int size;

    // each tile has a set of strings, each string is an adjacency string and a
    // number of left rotations to duplicate that adjacency
    // public Map<Tile, Set<String>> adjacents;
    public Set<Tile> adjacents;

    /** a map of all adjacent tiles, and their adjacency strings */

    public Tile(int name, String[] tilestr) {
        this.name = name;
        this.size = tilestr.length;
        this.adjacents = new HashSet<>();
        this.sides = new HashSet<>();
        this.tileStrings = tilestr;

        String left = "", right = "";

        for (int i = 0; i < size; i++) {
            left += tilestr[i].charAt(0);
            right += tilestr[i].charAt(tilestr.length - 1);
        }

        sides.add(left);
        sides.add(right);
        sides.add(tilestr[0]);
        sides.add(tilestr[tilestr.length - 1]);

        // now, need to create duplicates but reversed of each side
        Set<String> original = new HashSet<>(sides);
        for (String s : original)
        {
            sides.add((new StringBuilder(s)).reverse().toString());
        }

        return;
    }

    /**
     * copy of this tile
     */
    public Tile(Tile other) {
        this(other.name, other.tileStrings.clone());
    }

    /**
     * Return a clone of this tile
     */
    public Tile clone() {
        return new Tile(this);
    }

}
