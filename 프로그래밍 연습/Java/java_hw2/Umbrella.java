/*
 * ProjectName : Java Homework Project 2 - Umbrella
 * Name : 유용우 (uyu423@gmail.com)
 * Major : 컴퓨터공학
 * StdNum : 201021395
 * ================================================= *
 * ClassName : Umbrella
 * ClassDescription : 우산 객체를 표현할 Umbrella 정의 클래스 
 * DateTime : 2015. 04. 10 17:29
 * OS : Windows Embedded 8.1 Industry Pro (x64)
 * IDE : Eclipse Luna Service Release 2 (4.4.2)
 * Version : JavaSE-1.8
 */

package java_hw2;

/* 복잡한 정보를 가지는 Level(단), Frame(살)을 객체로 선언 */
public class Umbrella {
	private Level level;	//단 필드
	private Frame frame;	//살 필드
	private boolean auto;	//자동우산 유/무 필드
	private String str;		//문자열 필드
	private int price;		//가격 정보 필드
	
	//Constructor Example :
	//Umbrella u1 = new Umbrella(1, false, 6, "Happy");
	public Umbrella() {};	//기본 생성자
	
	/* Umbrella 객체 생성자, 예제의 형식을 따른다. */
	public Umbrella(int level, boolean auto, int frame, String str) {
		this.level = new Level(level);	//level 필드를 level 파라미터를 사용해 Level 객체로 생성
		this.frame = new Frame(frame);	//frame 필드를 frame 피라미터를 사용해 Frame 객체로 생성
		this.auto = auto;	//auto 초기화
		this.str = str;		//str 초기화
		this.calcPrice();	//가격 계산 메소드(calcPrice()) 호출
	}
	
	/* price 필드 값을 계산하는 메소드, 각각의 필드에 변화가 생길 때 마다 호출된다. */
	private void calcPrice() {
		int price = 0;
		if(this.isAuto())	price += 2000;
		if(this.getStr() != null)	price += 2000;	
		price += level.retPrice();
		price *= frame.retMultiple();
		this.setPrice(price);
	}
	
	//Print Method Example :
	//u1.showInfoUm();
	//2단 자동우산
	//(우산 살대수: 12)
	//삽입 문구: Happy
	//가격: 10350
	public void showInfoUm() {
		System.out.println(this.makeInfoStr());
		return;
	}
	
	/* 화면에 출력할 문자열을 조합하는 메소드 */
	public String makeInfoStr() {
		String output = level.toString() + "단";
		if(this.isAuto()) {
			output += " 자동";
		} output += " 우산\n";
		output += "(우산 살대수: " + frame.toString() + ")\n";
		if(this.getStr() != null) {
			output += "삽입 문구 : " + this.getStr() + "\n";
		}
		output += "가격 : " + this.getPrice() + "\n";
		
		return output;
	}
	
	/* getter, setter 선언, setter의 경우 실행될 때 마다 clacPrice()함수를 호출한다.  */
	public void setIsLevel(int dan) { 
		this.level.setValue(dan);
		this.calcPrice();
	}
	public void setIsFrame(int sal) { 
		this.frame.setValue(sal);
		this.calcPrice();
	}
	public void setAuto(boolean auto) { 
		this.auto = auto;
		this.calcPrice();
	}
	public void setStr(String str) { 
		this.str = str;
		this.calcPrice();
	}
	public void setPrice(int price) { this.price = price; }
	
	public String getIsLevel() { return this.level.toString(); }
	public String getIsFrame() { return this.frame.toString(); }
	public boolean isAuto() { return this.auto; }
	public String getStr() { return this.str; }
	public int getPrice() { return price; }
}
