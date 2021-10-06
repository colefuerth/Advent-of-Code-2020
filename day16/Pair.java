
public class Pair implements Comparable<Pair>{
    public int first;
    public int second;

    public Pair(int f, int s){
        this.first = f;
        this.second = s;
    }

    public Pair(){
        this(0, 0);
    }

    public int avg(){
        return (this.first + this.second)/2;
    }
    @Override
    public int compareTo(Pair arg0) {
        Pair that = (Pair) arg0;
        int a1 = this.avg();
        int a2 = that.avg();
        if (a1 < a2)
            return -1;
        if (a1 > a2)
            return 1;
        return 0;
    }
    @Override
    public String toString() {
        return this.first + "-" + this.second;
    }
}