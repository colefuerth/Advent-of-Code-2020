import java.util.HashSet;
import java.util.Set;

public class Cube {
    // each cube has a bool for whether it is active
    public boolean active;
    public Set<Cube> adjacent;

    public Cube(char state){
        if (state == '#')
            this.active = true;
        else
            this.active = false;
        this.adjacent = new HashSet<>();
    }

    public int activeAdjacent(){
        int count = 0;
        for (Cube c : adjacent){
            if (c.active)
                ++count;
        }
        return count;
    }

    public void addAdjacentCube(Cube cube){
        adjacent.add(cube);
    }

    @Override
    public String toString() {
        if (this.active)
            return "#";
        else
            return ".";
    }

}
