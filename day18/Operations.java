import java.util.*;

public class Operations {
    public static long evaluate(String str) {
        System.out.println("Evaluating: " + str);
        // long register = 0;
        str.trim(); // remove leading and trailing white space
        // start of string is either opening bracket or an integer

        // start by scanning whole string for brackets
        for (int iter = 0; iter < str.length(); iter++) {
            // parse string within brackets
            if (str.charAt(iter) == '(') {
                int endOfBracket = iter;
                int depth = 1; // set depth to 1
                while (depth > 0) {
                    char ch = str.charAt(++endOfBracket);
                    if (ch == '(')
                        ++depth;
                    else if (ch == ')')
                        --depth;
                } // after finding the final ')', iter is on closing bracket
                // replace solved bracket into original string; move on to rest of equation
                // str = str.substring(0, iter) + evaluate(str.substring(iter + 1, endOfBracket)) + str.substring(endOfBracket + 1);
                return evaluate(str.substring(0, iter) + evaluate(str.substring(iter + 1, endOfBracket)) + str.substring(endOfBracket + 1));
                //System.out.println(str);
            } 
        }
        // now, look for all '+' to solve
        String[] strsplit = str.split(" ");
        int sizeAccum = 0;
        for (int i=0; i<strsplit.length; i++){
            if (strsplit[i].equals("+")){
                long out = Long.parseLong(strsplit[i-1]) + Long.parseLong(strsplit[i+1]);
                if (strsplit.length == 3){
                    return out;
                }
                // if more processing is needed, prepare string accordingly
                String outputstr = Long.toString(out);
                // check if there is more string after out
                if (sizeAccum + strsplit[i].length() + strsplit[i+1].length() + 2 < str.length())
                    outputstr += str.substring(sizeAccum + strsplit[i].length() + strsplit[i+1].length() + 1);
                // if this is not the first operand, then tack on beginning of expression
                if (i > 1){
                    outputstr = str.substring(0, sizeAccum - strsplit[i-1].length() - 1) + outputstr;
                }
                return evaluate(outputstr);
            }
            sizeAccum += strsplit[i].length() + 1; // gotta include spaces in there
        }
        sizeAccum = 0;
        for (int i=0; i<strsplit.length; i++){
            if (strsplit[i].equals("*")){
                long out = Long.parseLong(strsplit[i-1]) * Long.parseLong(strsplit[i+1]);
                if (strsplit.length == 3){
                    return out;
                }
                // if more processing is needed, prepare string accordingly
                String outputstr = Long.toString(out);
                // check if there is more string after out
                if (sizeAccum + strsplit[i].length() + strsplit[i+1].length() + 2 < str.length())
                    outputstr += str.substring(sizeAccum + strsplit[i].length() + strsplit[i+1].length() + 1);
                // if this is not the first operand, then tack on beginning of expression
                if (i > 1){ 
                    outputstr = str.substring(0, sizeAccum - strsplit[i-1].length() - 1) + outputstr;
                }
                return evaluate(outputstr); 
            }
            sizeAccum += strsplit[i].length() + 1; // gotta include spaces in there
        }
        // at this point, string only contains a long value of results of inputs
        return Long.parseLong(str);
    }

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        long sum = 0;
        while (sc.hasNextLine()) {
            long x = evaluate(sc.nextLine());
            sum += x;
            System.out.println(x + "\t" + sum);
            if (x < 0 || sum < 0) {
                System.out.println("Overflow detected!");
                System.exit(1);
            }
        }
        // last try was 94237659710018
        // answer is 94240043727614
        sc.close();
        System.out.println(sum);
        System.exit(0);
    }
}
