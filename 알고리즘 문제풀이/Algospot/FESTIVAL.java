//DateTime : 2014. 08
//알고리즘은 맞는거 같은데 왜 안되는지 모르겠다. 나중에 다시 풀어봐야겠다.

import java.util.Scanner;

class festivalData {

    private int dayCount;
    private int teamnum;

    public int getDayCount() {
        return dayCount;
    }

    public void setDayCount(int dayCount) {
        this.dayCount = dayCount;
    }

    public int getTeamnum() {
        return teamnum;
    }

    public void setTeamnum(int teamnum) {
        this.teamnum = teamnum;
    }

    @Override
    public String toString() {
        return "festivalData [dayCount=" + dayCount + ", teamnum=" + teamnum
                + "]";
    }

}

class date {
    private int price;

    public int getPrice() {
        return price;
    }

    public void setPrice(int price) {
        this.price = price;
    }

    @Override
    public String toString() {
        return "date [price=" + price + "]";
    }

}

class dayCalc {
    private date[] day;
    private int dayCount;
    private int teamnum;
    private int sum = 0;
    private double min = 1000000;
    private int cnt = 0;

    public dayCalc(date[] day, int dayCount, int teamnum) {
        this.day = day;
        this.dayCount = dayCount;
        this.teamnum = teamnum;
    }

    public double returnValue() {
        for (int i = this.dayCount - 1; i >= 0; i--) {
            for (int j = i; j < this.dayCount; j++) {
                sum = sum + day[j].getPrice();
                cnt++;
                if (this.cnt >= this.teamnum) {
                    if (this.min > (double) sum / cnt) {
                        this.min = (double) sum / cnt;
                    }
                }
            }
            this.cnt = 0;
            this.sum = 0;
        }
        return min;
    }
}

class dayManager {

    Scanner scan = new Scanner(System.in);
    public static int totalFestival;
    festivalData fes = new festivalData();
    private date[] day;

    public void setFestivalData() {
        fes.setDayCount(scan.nextInt());
        fes.setTeamnum(scan.nextInt());
        // System.out.println(fes.toString());
        date[] day = new date[fes.getDayCount()];

        for (int i = 0; i < fes.getDayCount(); i++) {
            day[i] = new date();
            day[i].setPrice(scan.nextInt());
            // System.out.println(day[i].toString() + " ");
        }

        dayCalc cal = new dayCalc(day, fes.getDayCount(), fes.getTeamnum());
        System.out.printf("%.8f\n", cal.returnValue());
    }

}

public class Main {

    public static void main(String[] args) {
        // TODO Auto-generated method stub
        Scanner scan = new Scanner(System.in);
        dayManager man = new dayManager();
        dayManager.totalFestival = scan.nextInt();
        for (int i = 0; i < dayManager.totalFestival; i++) {
            man.setFestivalData();
        }
    }
}
