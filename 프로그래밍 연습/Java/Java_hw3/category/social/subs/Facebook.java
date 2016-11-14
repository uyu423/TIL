package category.social.subs;

import category.social.SocialNetworkService;

public class Facebook extends SocialNetworkService { //SocialNetworkService Class를 상속받음(is a)
	public static int serviceCnt = 1;	//계정 카운트. static
	private int userNo;	//현재의 serviceCnt 값
	private int postCnt;	//생성된 post 개수
	private String lastPostContents;	//마지막으로 작성한 post의 내용
	
	//Constructor Overloading
	public Facebook(String userEmail, String userPasswd, String userName) {
		this(userEmail, userPasswd, userName, null, null);
	}

	public Facebook(String userEmail, String userPasswd, String userName, String userPhone, String userAddress) {
		super("Facebook", userEmail, userPasswd, userName, userPhone, userAddress);
		this.userNo = serviceCnt++;
		this.postCnt = 0;
		this.lastPostContents = "** Empty Contents **";
	}
	
	public int getUserNo() { return userNo; }
	public void setUserNo(int userNo) { this.userNo = userNo; }
	public int getPostCnt() { return postCnt; }
	public void setPostCnt(int postCnt) { this.postCnt = postCnt; }
	public String getLastPostContents() { return lastPostContents; }
	public void setLastPostContents(String lastPostContents) { this.lastPostContents = lastPostContents; }
	
	/* 로그인 확인 유무 메서드 */
	private boolean isLogin() {
		if(super.serviceLogin == true) {
			return true;
		}
		else {
			return false;
		}
	}
	
	/* 포스팅 메서드(내용 있음) */
	public void writePost(String Contents) {
		if(isLogin() == true) {	//로그인 유무 확인
			this.lastPostContents = Contents;
			this.postCnt++;
			System.out.println("Facebook Posting Success");
			return;
		}
		else {
			System.out.println("Posting Failed : Facebook Not Login");
			return;
		}
	}
	/* 포스팅 메서드(내용 없음) */
	//Method Overloading
	public void writePost() {
		if(isLogin() == true) {
			this.lastPostContents = "** Empty Contents **";
			this.postCnt++;
			System.out.println("Facebook Posting Success");
			return;
		}
		else {
			System.out.println("Posting Failed : Facebook Not Login");
			return;
		}
	}
	
	/* 전체 정보 표시 */
	public void showFacebookInfo() {
		super.showServiceInfo();
		System.out.println("Facebook User Number : " + this.userNo);
		System.out.println("Facebook Total Post Count : " + this.postCnt);
		System.out.println("Facebook Last Post Contents : " + this.lastPostContents);
		return;
	}
}
