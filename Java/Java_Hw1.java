/*
 *
 *  Corder : YoWu(uyu423@gmail.com)
 * 	Datetime : 2015.03.21 02:09
 * 	OS :  CentOS Linux 6.5 x86 (kernel 2.6.32)
 * 	Editor : Vim
 * 	Compiler : Javac 1.8.0_31
 * 	SourceEncording : UTF-8
 *
 */


/*
 * 학년이 학년이니 만큼 단순 문제풀이 보다 객체지향 설계(Data, BO, UI)를 중점코딩
 */

import java.util.Random;
import java.util.Scanner;

//랜덤숫자1, 2, 배수에 대한 Data 객체
class NumberData {
	int num;

	//NumberData 객체 생성자
	public NumberData(int num) {
		this.num = num;
	}

	//필드 접근자, 설정자
	public void setNum(int num) { this.num = num; };
	public int getNum() { return num; };
}

//난수 생성, 데이터 입력 등 실제 작업이 처리되는 객체(BO)
class Procedure {
	private Random rnd;
	public NumberData rndNum1;
	public NumberData rndNum2;
	public NumberData multiNum;

	//Procedure 객체 생성자
	public Procedure() {
		rnd = new Random();
	}

	//Random Number Generator
	public int[] makeRand() {
		int[] arr = new int[2];
		int tmp = 0;

		//난수를 생성하되 두 난수가 동일하지 않을 때 까지 생성
		while(arr[0] == arr[1]) {
			arr[0] = rnd.nextInt(300) + 1;
			arr[1] = rnd.nextInt(300) + 1;
		}

		//먼저 생성된 난수가 더 클 경우 swap
		if(arr[0] > arr[1])	{
			tmp = arr[0];
			arr[0] = arr[1];
			arr[1] = tmp;
		}
		
		return arr;
	}

	//NumberData에 대한 Procedure 객체의 inputData 메소드 Overloadding
	public void inputData(int multi) {
		multiNum = new NumberData(multi);
	}
	public void inputData(int[] arr) {
		rndNum1 = new NumberData(arr[0]);
		rndNum2 = new NumberData(arr[1]);
	}

	//Debugging 용 toString
	public String toString() {
		return "num1 = " + rndNum1.getNum() + " num2 = " + rndNum2.getNum() + " multi = " + multiNum.getNum();
	}
}

//사용자에게 입출력을 담당하는 객체(UI)
class ProcedureUI {
	private Procedure proc;
	private Scanner scan;

	//ProcedureUI 객체의 생성자
	public ProcedureUI() {
		proc = new Procedure();
		scan = new Scanner(System.in);
	}

	//초기상태 시작 메소드, 사용자로부터 값을 입력받아 Procedure 객체의 inputData 메소드 호출
	public void startProcedure() {
		int tmp;

		System.out.printf("배수 입력 : ");
		proc.inputData(scan.nextInt());
		proc.inputData(proc.makeRand());
	}

	//출력 메소드. 예제와 같이 입력받은 배수에 해당하지 않는 값이라면 #출력 맞다면 i 출력
	public void printResult() {
		int stNum = proc.rndNum1.getNum();
		int edNum = proc.rndNum2.getNum();
		int multiNum = proc.multiNum.getNum();

		for(int i = stNum; i<= edNum; i++) {
			if(i % multiNum == 0)	System.out.printf(i + " ");
			else					System.out.printf("# ");
			if(i == edNum)			System.out.println("");
		}
		System.out.println("(" + stNum + "~" + edNum + ")");
	}
}

public class Java_Hw1 {
	public static void main(String[] args) {
		ProcedureUI ui = new ProcedureUI();
		ui.startProcedure();
		ui.printResult();
	}
}

