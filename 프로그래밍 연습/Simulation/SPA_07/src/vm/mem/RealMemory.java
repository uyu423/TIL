package vm.mem;

public class RealMemory {
	public int[] frame; // 프레임 공간
	public int size; // 프레임 사이즈
	public int now; // 현재 위치 flag

	public RealMemory(final int FRAME_SIZE) {
		this.frame = new int[FRAME_SIZE];
		this.size = FRAME_SIZE;
		this.setFrameEmpty();
	}

	public void setFrameEmpty() {
		for (int i = 0; i < frame.length; i++) {
			frame[i] = -1;
		}
		this.now = 0;
	}

	public boolean isFullFrame() {
		if (now >= size) {
			return true;
		}
		return false;
	}
}