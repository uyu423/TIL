/*
 *	Corder : YoWu (uyu423@gmail.com)
 *	Datetime : 2015.03.24 17:20 
 *	Title : Oop Homework 01
 *	OS : CentOS 6.5 x86 (kernel 2.6.32)
 *	Compiler : javac 1.8
 */

import java.util.Scanner;

abstract class Phone {
	private String prodNum;
	private String contNum;

	void setProdNum(String prodNum)	{ this.prodNum = prodNum; }
	void setContNum(String contNum)	{ this.contNum = contNum; }
	String getProdNum()	{ return this.prodNum; }
	String getContNum()	{ return this.contNum; }

	@Override
	public String toString() {
		return "Phone(ID : " + prodNum + ")\nNumber : " + contNum;
	}
}

class HomePhone extends Phone {
	@Override
	public String toString() {
		return "Home" + super.toString();
	}
}

class OfficePhone extends Phone {
	@Override
	public String toString() {
		return "Office" + super.toString();
	}
}

class Person {
	Scanner scan;
	private HomePhone home;
	private OfficePhone office;
	public Person() {
		home = new HomePhone();
		office = new OfficePhone();
		scan = new Scanner(System.in);
	}
	public void showInputMenu() {
		while(true) {
			System.out.println("입력할 전화기 선택(0(Home) or 1(Office))(-1은 종료) : ");
			switch(this.scan.nextInt()) {
				case -1:
					System.out.println("입력을 종료합니다");
					return;
				case 0:
					this.inputData(0);
					break;
				case 1:
					this.inputData(1);
					break;
				default:
					System.out.println("값이 잘못 입력되었습니다.");
			}
		}
	}
	public void showPrintMenu() {
		while(true) {
			System.out.println("검색할 전화기 선택(0(Home) or 1(Office))(-1은 종료) : ");
			switch(this.scan.nextInt()) {
				case -1:
					System.out.println("검색을 종료합니다");
					return;
				case 0:
					this.printData(0);
					break;
				case 1:
					this.printData(1);
					break;
				default:
					System.out.println("값이 잘못 입력되었습니다.");
			}
		}
	}
	public void inputData(int select) {
		String fflush = new String();
		System.out.printf("제품번호 입력 : ");
		if(select == 0)	{
			fflush = this.scan.nextLine();
			this.home.setProdNum(this.scan.nextLine());
		}
		else if(select == 1) { 
			fflush = this.scan.nextLine();
			this.office.setProdNum(this.scan.nextLine()); 
		}
		else { 
			System.out.println("Home Info Input Error"); 
			return; 
		}

		System.out.printf("전화번호 입력 : ");
		if(select == 0)	{ 
			this.home.setContNum(this.scan.nextLine()); 
		}
		else if(select == 1) {
			this.office.setContNum(this.scan.nextLine()); 
		}
		else { 
			System.out.println("Office Info Input Error"); 
			return; 
		}
	}

	public void printData(int select) {
		if(select == 0)	{ 
			if(this.home.getProdNum() == null && this.home.getContNum() == null) {
				System.out.println("Not exist Informaiton");
			}
			else {
				System.out.println("HomePhone(ID : " + this.home.getProdNum() + ")"); 
				System.out.println("Number : " + this.home.getContNum());
			}
		}
		else if(select == 1)	{ 
			if(this.office.getProdNum() == null && this.office.getContNum() == null) {
				System.out.println("Not exist Informaiton");
			}
			else {
				System.out.println("OfficePhone(ID : " + this.office.getProdNum() + ")"); 
				System.out.println("Number : " + this.office.getContNum());
			}
		}
		else { System.out.println("Data Print Error"); return; }
	}
}

class Oop_Hw1 {
	public static void main(String[] args) {
		Person human = new Person();
		System.out.println("전화기 설정================");
		human.showInputMenu();
		System.out.println("전화기 정보 출력================");
		human.showPrintMenu();
	}
}

