package category.social;

import java.security.MessageDigest;

public class SocialNetworkService {
	/* 필수 정보 필드 */
	protected String serviceName;	//서비스 이름
	protected boolean serviceLogin;	//서비스 로그인 유무
	private String userEmail;	//계정 이메일
	private String userPasswd;	//계정 비밀번호
	private String userName;	//사용자 이름
	/* 추가 정보 필드 */
	private String userPhone;	//사용자 연락처
	private String userAddress;	//사용자 주소
	
	/* Constructor */
	//Constructor Overloading
	public SocialNetworkService(String serviceName, String userEmail, String userPasswd, String userName) {
		this(serviceName, userEmail, userPasswd, userName, null, null);
	}

	public SocialNetworkService(String serviceName, String userEmail, String userPasswd, String userName, String userPhone, String userAddress) {
		this.serviceName = serviceName;
		this.userEmail = userEmail;
		this.setUserPasswd(userPasswd);
		this.userName = userName;
		this.userPhone = userPhone;
		this.userAddress = userAddress;
		this.serviceLogin = false;	//기본 로그인 설정은 false
	}

	/* Getter  && Setter */
	public String getUserEmail() { return userEmail; }
	public void setUserEmail(String userEmail) { this.userEmail = userEmail; }
	public String getUserPasswd() { return userPasswd; }
	public void setUserPasswd(String userPasswd) { this.userPasswd = sha(userPasswd); }	//비밀번호 암호화를 sha로
	public String getUserName() { return userName; }
	public void setUserName(String userName) { this.userName = userName; }
	public String getUserPhone() { return userPhone; }
	public void setUserPhone(String userPhone) { this.userPhone = userPhone; }
	public String getUserAddress() { return userAddress; }
	public void setUserAddress(String userAddress) { this.userAddress = userAddress; }
	
	/* Methods */
	public void showServiceInfo() {
		System.out.println("Service Name : " + this.serviceName);
		this.showUserInfo();
	}
	public void showUserInfo() {
		System.out.println("User Email : " + this.userEmail);
		System.out.println("User Password : " + this.userPasswd);
		System.out.println("User Name : " + this.userName);
		System.out.println("User Phone : " + this.userPhone);
		System.out.println("User Address : " + this.userAddress);
	}
	
	/* 로그인 메서드 */
	public void serviceLogin(String userEmail, String userPasswd) {
		if(this.serviceLogin == true) {
			System.out.println("Login Failed : Already Login");
			return;
		}
		else if(userEmail != this.userEmail) {
			System.out.println("Login Failed : Diffrent Email");
			return;
		}
		else if(this.userPasswd.equals(sha(userPasswd)) == false) {
			System.out.println("Login Failed : Diffrent Password");
			return;
		}
		else {
			System.out.println(this.serviceName + " Service Login Success");
			this.serviceLogin = true;	//로그인 성공
			return;
		}
	}
	
	/* 로그아웃 메서드 */
	public void serviceLogout() {
		if(this.serviceLogin == false) {
			System.out.println("Logout Failed : You Not Login");
		}
		else {
			System.out.println(this.serviceName + " Service Logout Success");
			this.serviceLogin = false;	//로그아웃 성공
			return;
		}
	}
	
	/* User Password SHA-256 Encrypt Method */
	protected String sha(String userPasswd) {
		String SHA = ""; 
		try{
			MessageDigest sh = MessageDigest.getInstance("SHA-256"); 
			sh.update(userPasswd.getBytes()); 
			byte byteData[] = sh.digest();
			StringBuffer sb = new StringBuffer(); 
			for(int i = 0 ; i < byteData.length ; i++){
				sb.append(Integer.toString((byteData[i]&0xff) + 0x100, 16).substring(1));
			}
			SHA = sb.toString();
			
		}catch(Exception e){
			e.printStackTrace(); 
			SHA = null; 
		}
		return SHA;
	}
}