
import java.util.*;
// import java.io.*;

public class Conway {

    public static String printCube(List<List<List<List<Cube>>>> cube) {
        // topmost layer is z coords; they need to be done at an offset so that middle
        // layer is z=0
        String str = "";
        int zoffset = cube.size() / 2;
        for (List<List<List<Cube>>> w : cube) {
            boolean anyActivew = false;
            String tempstrw = "";
            for (List<List<Cube>> z : w) { // for z layers in cube
                boolean anyActivez = false;
                String tempstr = "";
                // w and z offsets are the same
                tempstr += "\nZ = " + (cube.indexOf(z) - zoffset) + ", W = " + (cube.indexOf(w) - zoffset) + "\n";
                for (List<Cube> y : z) { // for y layers in z
                    for (Cube x : y) { // for x cubes in y layer
                        tempstr += x;
                        if (x.active) {
                            anyActivez = true;
                            anyActivew = true;
                        }
                    }
                    tempstr += "\n";
                }
                if (anyActivez)
                    tempstrw += tempstr;
            }
            if (anyActivew) {
                str += tempstrw;
            }
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

    public static List<List<List<Cube>>> wnew(int newsize) {
        List<List<List<Cube>>> newcube = new ArrayList<>();
        for (int i = 0; i < newsize; i++) {
            newcube.add(znew(newsize));
        }
        return newcube;
    }

    // return true if any cubes in outer shells are active
    public static boolean anyActiveInOuterShell(Cube[][][][] cube) {
        // check all edges
        int cubelen = cube.length - 1;
        for (int i = 0; i <= cubelen; i++) {
            for (int j = 0; j <= cubelen; j++) {
                for (int k = 0; k <= cubelen; k++) {
                    if (cube[0][i][j][k].active || cube[cubelen][i][j][k].active || cube[i][0][j][k].active
                            || cube[i][cubelen][j][k].active || cube[i][j][0][k].active || cube[i][j][cubelen][k].active
                            || cube[i][j][k][0].active || cube[i][j][k][cubelen].active) {
                        return true;
                    }
                }
            }
        }

        return false;
    }

    // must be run in main to add an extra shell between cycles
    public static void addOuterShell(List<List<List<List<Cube>>>> cube) {
        // need to add an inactive shell of new cubes
        // first, I need the old dimensions
        // this is a cube, so we can get the old length and just add two onto it
        int newsize = cube.size() + 2;

        for (List<List<List<Cube>>> w : cube) {
            for (List<List<Cube>> z : w) {
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
            w.add(0, znew(newsize)); // add new z on inside
            w.add(znew(newsize)); // add new z on outside
        }
        cube.add(0, wnew(newsize)); // add new z on inside
        cube.add(wnew(newsize)); // add new z on outside
    }

    // used in runcycle()
    public static Cube[][][][] toCubeArray(List<List<List<List<Cube>>>> cubelist) {
        // start by converting to a 3d array, for speed of random access
        int size = cubelist.size();
        Cube[][][][] cube = new Cube[size][size][size][size];
        for (int k = 0; k < size; k++) {
            List<List<List<Cube>>> w = cubelist.get(k);
            for (int i = 0; i < size; i++) {
                List<List<Cube>> z = w.get(i);
                for (int j = 0; j < size; j++) {
                    z.get(j).toArray(cube[k][i][j]); // convert 1 y row at a time, for all 4 dimensions
                }
            }
        }
        return cube;
    }

    public static int activeCubes(List<List<List<List<Cube>>>> cube) {
        int active = 0;
        for (List<List<List<Cube>>> w : cube) {
            for (List<List<Cube>> z : w) {
                // start by expanding x in each y outwards
                for (List<Cube> y : z) {
                    for (Cube x : y) {
                        if (x.active)
                            active++;
                    }
                }
            }
        }
        return active;
    }

    // used in runcycle()
    public static void updateAdjacentSets(Cube[][][][] cube) {
        int size = cube.length;
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                for (int k = 0; k < size; k++) {
                    for (int l = 0; l < size; l++) {
                        // for each cube in cube, update its peers with its presence
                        // dont bother checking, if cube already has a full shell of adjacents
                        if (cube[i][j][k][l].adjacent.size() < 80) {
                            for (int z = i - 1; z <= i + 1; z++) {
                                if (z < 0 || z >= size) // skip invalid z
                                    continue;
                                for (int y = j - 1; y <= j + 1; y++) {
                                    if (y < 0 || y >= size) // skip invalid y
                                        continue;
                                    for (int x = k - 1; x <= k + 1; x++) {
                                        if (x < 0 || x >= size) // skip invalid x
                                            continue;
                                        for (int w = l - 1; w <= l + 1; w++) {
                                            // skip invalid w, as well as self
                                            if (w < 0 || w >= size || (z == i && y == j && x == k && w == l))
                                                continue;
                                            cube[i][j][k][l].addAdjacentCube(cube[z][y][x][w]);
                                        }
                                    }
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
    public static int runcycle(List<List<List<List<Cube>>>> cube) {
        // before running cycle, need to update each cube with its peers
        Cube[][][][] cubeArray = toCubeArray(cube);
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
        for (List<List<List<Cube>>> w : cube) {
            for (List<List<Cube>> z : w) {
                for (List<Cube> y : z) {
                    for (Cube x : y) {
                        int temp = x.activeAdjacent(); // get number of active cubes in adjacent set
                        if (x.adjacent.size() > 80)
                            System.out.println("Cube detected with too large an adjacent set!");
                        if (x.active && temp != 2 && temp != 3) {
                            toBeChanged.add(x);
                        } else if (!x.active && temp == 3) {
                            toBeChanged.add(x);
                        }
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
        List<List<List<List<Cube>>>> cube = new ArrayList<>();
        // w, z, y, x
        // start with one depth z
        cube.add(new ArrayList<>()); // construct first w cube
        List<List<List<Cube>>> firstcube = cube.get(0);
        firstcube.add(new ArrayList<>()); // construct first z layer
        List<List<Cube>> firstlayer = cube.get(0).get(0);
        while (sc.hasNextLine()) {
            List<Cube> xCubes = new ArrayList<>();
            firstlayer.add(xCubes); // add new y coord to z=0 layer
            String line = sc.nextLine();
            for (int i = 0; i < line.length(); i++) {
                xCubes.add(new Cube(line.charAt(i)));
            }
        }
        sc.close(); // be sure to close the scanner when done reading input

        // print initial configuration
        System.out.println("Before any cycles:\n" + printCube(cube));

        // need to fill out cube into four dimensions before initial configuration
        int initialsize = firstlayer.size();
        for (int i = 0; i < initialsize - 1; i++) {
            if (i % 2 == 0){
                firstcube.add(0, znew(initialsize));
                cube.add(0, wnew(initialsize));
            }
            else{
                firstcube.add(znew(initialsize));
                cube.add(wnew(initialsize));
            }
        }

        for (int i = 0; i < 6; i++) {
            runcycle(cube);
            System.out.println("After " + (i + 1) + " cycles:\n" + printCube(cube));
        }
        System.out.println(activeCubes(cube) + " active cubes remain.");
    }
}
