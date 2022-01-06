import java.io.FileNotFoundException;
import java.util.Scanner;
import java.io.File;
import java.util.ArrayList;
// import java.util.ListIterator;
import java.util.List;
import java.util.HashMap;
import java.util.Map;
// import java.util.Collections;

// https://adventofcode.com/2020/day/16

public class Tickets {

    // cursed, but it works
    public static Pair[] parseRangesPairs(String line) {
        String[] str = line.trim().replace("or ", "").replace("-", " ").split(" "); // trim to just four integers, space
                                                                                    // separated
        if (str.length != 4) {
            System.out.println("Requires 4 integers! got " + str.length + " instead!");
        }
        Pair[] pairs = new Pair[2];
        pairs[0] = new Pair(Integer.parseInt(str[0]), Integer.parseInt(str[1]));
        pairs[1] = new Pair(Integer.parseInt(str[2]), Integer.parseInt(str[3]));
        return pairs;
    }

    /**
     * check if value is in a set of ranges
     */
    public static boolean inRangePair(int val, Pair[] pair) {
        for (Pair p : pair) {
            if (val > p.first && val < p.second) {
                return true;
            }
        }
        return false;
    }

    /**
     * returns first index of where val exists in a set of range pairs
     * 
     * @param val   value to look for
     * @param pairs list of pair arrays
     * @return index, or -1 if not found
     */
    public static int whichPair(int val, List<Pair[]> pairs) {
        for (Pair[] p : pairs) {
            if (inRangePair(val, p))
                return pairs.indexOf(p);
        }
        return -1;
    }

    /**
     * take in a string of comma-separated integers, return as int array
     */
    public static int[] parseticket(String line) {
        String[] str = line.split(",");
        int[] vals = new int[str.length];
        for (int i = 0; i < str.length; i++) {
            vals[i] = Integer.parseInt(str[i]);
        }
        return vals;
    }

    public static void main(String args[]) throws FileNotFoundException {
        // begin by scanning the tickets
        Scanner sc = new Scanner(new File("small.txt"));
        // there are sets of values, and we do not know what language they are in.
        // we can determine whether a ticket is valid, by seeing if all of its numbers
        // are in valid ranges
        // start by getting lines until we reach a line that does not have an 'or' in it

        // going to use an array to store tickets, since I will be doing a lot of random
        // access, and values need to be ordered
        List<Pair[]> ranges = new ArrayList<>(); // list of ranges, each entry has two ranges
        List<String> names = new ArrayList<>(); //

        // injest input here
        while (sc.hasNextLine()) {
            // get next line
            String line = sc.nextLine();
            // if next line has 'or' in it, it is a range field
            if (!line.contains(":")) {
                break;
            }
            // now, each line has two parts: name and ranges
            // start with name
            String[] halves = line.split(":");
            names.add(halves[0]);
            ranges.add(parseRangesPairs(halves[1]));
        }

        /*
         * // test: print generated output for (int i = 0; i < names.size(); i++) {
         * Pair[] p = ranges.get(i); System.out.println(names.get(i) + ": " + p[0] +
         * " or " + p[1]); }
         */

        // inject your own ticket, and then skip to beginning of bulk ticket injestion
        // do my ticket separate
        List<int[]> ticketList = new ArrayList<>();
        while (sc.hasNextLine()) {
            String nl = sc.nextLine();
            if (nl.contains("your ticket")) { // must add your ticket first
                ticketList.add(parseticket(sc.nextLine()));
            }
            if (nl.contains("nearby tickets"))
                break;
        }

        // injest all tickets
        while (sc.hasNextLine()) {
            // inject tickets here
            int[] ticket = parseticket(sc.nextLine()); // parse ticket, then check if it's valid before adding it
            boolean valid = true; // set flag to false if any are declared not there
            for (int val : ticket) { // check that all values on ticket are valid
                if (whichPair(val, ranges) < 0) {
                    valid = false;
                    break;
                }
            }
            if (valid) { // if every value on ticket exists in at least one range, then it is a valid
                         // ticket
                ticketList.add(ticket);
            }
        } // end of main ticket injestion

        // now, ticketList holds a list of only valid tickets

        // create a map of strings to int indexes, for each index, add a map from name
        // of entry to what index it is
        Map<String, Integer> positionMap = new HashMap<>();

        // for each range, check that every ticket at a certain index is in that range
        // possible bug is, if two ranges could be at the same index, i do not account
        // for that

        // NOTE: this only actually passes 7 values, so just see which position matches
        // each range the most, and use that for the mapping
        // (clearly I did not filter invalid tickets correctly, but at least it should
        // be mostly correct)
        for (Pair[] range : ranges) { // for each range
            for (int i = 0; i < ranges.size(); i++) { // for each possible position in ticket
                boolean isHere = true;
                for (int[] ticket : ticketList) { // check each ticket, at position i
                    if (!inRangePair(ticket[i], range)) { // if any ticket does not fit in this range at this position,
                                                          // then it is not this position
                        isHere = false;
                        break;
                    }
                }
                if (isHere) { // if this range is at index i, then add it to the map and move on to the next
                              // range
                    positionMap.put(names.get(i), i);
                    break;
                }
            }
        }

        // print index map
        System.out.println(positionMap);

        // sum the 6 positions of my ticket, where the name starts with 'departure'

    }
}