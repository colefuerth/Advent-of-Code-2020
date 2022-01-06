import java.io.FileNotFoundException;
import java.util.Scanner;
import java.io.File;
import java.util.ArrayList;
import java.util.ListIterator;
import java.util.Collections;

// https://adventofcode.com/2020/day/16

public class Tickets {
    /*
     * public static void optimizeList(ArrayList<Pair> lst){ Collections.sort(lst);
     * ListIterator<Pair> iter = lst.listIterator(); Pair me = iter.next(); while
     * (iter.hasNext()){ Pair you = iter.next(); // if there is an overlap, merge if
     * (me.second > you.first){ me.first = Math.min(me.first, you.first); me.second
     * = Math.max(me.second, you.second); lst.remove(you); // remove you, cycle in
     * next you } else me = you; // else, shift you into me and grab new you } }
     */
    public static void main(String args[]) throws FileNotFoundException {
        // begin by scanning the tickets
        Scanner sc = new Scanner(new File("input.txt"));
        // there are sets of values, and we do not know what language they are in.
        // we can determine whether a ticket is valid, by seeing if all of its numbers
        // are in valid ranges
        // start by getting lines until we reach a line that does not have an 'or' in it
        ArrayList<Pair> ranges = new ArrayList<>();
        while (sc.hasNextLine()) {
            boolean exitFlag = false;
            for (String line : sc.nextLine().split(" ")) {
                if (line.contains("-")) {
                    exitFlag = true;
                    // each dash will only have two values
                    String[] temp = line.split("-");
                    ranges.add(new Pair(Integer.parseInt(temp[0]), Integer.parseInt(temp[1])));
                }
            }
            if (exitFlag == false)
                break;
        }
        // optimizeList(ranges);
        while (sc.hasNextLine()) {
            if (sc.nextLine().contains("nearby tickets"))
                break;
        }
        ArrayList<Integer> invalidSpaces = new ArrayList<>();
        while (sc.hasNextLine()) {
            boolean anyValidSpaces = false;
            // ArrayList<Integer> cardInvSpaces = new ArrayList<>();
            for (String str : sc.nextLine().split(",")) {
                int me = Integer.parseInt(str);
                boolean thisOneValid = false;
                for (Pair p : ranges) {
                    if (me > p.first && me < p.second) {
                        anyValidSpaces = true;
                        thisOneValid = true;
                    }
                }
                if (!thisOneValid)
                    invalidSpaces.add(me);
            }
            // only add invalid spaces to main set if at least one space on the card is
            // valid
            /*
             * if (anyValidSpaces) { for (int x : cardInvSpaces) { invalidSpaces.add(x); } }
             */
        } // end of main ticket processing
        int sum = 0;
        for (int x : invalidSpaces) {
            sum += x;
        }
        System.out.println(sum);
    }
}