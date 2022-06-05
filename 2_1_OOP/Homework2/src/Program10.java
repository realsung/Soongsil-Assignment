public class Program10 {

	public static void main(String[] args) {
		int [][]arr = new int[4][4];
		int cnt = 0;
		int idx1, idx2, val;
		while(cnt != 10) {
			idx1 = (int)(Math.random() * 4);
			idx2 = (int)(Math.random() * 4);
			val = (int)(Math.random() * 10 + 1);
			if(arr[idx1][idx2] == 0) {
				arr[idx1][idx2] = val;
				cnt++;
			}
		}
		for(int i=0; i<arr.length; i++) {
			for(int j=0; j<arr[i].length; j++) {
				System.out.print(arr[i][j] + "\t");
			}
			System.out.println();
		}
	}
}