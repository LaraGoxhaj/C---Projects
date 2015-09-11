public class modMergeSort {
	
	public static void main(String args[]){
		int[] a = {5,2,6,7,1};
		int i = mergeCheck(a,0,4);
		System.out.println(i);
	}
	
	public static int mergeCheck(int[] a, int left, int right) {
		int checkNum = 0;
		System.out.println(left + " " + right);
		if (left < right) {
			int mid = (left + right) / 2;
			int check1 = mergeCheck(a, left, mid);
			int check2 = mergeCheck(a, mid + 1, right);
			checkNum = check1 + check2 + check(a, left, mid, right);
		}
		return checkNum;
	}

	public static int check(int[] a, int left, int mid, int right) {
		int j = mid + 1;
		int checkNum = 0;
		System.out.print(left + " " + mid + " " + right + "   ");
		for (int i = left; i <= mid; i++) {
			j = mid + 1;
			while (j <= right) {
				if (a[i] > a[j]) {
					checkNum++;
				}
				j++;
			}
		}
		System.out.println(checkNum);
		return checkNum;
	}
}