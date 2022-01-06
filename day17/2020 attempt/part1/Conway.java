
import java.util.*;
// import java.io.*;

public class Conway {

    public static String printCube(List<List<List<Cube>>> cube) {
        // topmost layer is z coords; they need to be done at an offset so that middle
        // layer is z=0
        String str = "";
        int zoffset = cube.size() / 2;
        for (List<List<Cube>> z : cube) { // for z layers in cube
            boolean anyActive = false;
            String tempstr = "";
            tempstr += "\nZ = " + (cube.indexOf(z) - zoffset) + "\n";
            for (List<Cube> y : z) { // for y layers in z
                for (Cube x : y) { // for x cubes in y layer
                    tempstr += x;
                    if (x.active)
                        anyActive = true;
                }
                tempstr += "\n";
            }
            if (anyActive)
                str += tempstr;
        }
        return str;
    }

    public static List<Cube> ynew(int newsize) {
        List<Cube> newrow = new ArrayList<>();
        for (int i = 0; i < newsize; i++) {
            newrow.add(new Cube('.'));
        }
        return newrow;
    }

    public static List<List<Cube>> znew(int newsize) {
        List<List<Cube>> newlayer = new ArrayList<>();
        for (int i = 0; i < newsize; i++) {
            newlayer.add(ynew(newsize));
        }
        return newlayer;
    }

    // return true if any cubes in outer shells are active
    public static boolean anyActiveInOuterShell(Cube[][][] cube) {
        // check all edges
        int cubelen = cube.length - 1;
        for (int i = 0; i <= cubelen; i++) {
            for (int j = 0; j <= cubelen; j++) {
                if (cube[0][i][j].active || cube[cubelen][i][j].active || cube[i][0][j].active
                        || cube[i][cubelen][j].active || cube[i][j][0].active || cube[i][j][cubelen].active) {
                    return true;
                }
            }
        }

        return false;
    }

    // must be run in main to add an extra shell between cycles
    public static void addOuterShell(List<List<List<Cube>>> cube) {
        // need to add an inactive shell of new cubes
        // first, I need the old dimensions
        // this is a cube, so we can get the old length and just add two onto it
        int newsize = cube.size() + 2;

        for (List<List<Cube>> z : cube) {
            // start by expanding x in each y outwards
            for (List<Cube> y : z) {
                y.add(0, new Cube('.'));
                y.add(new Cube('.'));
            }
            // then, for each z layer, add a new y on top and bottom
            z.add(0, ynew(newsize));
            z.add(ynew(newsize));
        }
        // then, fill out z with a new layer at start and end
        cube.add(0, znew(newsize)); // add new z on inside
        cube.add(znew(newsize)); // add new z on outside
    }

    // used in runcycle()
    public static Cube[][][] toCubeArray(List<List<List<Cube>>> cubelist) {
        // start by converting to a 3d array, for speed of random access
        int size = cubelist.size();
        Cube[][][] cube = new Cube[size][size][size];
        for (int i = 0; i < size; i++) {
            List<List<Cube>> z = cubelist.get(i);
            for (int j = 0; j < size; j++) {
                z.get(j).toArray(cube[i][j]); // convert 1 y row at a time
            }
        }
        return cube;
    }

    public static int activeCubes(List<List<List<Cube>>> cube) {
        int active = 0;
        for (List<List<Cube>> z : cube) {
            // start by expanding x in each y outwards
            for (List<Cube> y : z) {
                for (Cube x : y) {
                    if (x.active)
                        active++;
                }
            }
        }
        return active;
    }

    // used in runcycle()
    public static void updateAdjacentSets(Cube[][][] cube) {
        int size = cube.length;
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                for (int k = 0; k < size; k++) {
                    // for each cube in cube, update its peers with its presence
                    if (cube[i][j][k].adjacent.size() < 26) { // dont bother checking, if cube already has a full shell
                                                              // of adjacents
                        for (int z = i - 1; z <= i + 1; z++) {
                            if (z < 0 || z >= size) // skip invalid z
                                continue;
                            for (int y = j - 1; y <= j + 1; y++) {
                                if (y < 0 || y >= size) // skip invalid y
                                    continue;
                                for (int x = k - 1; x <= k + 1; x++) {
                                    if (x < 0 || x >= size || (z == i && y == j && x == k)) // skip invalid x
                                        continue;
                                    cube[i][j][k].addAdjacentCube(cube[z][y][x]);
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    /**
     * Runs a changeover cycle on cube
     * <p>
     * Self-updates adjacent sets on each cube
     * 
     * @param cube: 3d list of cube
     * @return: number of cubes changed over
     */
    public static int runcycle(List<List<List<Cube>>> cube) {
        // before running cycle, need to update each cube with its peers
        Cube[][][] cubeArray = toCubeArray(cube);
        // if cube is in need of expansion, expand
        if (anyActiveInOuterShell(cubeArray)) {
            addOuterShell(cube); // expand shell
            cubeArray = toCubeArray(cube); // update cube array with new Cube
        }
        updateAdjacentSets(cubeArray);

        // need a set to contain any cubes that make requirements for changing state
        Set<Cube> toBeChanged = new HashSet<>();

        // now, iterate through cubes in cube. If a cube makes requirements, then mark
        // it for changeover.
        // NOTE: no changeovers can be made until analysis is complete.
        for (List<List<Cube>> z : cube) {
            for (List<Cube> y : z) {
                for (Cube x : y) {
                    int temp = x.activeAdjacent(); // get number of active cubes in adjacent set
                    if (x.adjacent.size() > 26)
                        System.out.println("Cube detected with too large an adjacent set!");
                    if (x.active && temp != 2 && temp != 3) {
                        toBeChanged.add(x);
                    } else if (!x.active && temp == 3) {
                        toBeChanged.add(x);
                    }
                }
            }
        }

        // apply changes
        for (Cube c : toBeChanged) {
            c.active = !c.active;
        }

        return toBeChanged.size();
    }

    public static void main(String[] args) {
        // read in whole file, I will use stdin with a pipe this time
        Scanner sc = new Scanner(System.in);
        List<List<List<Cube>>> cube = new ArrayList<>();
        // z, y, x
        // start with one depth z
        cube.add(new ArrayList<>()); // construct first Z layer
        while (sc.hasNextLine()) {
            List<Cube> xCubes = new ArrayList<>();
            cube.get(0).add(xCubes); // add new y coord to z=0 layer
            String line = sc.nextLine();
            for (int i = 0; i < line.length(); i++) {
                xCubes.add(new Cube(line.charAt(i)));
            }
        }
        sc.close(); // be sure to close the scanner when done reading input

        // print initial configuration
        System.out.println("Before any cycles:\n" + printCube(cube));

        // need to fill out cube into three dimensions before initial configuration
        int initialsize = cube.get(0).size();
        for (int i = 0; i < initialsize - 1; i++) {
            if (i % 2 == 0)
                cube.add(0, znew(initialsize));
            else
                cube.add(znew(initialsize));
        }

        for (int i = 0; i < 6; i++) {
            runcycle(cube);
            System.out.println("After " + (i + 1) + " cycles:\n" + printCube(cube));
        }
        System.out.println(activeCubes(cube) + " active cubes remain.");
    }
}
