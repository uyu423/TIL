import java.util.Random;
import java.util.Scanner;

/* 푸아송 함수 선언 */
class Calc {
	public static double poissn(int mean, int seed) {
		Random rnd = new Random(seed);
		double b, prod = 1.0, u, p = 0;
		b = Math.exp((double)-mean);	//자연로그 밑 e를 -mean 만큼 제곱
		u = (double)rnd.nextDouble();	//0~1 사이의 일양분포 생성
		prod = prod * u;
		while(prod >= b) {
//			System.out.println(prod + " " + b + " " + u + " " + p);	//Poisson Debug Function
			u = (double)rnd.nextDouble();	//0~1사이의 일양분포 생성
			prod = prod * u;	//prod에 곱해줘서 prod가 b보다 작아질 때까지 p 증가
			p++;
		}
		return p;	//푸아송 분포를 가지는 p 값 리턴
	}

	/* 푸아송 함수 값 분포 테스트 메소드 */
	public static void poissonTest(int cnt, int mean, int seed) {
		Random rnd = new Random(seed);
		int[] arr = new int[mean*3];
		for(int i = 0; i < mean*3; i++) {
			arr[i] = 0;
		}
		for(int i = 0; i < cnt; i++) {
			arr[(int)Calc.poissn(mean, rnd.nextInt())]++;
		}
		for(int i = 0; i < mean*3; i++) {
			System.out.println("arr[" + i + "] = " + arr[i]);
		}
		return;
	}
}

class GasStation {
	Random rnd;	//Random Generator 선언
	/*	
	 *	** INTEGER **
	 *	seed : 난수 시드값
	 *	mean : 평균 서비스 시간
	 *	arrive : 고객 도착 여부
	 *	queue : 대기자 수
	 *	tlimit : TIME = 0~tlimit
	 *	toque : 총 고객 수
	 *	quenum : 창구(Server, Queue) 개수
	 *
	 *	** DOUBLE **
	 *	tstep : 시간 증가량
	 *	prarr : 고객이 tstep내 도착할 확률
	 *	u : 일양 분포를 가지는 랜덤 값
	 *	p: 푸아송 분포를 가지는 랜덤 값
	 */
	int seed, mean, arrive, queue, tlimit, totque, quenum; 
	double tstep, prarr, time, u, p;
	Queue[] tpump;	//Queue로 사용할 인스턴스 생성

	/* GasStation Generator, init values and allocate instance */
	public GasStation(double tstep, double prarr, int seed, int mean, int quenum) {
		/* quenum 만큼 창구(Queue) 생성 */
		this.quenum = quenum;
		tpump = new Queue[this.quenum];
		for(int i = 0; i < this.quenum; i++) {
			tpump[i] = new Queue();
		}

		this.tstep = tstep;
		this.prarr = prarr;
		this.mean = mean;
		this.seed = seed;
		this.time = 0;
		this.tlimit = 100;
		this.p = 0;
		this.totque = 0;
		this.queue = 0;
		rnd = new Random(this.seed);	//seed 값을 가지는 Random 객체 생성
	}
	
	/* Start the Gas Station business */
	public void open() {
		this.showInitState();

		/* 시간이 tstep 만큼 tlimit이 될 때 까지 증가 */
		for(time = tstep; time <= tlimit; time = time+tstep) {
			arrive = 0;	//매 tstep에 대해 도착 여부 초기화
			u = rnd.nextDouble();

			/* u가 prarr * tstep 보다 작으면 고객이 도착. */
			if(u < prarr * tstep) {
				arrive = 1;
				queue  = queue + arrive;	//대기자수 증가
			}

			/* 두개의 Queue(tpump)를 체크하면서 큐가 비었을 경우 큐 사용 */
			for(int i = 0; i < quenum; i++) {
				if(tpump[i].getCnt() > 0) {
					//큐[i]가 이미 사용 중이라면 해당 창구의 값을 tstep 만큼 감소
					tpump[i].setCnt(tpump[i].getCnt() - tstep);
					if(tpump[i].getCnt() < 0) {
						//tpump[i]-tstep이 음수가 되었을 때의 예외처리
						tpump[i].setCnt(0);
					}
				}

				/* tpump[i]가 빈 상태이고 대기자가 있을 경우 */
				if(tpump[i].getCnt() == 0 && queue != 0) {
					//고객 감소 후 작업 시간을 푸아송 분포로 tpump[i].cnt로 할당
					queue--;
					p = Calc.poissn(mean, rnd.nextInt());
					tpump[i].setCnt(p);
				}
			}
			totque = totque + queue;	//총 고객수 카운터
			System.out.printf("%f\t%d\t%d", time, arrive, queue);
			for(int i = 0; i < quenum; i++) {
				System.out.printf("\t%f", tpump[i].getCnt());
			}
			System.out.println();
		}
		System.out.println("\nAVERAGE : " + (double)totque / (tlimit / tstep));	
		return;
	}

	/* 초기상태 출력 함수 */
	private void showInitState() {
		System.out.printf("\nSIMULATION FOR A GAS STATION QUEUEING SYSTEM\n");
		System.out.printf("TO EVALUATE MEAN QUEUE LENGTH\n");
		System.out.printf("\tTWO SERVERS AND\n");
		System.out.printf("\tTHE SERVICE TIME HAS POISSOM DISTRIBUTIION\n\n");
		System.out.println("THE TIME STEP : " + this.tstep);
		System.out.println("THE TIME LIMIT : " + (double)this.tlimit);
		System.out.println("THE ARRIVAL PROBABILITY : " + this.prarr);
		System.out.println("THE POISSON MEAN : " + (double)this.mean);
		System.out.println("THE RANDOM SEED : " + this.seed);
		System.out.printf("TIME\t\tARRIVAL\tQUEUE\t");
		for(int i = 0; i < quenum; i++) {
			System.out.printf("TPUMP[%d]\t", i);
		}
		System.out.println();
		return;
	}
}

/* tpump를 나타낼 객체 선언 */
class Queue {
	private double cnt;
	public Queue() {
		this.cnt = 0;
	}
	public void setCnt(double cnt) {
		this.cnt = cnt;
	}
	public double getCnt() {
		return this.cnt;
	}
}

class SPA_05 {
	public static void main(String[] args) {		
		double tstep, prarr;
		int seed, mean, quenum;
		Scanner scan = new Scanner(System.in);

		/* input st */
 		System.out.printf("input tstep : ");	tstep = scan.nextDouble();	//시간 증가량
		System.out.printf("input prarr : ");	prarr = scan.nextDouble();	//고객 도착 확률
		System.out.printf("input seed : ");	seed = scan.nextInt();		//랜덤 시드 값
		System.out.printf("input mean : ");	mean = scan.nextInt();	 	//평균 서비스 시간
		System.out.printf("input ququeNum : ");	quenum = scan.nextInt();	//창구 개수
		/* input ed*/

//		Calc.poissonTest(1000, mean, seed);	//푸아송 분포 값 분포 테스트 함수

		/* Generate GasStation Instance at Default values */ 
//		GasStation gas = new GasStation(1, 0.333333, 921203, 4, 2);
		GasStation gas = new GasStation(tstep, prarr, seed, mean, quenum);
		gas.open();
		return;
	}
}
