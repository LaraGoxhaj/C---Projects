// STUDENT1_NAME: Lara Goxhaj
//STUDENT1_ID: 260574574
//LG: From here on out, comments written by me will be preceded with "LG:"

import java.io.*;
import java.util.*;

class ex8 {
	public static int modMergeSort(studentList L1,studentList L2) {
		int i = 0;
		int num1 = L1.studentID.length;
		int num2 = L1.studentID.length;
		int[] list1 = L1.studentID;
		int[] list2 = L2.studentID;
		int[] A = new int[num1 + num2];
		for (int i = 0; i < num1; i++) {
			A[i] = list1[i];
		}
		for (int i = 0; i < num2; i++) {
			A[i + num1] = list2[i];
		}
		Arrays.sort(A);
		int p = 0;
		while (p < num1 + num2 - 1) {
			if (A[p] == A[p + 1]) {
				both++;
				p += 2;
			} else
				p++;
		}
		return both;
	}

		public static void main(String args[]){
			int a[] = {5,2,6,7,1};
			//int i = modMergeSort();
			//System.out.println(i);
		}
}
