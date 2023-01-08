import java.time.DayOfWeek;
import java.time.LocalDate;

public class Work_1 {
    static void run() {
        System.out.println("\nWORK 1\n\n");

        LocalDate date = LocalDate.now();
        DayOfWeek dayOfWeek = date.getDayOfWeek();
        System.out.println("Silence is golden");
        System.out.println(dayOfWeek);
        System.out.println(date.getMonth());
        System.out.println("Maksim");
    }
}
