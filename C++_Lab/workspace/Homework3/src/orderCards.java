import java.util.*;

class orderCards {
	public static void orderCards(int n){
		int[] orderedDeck = new int[n];
		int c1=0;
		int c2=n+1;
		int card;

		for (int i=0; i<n; i++){
			if (i%2 == 0){ 
				c1++;
				card=c1;
			}
			else{
				c2--;
				card=c2;
			}
			orderedDeck[i] = card;
		}
		
		for(int i=0; i<n; i++){
			System.out.print(orderedDeck[i] + ",");
		}
	}
	
	public static void main (String args[]) throws Exception {

		for(int i=0; i<6; i++){
			orderCards(i);
			System.out.println("");
		}
	}
}