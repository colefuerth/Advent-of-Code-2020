import java.util.*;
import java.util.Map.Entry;

public class Monster {

    

    public static Map<String, List<Integer>> buildRuleSet(int ruleToCheck,
            Map<Integer, Map<String, List<Integer>>> masterSet, Map<Integer, List<int[]>> rules) {
        // check if set has already been built
        // base cases are already in master set, so no need to account for them in this
        // function
        System.out.println("Calculating rule " + ruleToCheck);
        if (masterSet.containsKey(ruleToCheck)) {
            System.out.println("Found rule " + ruleToCheck + " in cache");
            return masterSet.get(ruleToCheck);
        }
        System.out.print(ruleToCheck + ": ");
        for (int[] arr : rules.get(ruleToCheck)){
            for (int i : arr){
                System.out.print(i + " ");
            }
        }
        System.out.println();
        // else, build map
        Map<String, List<Integer>> thisMap = new HashMap<>();

        List<int[]> subrules = rules.get(ruleToCheck);
        for (int[] rule : subrules) {
            // ruleset is the union set of all rules in subrule
            Map<String, List<Integer>> ruleset = new HashMap<>(); // set will be for all in this rule
            for (int r : rule) {
                // temp set from rule r, for including into ruleset
                Map<String, List<Integer>> rset = buildRuleSet(r, masterSet, rules);
                // if this rule set is empty, just add rset and move on
                if (ruleset.size() == 0) {
                    ruleset.putAll(rset);
                } else { // if ruleset has elements, then ruleset must become a merge of rset and old
                         // ruleset contents
                    Map<String, List<Integer>> merged = new HashMap<>();
                    for (Entry<String, List<Integer>> a : ruleset.entrySet()) {
                        for (Entry<String, List<Integer>> b : rset.entrySet()) {
                            String s = a.getKey() + b.getKey();
                            List<Integer> path = new LinkedList<>(a.getValue());
                            path.addAll(b.getValue());
                            merged.put(s, path);
                        }
                    }
                    ruleset = merged; // copy merged into ruleset
                }
            }
            thisMap.putAll(ruleset);
        }
        masterSet.put(ruleToCheck, thisMap);
        System.out.println("Done calculating rule " + ruleToCheck);
        return thisMap;
    }

    public static void main(String[] args) {

        /**
         * Master Set contains the dynamic cache of entries calculated so far Each key
         * is a rule that has been calculated Each value is a map from every possible
         * string produced from that rule and its subrules, and the list of integer
         * steps to recreate that string
         */
        Map<Integer, Map<String, List<Integer>>> masterSet = new HashMap<>();

        // start by injesting the input and store them in sets
        Scanner sc = new Scanner(System.in);

        // parse rules from input
        Map<Integer, List<int[]>> rules = new TreeMap<>();
        // inject all rules (first half of input)
        while (sc.hasNextLine()) {
            String nl = sc.nextLine(); // get next line
            if (nl.trim().equals("")) // if next line is blank, then this is the end of rules input
                break;
            // System.out.println("parsing rule " + nl);
            String[] halves = nl.split(":"); // split into rule : subrules halves
            List<int[]> subrules = new LinkedList<>(); // can be more than one subrule, each subrule is a pair of rules
            if (halves[1].contains("\"")) { // base rules are added directly to the master set
                // this is a base rule; store the ASCII code for character in quotation marks
                int rule = Integer.parseInt(halves[0]);
                String letter = halves[1].trim().replace("\"", "");
                List<Integer> baseList = new LinkedList<>();
                baseList.add(rule);
                Map<String, List<Integer>> baseRule = new HashMap<>();
                baseRule.put(letter, baseList);
                // System.out.println("ASCII " + here[0] + " CHAR " + (char) here[0]);
                // subrules.add(here);
                masterSet.put(rule, baseRule);
            } else {
                for (String str : halves[1].trim().split("\\|")) { // each subrule is split by '|'
                    // System.out.println("Parsing half " + str);
                    String[] strints = str.trim().split(" "); // get ints out of each subrule
                    int[] me = new int[strints.length];
                    for (int i = 0; i < strints.length; i++) {
                        me[i] = Integer.parseInt(strints[i]);
                    }
                    subrules.add(me); // add this subrule to list of subrules for each rule
                }
            }
            rules.put(Integer.parseInt(halves[0]), subrules);
        }

        // remainder of file is input strings to test; ensure that no duplicate test
        // strings exist
        Set<String> testcases = new HashSet<>();
        while (sc.hasNextLine()) {
            if (!testcases.add(sc.nextLine())) {
                System.out.println("Duplicate test string detected!");
                System.exit(1);
            }
        }

        // now, begin processing
        System.out.println(masterSet);
        // now, iterate through rules in set, skipping the predetermined ones
        /*for (int i : rules.keySet()) {
            // if we did not already calculate master set for i, then calculate the set
            if (!masterSet.containsKey(i)) {
                System.out.println("RULE " + i);
            }
        }*/
        // System.out.println(masterSet);
        
        Set<String> zeroStrings = buildRuleSet(0, masterSet, rules).keySet();
        zeroStrings.retainAll(testcases);   // update zero strings to be the intersection of strings that appear in both sets
        System.out.println("There are " + zeroStrings.size() + " valid zero strings.");

        sc.close();
        System.exit(0);
    }
}
