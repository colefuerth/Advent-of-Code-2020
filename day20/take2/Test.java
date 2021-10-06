
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

    public static void main(String[] args) {
        // inject input from stdin
        Set<Tile> tiles = getInput(new Scanner(System.in));

        // find all adjacent combinations of tiles
        for (Tile t : tiles)
        {
            for (Tile v : tiles){
                if (t == v || t.adjacents.contains(v))
                    continue;
                for (String ts : t.sides)
                    for (String vs : v.sides)
                        if (ts.equals(vs)){
                            t.adjacents.add(v);
                            v.adjacents.add(t);
                        }
            }
        }

        System.out.println(tiles.size() + " tiles read in.");

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
