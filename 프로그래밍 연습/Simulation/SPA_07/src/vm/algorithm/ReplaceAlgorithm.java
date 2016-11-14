package vm.algorithm;

import java.util.Random;
import vm.mem.RealMemory;
import vm.mem.ReferString;

public class ReplaceAlgorithm {
	/* 해당 프레임에 value가 있는지 검사하는 정적 함수 */
	private static boolean searchFrame(RealMemory ram, int value) {
		for (int i = 0; i < ram.size; i++) {
			if (ram.frame[i] == value) {
				return true;
			}
			if (ram.frame[i] == -1) {
				return false;
			}
		}
		return false;
	}

	// Debug Function
	private static void showFrameStatus(String type, int now, RealMemory ram) {
		System.out.println(type + "| level " + now);
		for (int i = 0; i < ram.size; i++) {
			System.out.printf("%d\t", ram.frame[i]);
		}
		System.out.println();
	}

	/* Fisrt-in, First-out 페이지 교체 알고리즘 */
	public static int usingFIFO(RealMemory ram, ReferString rs) {
		int fault = 0;
		int last = 0;
		for (int i = 0; i < rs.size; i++) {
			if (searchFrame(ram, rs.strSet[i]) == false) {
				fault++;
				if (ram.isFullFrame() == true) {
					ram.frame[last++] = rs.strSet[i];
					if (last >= ram.size) {
						last = 0;
					}
				} else {
					ram.frame[ram.now++] = rs.strSet[i];
				}
			}
			// showFrameStatus("FIFO", i+1, ram);
		}
		ram.setFrameEmpty(); // frame 공간 초기화
		return fault;
	}

	/* Least Recently Used 페이지 교체 알고리즘 */
	public static int usingLRU(RealMemory ram, ReferString rs) {
		int fault = 0;
		int old = 210000000;
		int[] tb = new int[ram.size]; // 페이지 교체 Time이 저장되는 배열 tb
		for (int i = 0; i < ram.size; i++) { // tb 배열 -1로 초기화
			tb[i] = -1;
		}
		for (int i = 0; i < rs.size; i++) { // rs의 끝까지
			if (rs.mod == 'G') { // rs 타입이 locality일 때 유효값 검사
				if (rs.strSet[i] >= rs.avg * 2) {
					rs.strSet[i] = rs.avg;
				}
			}
			if (searchFrame(ram, rs.strSet[i]) == false) {
				fault++;
				if (ram.isFullFrame() == true) {
					old = 2100000000;	//INFINITY
					int oldi = 0;
					for (int j = 0; j < tb.length; j++) {	//오래동안 사양되지 않은 값과 인덱스를 검사
						if (old > tb[j]) {
							old = tb[j];
							oldi = j;
						}
					}
					ram.frame[oldi] = rs.strSet[i];
					tb[oldi] = i;
				} else {
					ram.frame[ram.now] = rs.strSet[i];
					tb[ram.now++] = i;
				}
			} else {
				for (int j = 0; j < ram.size; j++) {
					if (ram.frame[j] == rs.strSet[i]) {	//프레임에 존재하는 값일 경우 tb 갱신
						tb[j] = i;
						break;
					}
				}
			}
			// showFrameStatus("LRU", i+1, ram);
		}
		ram.setFrameEmpty(); // frame 공간 초기화
		return fault;
	}

	/* Random 페이지 교체 알고리즘 */
	public static int usingRandom(RealMemory ram, ReferString rs, final int SEED) {
		int fault = 0;
		Random rnd = new Random(SEED); // 랜덤 인스턴스 생성
		for (int i = 0; i < rs.size; i++) {
			if (searchFrame(ram, rs.strSet[i]) == false) {
				fault++;
				if (ram.isFullFrame() == true) {
					ram.frame[rnd.nextInt(ram.size)] = rs.strSet[i];
				} else {
					ram.frame[ram.now++] = rs.strSet[i];
				}
			}
			// showFrameStatus("RANDOM", i+1, ram);
		}
		ram.setFrameEmpty(); // frame 공간 초기화
		return fault;
	}

	/* Second-Chance 페이지 교체 알고리즘 */
	public static int usingSecond(RealMemory ram, ReferString rs) {
		int fault = 0;
		int last = 0;
		boolean[] mark = new boolean[ram.size];	//Boolean타입의 Value Marking Table
		for (int i = 0; i < mark.length; i++) {
			mark[i] = false;
		}
		for (int i = 0; i < rs.size; i++) {
			for (int j = 0; j < ram.size; j++) {
				if (ram.frame[j] == -1) {	//현재 검사 Frame이 빈 상태라면 삽입
					fault++;
					mark[ram.now] = true;
					ram.frame[ram.now++] = rs.strSet[i];
					break;
				}
				if (ram.frame[j] == rs.strSet[i]) {	//Frame에서 값을 찾은 경우 mark 테이블을 true로
					mark[j] = true;
					break;
				}
				if (j == ram.size - 1) {
					fault++;
					while (mark[last % ram.size] == true) { // Frame을 원형큐로 사용
						mark[last % ram.size] = false;
						last++;
					}
					ram.frame[last % ram.size] = rs.strSet[i];
					mark[last % ram.size] = true;
					last++;
				}
			}
			// showFrameStatus("SECOND-CHANCE", i+1, ram);
		}
		ram.setFrameEmpty(); // frame 공간 초기화
		return fault;
	}
}