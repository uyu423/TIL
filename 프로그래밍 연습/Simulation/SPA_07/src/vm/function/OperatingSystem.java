package vm.function;

import vm.algorithm.ReplaceAlgorithm;
import vm.mem.RealMemory;
import vm.mem.ReferString;

public class OperatingSystem {
	final int SEED; // 랜덤 시드 값
	RealMemory[] mem; // 실제 메모리 프레임 인스턴스
	ReferString[] rsd; // non locality reference string set 인스턴스 배열
	ReferString[] rsp; // locality reference string set 인스턴스 배열
	int[] referSize; // 테스트할 rs 사이즈 배열
	int[] referRange; // 테스트할 rs 범위 배열
	int[] frameSize; // 테스트할 프레임 사이즈 배열

	public OperatingSystem() {
		SEED = 921203;
		referSize = new int[] { 1000, 5000, 10000, 50000, 100000 };
		referRange = new int[] { 20, 40, 80, 160, 320, 640 };
		frameSize = new int[] { 8, 16, 32, 64, 128, 256 };
		/* Default Test Case */
		// referSize = new int[] {20};
		// referRange = new int[] {10};
		// frameSize = new int[] {4};
		mem = new RealMemory[frameSize.length];
		rsd = new ReferString[referSize.length * referRange.length];
		rsp = new ReferString[referSize.length * referRange.length];

		this.setMemory();
		this.setReferString(SEED);
	}

	/* 메모리 인스턴스들 생성 */
	private void setMemory() {
		for (int i = 0; i < frameSize.length; i++) {
			mem[i] = new RealMemory(frameSize[i]);
		}
		return;
	}

	/* rs 인스턴스들 생성 */
	private void setReferString(final int SEED) {
		/*
		 * public ReferString(int RS_SIZE, int RANGE, int SEED, char MOD) MOD G
		 * : make random values having locality distribution, RANGE value is MAX
		 * Index MOD D : make random values using only uniform distribution,
		 * RANGE value is Poisson Average Value
		 */
		int cnt = 0;
		for (int i = 0; i < referSize.length; i++) {
			for (int j = 0; j < referRange.length; j++) {
				rsd[cnt] = new ReferString(referSize[i], referRange[j], SEED,
						'D');
				rsp[cnt] = new ReferString(referSize[i], referRange[j], SEED,
						'G');
				cnt++;
			}
		}
		// rsd[0].showLocality();
		// rsp[0].showLocality();
		return;
	}

	/* Test Start */
	public void excuteMem() {
		System.out
				.println("ALGORITHM\tF_SIZE\tR_MOD\tR_SIZE\tR_RANGE\tFAULT_CNT");
		// using BASIC RS
		for (int i = 0; i < frameSize.length; i++) {
			for (int j = 0; j < referSize.length * referRange.length; j++) {
				printStatus("RANDOM",
						ReplaceAlgorithm.usingRandom(mem[i], rsd[j], SEED),
						mem[i], rsd[j]);
				printStatus("FIFO", ReplaceAlgorithm.usingFIFO(mem[i], rsd[j]),
						mem[i], rsd[j]);
				printStatus("LRU", ReplaceAlgorithm.usingLRU(mem[i], rsd[j]),
						mem[i], rsd[j]);
				printStatus("SECOND",
						ReplaceAlgorithm.usingSecond(mem[i], rsd[j]), mem[i],
						rsd[j]);
			}
		}

		// using LOCALITY RS
		for (int i = 0; i < frameSize.length; i++) {
			for (int j = 0; j < referSize.length * referRange.length; j++) {
				printStatus("RANDOM",
						ReplaceAlgorithm.usingRandom(mem[i], rsp[j], SEED),
						mem[i], rsp[j]);
				printStatus("FIFO", ReplaceAlgorithm.usingFIFO(mem[i], rsp[j]),
						mem[i], rsp[j]);
				printStatus("LRU", ReplaceAlgorithm.usingLRU(mem[i], rsp[j]),
						mem[i], rsp[j]);
				printStatus("SECOND",
						ReplaceAlgorithm.usingSecond(mem[i], rsp[j]), mem[i],
						rsp[j]);
			}
		}
	}

	private void printStatus(String algo, int fault, RealMemory fr,
			ReferString rs) {
		System.out.println(algo + "\t" + fr.size + "\t" + rs.mod + "\t"
				+ rs.size + "\t" + (rs.mod == 'G' ? rs.avg : rs.range) + "\t"
				+ fault);
		return;
	}
}
