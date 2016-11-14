/*
 * ProjectName : Java Homework Project 2 - Umbrella
 * Name : 유용우 (uyu423@gmail.com)
 * Major : 컴퓨터공학
 * StdNum : 201021395
 * ================================================= *
 * ClassName : Level
 * ClassDescription : Umbrella Class의 내부 필드 Level(단) 정의 클래스 
 * DateTime : 2015. 04. 11 21:32
 * OS : Windows Embedded 8.1 Industry Pro (x64)
 * IDE : Eclipse Luna Service Release 2 (4.4.2)
 * Version : JavaSE-1.8
 */

package java_hw2;

/* Umbrella 객체에 포함된 Level 객체를 정의 */
public class Level {
	private int value;	//단 정보 값을 가지는 필드

	/* 기본 생성자, 기본 값은 2다. */
	public Level() {
		this.setValue(2);
		return;
	}
	
	/* 생성자, value 값이 1~3일 때만 처리한다. */
	public Level(int value) {
		if(value >= 1 && value <= 3) {
			this.setValue(value);
			return;
		}
		this.setValue(2);
	}

	/* value값에 따른 가격을 반환하는 메소드 */
	public int retPrice() {
		if(this.value == 1 || this.value == 2)
			return 5000;
		else if(this.value == 3)
			return 6000;
		else	return -1;	//error handling
	}
	
	/* value값을 String으로 반환하는 메소드 */
	@Override
	public String toString() {
		return String.valueOf(this.getValue());
	}
	
	/* 접근자, 설정자 정의 */
	public int getValue() { return value; }
	public void setValue(int value) { this.value = value; }
}
