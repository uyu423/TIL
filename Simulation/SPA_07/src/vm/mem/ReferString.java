package vm.mem;

import java.util.Arrays;
import java.util.Random;

public class ReferString {
	Random rnd; // Random 객체
	public int[] strSet; // 실제 rs 리스트 저장공간
	public int size; // rs 사이즈
	public int range; // rs 범위
	public int avg; // rs 평균
	public char mod; // rs 타입

	/* Reference String 생성자 */
	public ReferString(int RS_SIZE, int RANGE, int SEED, char MOD) {
		this.size = RS_SIZE;
		this.mod = MOD;
		this.rnd = new Random(SEED);
		this.strSet = new int[RS_SIZE];

		/* MOD=='D' : Non Locality || MOD=='G' : Locality(using Gaussian) */
		switch (MOD) {
		case 'D':
			this.range = RANGE;
			this.avg = -1;
			this.makeStringDefault(range, SEED, 0, strSet.length);
			break;
		case 'G':
			this.range = RANGE;
			this.avg = RANGE / 2;
			this.makeStringDefault(range, SEED, 0, strSet.length / 5);
			this.makeStringGaussian(avg, avg / 10, SEED, strSet.length / 5,
					strSet.length / 5 * 2);
			this.makeStringDefault(range, SEED, strSet.length / 5 * 2,
					strSet.length / 5 * 3);
			this.makeStringGaussian((int) (avg * 1.5), avg / 10, SEED,
					strSet.length / 5 * 3, strSet.length / 5 * 4);
			this.makeStringDefault(range, SEED, strSet.length / 5 * 4,
					strSet.length);
			break;
		default:
			System.out.println("Make ReferString MOD Exception : " + MOD);
			return;
		}
	}

	/* 일양 분포의 리스트 생성 */
	public void makeStringDefault(int RANGE, int SEED, int st, int ed) {
		for (int i = st; i < ed; i++) {
			strSet[i] = rnd.nextInt(RANGE);
		}
	}

	/* 가우시안 분포 형태의 리스트 생성 */
	private void makeStringGaussian(int RANGE, int STDEV, int SEED, int st,
			int ed) {
		for (int i = st; i < ed; i++) {
			double v1, v2, s, temp;
			do {
				v1 = 2 * rnd.nextDouble() - 1; // -1.0 ~ 1.0 사이의 일양분포 생성
				v2 = 2 * rnd.nextDouble() - 1; // -1.0 ~ 1.0 사이의 일양분포 생성
				s = (v1 * v1) + v2 * v2;
			} while (s >= 1 || s == 0);
			s = Math.sqrt((-2 * Math.log(s)) / s);
			temp = v1 * s;
			temp = (STDEV * temp) + (double) RANGE; // 평균 값과 표준편차 값이 적용된 가우시안 값을
													// 생성
			strSet[i] = (int) temp > 0 ? (int) temp : (int) temp * -1;
		}
	}

	/* 지역성 테스트 메소드 */
	public void showLocality() {
		System.out.println(this.toString());
		int value = this.mod == 'G' ? this.avg * 2 : this.range;
		int[] cnt = new int[value];
		for (int i = 0; i < cnt.length; i++) {
			cnt[i] = 0;
		}
		for (int i = 0; i < this.strSet.length; i++) {
			cnt[strSet[i]]++;
		}
		for (int i = 0; i < cnt.length; i++) {
			System.out.printf("[%d] : ", i);
			for (int j = 0; j < cnt[i]; j++) {
				System.out.printf("*");
			}
			System.out.println();
		}

	}

	@Override
	public String toString() {
		return "ReferString [strSet=" + Arrays.toString(strSet) + "]";
	}
}
