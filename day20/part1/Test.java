
// get input from stdin

// https://adventofcode.com/2020/day/20

import java.util.*;

public class Test {

    private static Set<Tile> getInput(Scanner sc) {
        Set<Tile> tiles = new HashSet<>();
        int name = 0;
        List<String> lines = null;
        while (sc.hasNextLine()) {
            String line = sc.nextLine();
            if (line.equals("")) { // add new tiles on newlines
                String[] arr = new String[lines.size()];
                lines.toArray(arr);
                tiles.add(new Tile(name, arr));
                lines = null;
                name = 0;
            } else if (line.contains("Tile")) {
                // 'tile' means we are starting a new tile
                lines = new ArrayList<>();
                name = Integer.parseInt(line.split(" ")[1].replace(":", ""));
            } else {
                lines.add(line);
            }
        }
        if (name != 0 || lines != null) {
            String[] arr = new String[lines.size()];
            lines.toArray(arr);
            tiles.add(new Tile(name, arr));
        }
        return tiles;
    }

    /**
     * Checks all combinations of all tiles for adjacencies
     * 
     * returns a count of number of adjacencies found
     */
    private static int updateAdjacentsUnusedSides(Set<Tile> tiles) {
        int count = 0;
        // for each tile, check its adjacency against all other tiles
        for (Tile t : tiles) {
            // adjacentEdges function only returns adjacents on unused sides
            // need to clear adjacents cache on each tile before starting, since many tiles
            // have changed since last check
            // t.clearAdjacents();
            for (Tile other : tiles) {
                // dont bother checking its own adjacency
                if (other == t || t.adjacents.contains(other))
                    continue;
                // try all four orientations, flipped all ways
                for (int k = 0; k < 2; k++) {
                    for (int j = 0; j < 2; j++) {
                        for (int i = 0; i < 4; i++) {
                            String adjString = t.adjacentEdges(other); // check for adjacencies between other tile and t
                            other.arr = other.rotateLeft(1); // rotate other tile left for next try
                            // if no adjacencies are found, try next configuration
                            if (adjString == null)
                                continue;
                            // record them as adjacents
                            t.adjacents.add(other);
                            other.adjacents.add(t);
                            // update the adjacency found (one character for each adjacency found in current
                            // config
                            /*
                             * // if any adjacencies were found, make sure to add the current rotation to
                             * the // adjacency string adjString += " " + i; // construct a hashset of
                             * adjacency strings, if other is not already an adjacent if
                             * (!t.adjacents.containsKey(other)) { t.adjacents.put(other, new HashSet<>());
                             * } // add adjacency string to other tile, onto t
                             * t.adjacents.get(other).add(adjString);
                             */
                        }
                        other.arr = other.fliphorizontal();
                    }
                    other.arr = other.flipvertical();
                }
            }
        }
        return count;
    }
    /*
     * private static int storeNextMoveSet(Set<Tile> tiles) { int count = 0;
     * Set<Tile> matchedThisRound = new HashSet<>(); // cannot set adjacents on a
     * rotated tile this round, since it has // changed for (Tile t : tiles) { if
     * (matchedThisRound.contains(t)) continue; if (t.adjacents.size() == 1) { Tile
     * adj = t.adjacents.keySet().iterator().next(); if
     * (matchedThisRound.contains(adj)) continue; Set<String> adjInfo =
     * t.adjacents.get(adj); if (adjInfo.size() != 1) { // if a tile has more than
     * one orientation with current tile, then it is // not // certain that tile
     * goes there continue; } String[] data = adjInfo.iterator().next().split(" ");
     * // [0] contains side, [1] contains orientation if (data[0].length() != 0) {
     * // ensure current orientation only works on one side continue; } // increment
     * count of matches made this round count += 1; // add both tiles to set of
     * tiles modified this round matchedThisRound.add(t); matchedThisRound.add(adj);
     * // attach the tiles char side = data[0].charAt(0); int orientation =
     * Integer.parseInt(data[1]); adj.arr = adj.rotateLeft(orientation); // set tile
     * to final orientation t.adjTilesFinal[Tile.sideIndex(side)] = adj;
     * adj.adjTilesFinal[(Tile.sideIndex(side) + 2) % 4] = t; } } return count; }
     */

    public static void main(String[] args) {
        // inject input from stdin
        Set<Tile> tiles = getInput(new Scanner(System.in));

        // find all adjacent combinations of tiles
        System.out.println(tiles.size() + " tiles read in.");
        updateAdjacentsUnusedSides(tiles);
        System.out.println("Done matching.");
        Set<Tile> corners = new HashSet<>();
        for (Tile t : tiles){
            if (t.adjacents.size() == 2){
                corners.add(t);
            }
        }
        System.out.println(corners.size() + " corners found.");
        long cornerproduct = 1;
        for (Tile t : corners){
            cornerproduct *= (long) t.name;
        }
        System.out.println("Product of names is " + cornerproduct);

        System.exit(0);
    }
}
