/*
 * ProjectName : Java Homework Project 2 - Umbrella
 * Name : 유용우 (uyu423@gmail.com)
 * Major : 컴퓨터공학
 * StdNum : 201021395
 * ================================================= *
 * ClassName : Frame
 * ClassDescription : Umbrella Class의 내부 필드 Frame(살) 정의 클래스 
 * DateTime : 2015. 04. 12 22:44
 * OS : Windows Embedded 8.1 Industry Pro (x64)
 * IDE : Eclipse Luna Service Release 2 (4.4.2)
 * Version : JavaSE-1.8
 */


package java_hw2;

/* Umbrella 객체에 포함된 Frame 객체를 정의 */
public class Frame {
	private int value;	//살 정보를 가지는 필드
	private double multiple;	//value의 값에 따라 배수를 정의
	
	/* 기본 생성자. 기본 값은 각각  6, 1.0이다. */
	public Frame() {
		this.setMultiple(1.0);
		this.setValue(6);
		return;
	}
	
	/* 생성자. value 값이 6, 8, 12일 때만  생성자로 처리한다.*/
	public Frame(int value) {
		if(value == 6 || value == 8 || value == 12)
			this.value = value;
		else	
			this.value = 6;
		this.calcMultiple();	//배수를 계산하는 메소드 호출
		return;
	}
	
	/* 배수를 계산하는 메소드 */
	private void calcMultiple() {
		switch(this.value) {
			case 6:
				this.setMultiple(1.0);
				break;
			case 8:
				this.setMultiple(1.1);
				break;
			case 12:
				this.setMultiple(1.15);
				break;
			//value error handling
			default:
				this.setMultiple(-1);
		}
	}
	
	/* getMultiple() 참조 메소드, multiple 값을 반환한다. */
	public double retMultiple() {
		return this.getMultiple();
	}
	
	/* value 값을 String으로 출력 */
	@Override
	public String toString() {
		return String.valueOf(this.getValue());
	}
	
	/* 접근자 및 설정자 정의 */
	public int getValue() { return this.value; }
	public void setValue(int value) { 
		this.value = value;
		this.calcMultiple();
	}
	public double getMultiple() { return this.multiple; }
	public void setMultiple(double multiple) { this.multiple = multiple; }
}
