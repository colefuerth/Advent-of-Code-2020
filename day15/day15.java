import java.util.List;
import java.util.stream.Collector;
import java.util.stream.Stream;

public class day15 {

    public static void main(String[] args) {
        List<Integer> list = Stream.of("7,14,0,17,11,1,2".split(",")).map(Integer::parseInt).collect(toList());
        Map<Integer, Integer> lastOccurrence = list.stream().collect(toMap(identity(), list::indexOf));

        int number = 0;
        for (int index = list.size(); index < 30000000 - 1; ++index) {
            Integer last = lastOccurrence.put(number, index);
            number = last == null ? 0 : index - last;
        }
        System.out.println(number);
    }

    private static Collector toList() {
        return null;
    }

}
