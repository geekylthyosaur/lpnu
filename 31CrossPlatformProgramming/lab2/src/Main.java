import java.util.ArrayList;
import java.util.Comparator;
import java.util.List;
abstract class Housing {
    private String name;
    private int distanceToSchool;
    private int distanceToPark;

    public Housing(String name, int distanceToSchool, int distanceToPark) {
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
class Townhouse extends Housing {
    private int numberOfFloors;

    public Townhouse(String name, int distanceToSchool, int distanceToPark, int numberOfFloors) {
        super(name, distanceToSchool, distanceToPark);
        this.numberOfFloors = numberOfFloors;
    }

    public int getNumberOfFloors() {
        return numberOfFloors;
    }

    @Override
    public String toString() {
        return super.toString() + "\nNumber of Floors: " + numberOfFloors;
    }
}

// Subclass for Mansion
class Mansion extends Housing {
    private int numberOfBathrooms;

    public Mansion(String name, int distanceToSchool, int distanceToPark, int numberOfBathrooms) {
        super(name, distanceToSchool, distanceToPark);
        this.numberOfBathrooms = numberOfBathrooms;
    }

    public int getNumberOfBathrooms() {
        return numberOfBathrooms;
    }

    @Override
    public String toString() {
        return super.toString() + "\nNumber of Bathrooms: " + numberOfBathrooms;
    }
}

class Condo extends Housing {
    private int floorNumber;
    private boolean hasAmenities;

    public Condo(String name, int distanceToSchool, int distanceToPark, int floorNumber, boolean hasAmenities) {
        super(name, distanceToSchool, distanceToPark);
        this.floorNumber = floorNumber;
        this.hasAmenities = hasAmenities;
    }

    public int getFloorNumber() {
        return floorNumber;
    }

    public boolean hasAmenities() {
        return hasAmenities;
    }

    @Override
    public String toString() {
        return super.toString() + "\nFloor Number: " + floorNumber + "\nHas Amenities: " + (hasAmenities ? "Yes" : "No");
    }
}


class HousingManager {
    List<Housing> housings;

    HousingManager(List<Housing> housings) {
        this.housings = housings;
    }

    static class sortByDistanceToSchoolAsc implements Comparator<Housing> {
        @Override
        public int compare(Housing h1, Housing h2) {
            return Integer.compare(h1.getDistanceToSchool(), h2.getDistanceToSchool());
        }
    }

    class sortByDistanceToParkAsc implements Comparator<Housing> {
        @Override
        public int compare(Housing h1, Housing h2) {
            return Integer.compare(h1.getDistanceToPark(), h2.getDistanceToPark());
        }
    }

    public static Comparator<Housing> sortByDistanceToSchoolDesc() {
        return new Comparator<Housing>() {
            @Override
            public int compare(Housing h2, Housing h1) {
                return Integer.compare(h1.getDistanceToSchool(), h2.getDistanceToSchool());
            }
        };
    }

    public static Comparator<Housing> sortByDistanceToParkDesc() {
        return (h2, h1) -> Integer.compare(h1.getDistanceToPark(), h2.getDistanceToPark());
    }
}

public class Main {
    public static void main(String[] args) {
        List<Housing> housingList = new ArrayList<>();
        housingList.add(new Condo("Condo A", 2, 1, 5, true));
        housingList.add(new Mansion("Mansion B", 1, 5, 1));
        housingList.add(new Townhouse("Townhouse C", 4, 3, 2));
        HousingManager mgr = new HousingManager(housingList);

        // Sort by distance to school (ascending) using static inner class
        housingList.sort(new HousingManager.sortByDistanceToSchoolAsc());
        System.out.println("Sorted by distance to school (ascending):");
        System.out.println(housingList);

        // Sort by distance to park (ascending) using inner class
        housingList.sort(mgr.new sortByDistanceToParkAsc());
        System.out.println("\nSorted by distance to park (ascending):");
        System.out.println(housingList);

        // Sort by distance to school (descending) using anonymous inner class
        housingList.sort(HousingManager.sortByDistanceToSchoolDesc());
        System.out.println("\nSorted by distance to school (descending):");
        System.out.println(housingList);

        // Sort by distance to park (descending) using lambda expressions
        housingList.sort(HousingManager.sortByDistanceToParkDesc());
        System.out.println("\nSorted by distance to park (descending):");
        System.out.println(housingList);
    }
}
