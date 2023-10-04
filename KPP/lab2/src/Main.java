import java.util.ArrayList;
import java.util.Comparator;
import java.util.List;
class House {
    private String name;
    private int distanceToSchool;
    private int distanceToPark;

    public House(String name, int distanceToSchool, int distanceToPark) {
        this.name = name;
        this.distanceToSchool = distanceToSchool;
        this.distanceToPark = distanceToPark;
    }

    public String getName() {
        return name;
    }

    public int getDistanceToSchool() {
        return distanceToSchool;
    }

    public int getDistanceToPark() {
        return distanceToPark;
    }

    @Override
    public String toString() {
        return "Housing{" +
                "name='" + name + '\'' +
                ", distanceToSchool=" + distanceToSchool +
                ", distanceToPark=" + distanceToPark +
                '}';
    }
}

class HousingManager {
    List<House> houses;

    HousingManager(List<House> houses) {
        this.houses = houses;
    }

    static class sortByDistanceToSchoolAsc implements Comparator<House> {
        @Override
        public int compare(House h1, House h2) {
            return Integer.compare(h1.getDistanceToSchool(), h2.getDistanceToSchool());
        }
    }

    class sortByDistanceToParkAsc implements Comparator<House> {
        @Override
        public int compare(House h1, House h2) {
            return Integer.compare(h1.getDistanceToPark(), h2.getDistanceToPark());
        }
    }

    public static Comparator<House> sortByDistanceToSchoolDesc() {
        return new Comparator<House>() {
            @Override
            public int compare(House h2, House h1) {
                return Integer.compare(h1.getDistanceToSchool(), h2.getDistanceToSchool());
            }
        };
    }

    public static Comparator<House> sortByDistanceToParkDesc() {
        return (h2, h1) -> Integer.compare(h1.getDistanceToPark(), h2.getDistanceToPark());
    }
}

public class Main {
    public static void main(String[] args) {
        List<House> houseList = new ArrayList<>();
        houseList.add(new House("Apartment A", 2, 1));
        houseList.add(new House("Penthouse B", 1, 5));
        houseList.add(new House("Mansion C", 4, 3));
        HousingManager mgr = new HousingManager(houseList);

        // Sort by distance to school (ascending) using static inner class
        houseList.sort(new HousingManager.sortByDistanceToSchoolAsc());
        System.out.println("Sorted by distance to school (ascending):");
        System.out.println(houseList);

        // Sort by distance to park (ascending) using inner class
        houseList.sort(mgr.new sortByDistanceToParkAsc());
        System.out.println("\nSorted by distance to park (ascending):");
        System.out.println(houseList);

        // Sort by distance to school (descending) using anonymous inner class
        houseList.sort(HousingManager.sortByDistanceToSchoolDesc());
        System.out.println("\nSorted by distance to school (descending):");
        System.out.println(houseList);

        // Sort by distance to park (descending) using lambda expressions
        houseList.sort(HousingManager.sortByDistanceToParkDesc());
        System.out.println("\nSorted by distance to park (descending):");
        System.out.println(houseList);
    }
}
