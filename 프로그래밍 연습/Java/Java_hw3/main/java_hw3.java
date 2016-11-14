/*
*	ProjectName	: 2015-1 객체지향프로그래밍 설계 Homework 03
*	Corder 		: 유용우 / 201021395
*	Organiz.	: Catholic Univ. of Korea
*	Major		: Computer Science (Minor : Infomation System Eng)
*	DateTime	: 2015.06.10 22:40
*	Develop OS	: Microsoft Windows 8.1 Embedded Industy Pro (x64)
*	PorgramLang	: Java (Java1.8.0_45)
*	IDE			: Eclipse Luna
*	Compiler	: Javac 1.8
*/

package main;

import category.social.SocialNetworkService;	//import Super Class
import category.social.subs.Facebook;	//import Sub Class

public class java_hw3 {

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		SocialNetworkService blogServ = new SocialNetworkService("Blog", "uyu423@gmail.com", "1q2w3e4r", "Yu Yongwoo");
		blogServ.showServiceInfo();	//서비스 정보 표시
		System.out.println();
		blogServ.serviceLogout();	//로그아웃 -> 로그인 하지 않았으므로 실패
		blogServ.serviceLogin("uyu423@gmail.com", "1q2w3e4r");	//로그인 -> 성공
		blogServ.serviceLogout();	//로그아웃 -> 로그인 했으므로 성공
		System.out.println();
		
		Facebook fbServ = new Facebook("qkrrhdms@gmail.com", "qqqq", "Park Goeun", "010-4617-****", "Earth");
		fbServ.showFacebookInfo();	//서비스 정보 표시
		System.out.println();
		fbServ.serviceLogin("qkrrhdms@gmail.com", "1q2w3e4r");	//로그인 -> 비밀번호 틀려서 실패
		fbServ.writePost("Hello World !");	//포스팅 -> 로그인 하지 않았으므로 실패
		fbServ.serviceLogin("qkrrhdms@gmail.com", "qqqq");	//로그인 -> 성공
		fbServ.writePost("Hello World !");	//포스팅 -> 성공
		System.out.println();
		fbServ.showFacebookInfo();	//서비스 정보 표시 -> 포스팅 관련 변수 값 변경됨
		System.out.println();
		fbServ.writePost();	//포스팅 -> 성공
		System.out.println();
		fbServ.showFacebookInfo(); //서비스 정보 표시 -> 포스팅 관련 변수 값 변경됨
		System.out.println();
		fbServ.serviceLogout(); //로그아웃 -> 성공
	}

}
