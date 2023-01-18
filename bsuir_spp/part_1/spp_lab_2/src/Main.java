import mpi.*;
import java.util.*;

public class Main {
    private static String[] sArr = {"dwd", "awdw", "jwlke", "lwkdow", "dfn3lm"};

    public static void sortMethod2(String[] strArr) {
        List<String> stringList = Arrays.asList(strArr);
        Collections.sort(stringList, new Comparator<String>() {
            @Override
            public int compare(String s1, String s2) {
                if (s1.toLowerCase().equals(s1) && s2.toUpperCase().equals(s2)) {
                    return 1;
                }

                if (s1.toUpperCase().equals(s1) && s2.toLowerCase().equals(s2)) {
                    return -1;
                }

                return s1.compareTo(s2);
            }
        });
        System.out.println(stringList);
    }

    public static void sortMethod1() {
        Arrays.sort(sArr);
        System.out.print("[");
        for (var el: sArr) {
            System.out.print(el + " ");
        }
        System.out.println("]");
    }

    public static void main(String[] args) {
        MPI.Init(args);
        int me = MPI.COMM_WORLD.Rank();
        int size = MPI.COMM_WORLD.Size();
        if (me == 0) {
            sortMethod1();
        } else if (me == 1) {
            sortMethod2(sArr);
        } else if (me == 2) {
        } else {
            System.out.println("Error");
        }
        MPI.Finalize();
    }
        //System.out.println(Arrays.toString(mas));
    }