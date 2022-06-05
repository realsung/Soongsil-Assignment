public class Program12 {

	public static void main(String[] args) {
		int val, sum = 0;
		for(int i=0; i<args.length; i++) {
			try {
				val = Integer.parseInt(args[i]); 
				sum += val;
			}catch(NumberFormatException e) {
				continue;
			}
		}
		System.out.println(sum);
	}

}