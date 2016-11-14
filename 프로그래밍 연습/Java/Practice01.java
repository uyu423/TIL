import java.util.Scanner;

//Data
class StudentData {
	int point;

	public StudentData(int point) {
		this.setPoint(point);
	}

	public int getPoint() {
		return point;
	}

	public void setPoint(int point) {
		this.point = point;
	}

}

// B.O
class calcPoint {

	private int sum = 0;
	private double val;

	public double calc(StudentData[] stu, int cnt) {

		for (int i = 0; i < cnt; i++) {
			this.sum = this.sum + stu[i].getPoint();
		}

		this.val = sum / cnt;
		return this.val;

	}
}

// I.O
class Machine {

	private int cnt;
	Scanner scan = new Scanner(System.in);

	public void startFunc() {
		System.out.printf("학생 수를 입력하시오 : ");
		this.cnt = scan.nextInt();
		StudentData[] stu = new StudentData[cnt];
		for (int i = 0; i < cnt; i++) {
			System.out.printf("학생 " + (i + 1) + "의 성적을 입력하시오 : ");
			int temp = scan.nextInt();
			if (temp > 100) {
				System.out.println("잘못된 성적입니다. 다시 입력하시오.");
				i--;
				continue;
			}
			stu[i] = new StudentData(temp);
		}
		calcPoint calc = new calcPoint();
		this.printData(calc.calc(stu, this.cnt));
	}

	private void printData(double value) {
		System.out.println("성적 평균은 " + value + "입니다.");
	}

}

public class Students {

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		Machine shit = new Machine();
		shit.startFunc();
	}

}

