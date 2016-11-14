/*
 *
 *  	Corder : YoWu(uyu423@gmail.com)
 * 	Datetime : 2015.03.21 02:09
 * 	OS :  CentOS Linux 6.5 x86 (kernel 2.6.32)
 * 	Editor : Vim
 * 	Compiler : Javac 1.8.0_31
 * 	SourceEncording : UTF-8
 *
 */

 /*
 다음 조건에 맞도록 프로그램을 작성하시오. 
 - 랜덤으로 수 2개를 결정한다. 랜덤 수는 1~300 사이의 값이다. 
 - 랜덤으로 결정된 두 수가 만일 동일하다면 다시 랜덤으로 결정되어야 한다.(서로 다른 값이 될 때까지 반복) 
 - 정수를 하나 입력받는다. 이 정수는 배수 값으로 사용할 것이다. 
 - 두 랜덤 수 사이의 값들 중 입력한 배수 값의 배수에 해당하면 출력하고 그렇지 않으면 “#”을 출력하도록 한다. 
 - 출력 할 때는 한 라인에 최대 10개씩 출력한다. 
 - 아래 출력 결과 예를 참고하도록 한다.
	출력 결과 예1)
	배수 입력: 13
	# # # # # 65 # # # # # # # # # # # # 78 # # # # # # # # # # # # 91 # # # # # # # # # # # # 104 # # # #
	(60~108)
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

