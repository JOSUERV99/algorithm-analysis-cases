package Algorithms;
import java.util.Random;

public class ArraysGenerator {

	private static final int randomMaxRange = 10000000; 
	
	public int[] generateRandomNumbers(int amountNumbers) {
		Random randomGenerator = new Random();
		int generatedList[] = new int[amountNumbers];
		for (int currentIndex = 0; currentIndex < amountNumbers; currentIndex++) 
			generatedList[currentIndex] = randomGenerator.nextInt(randomMaxRange);

		return generatedList;
	}	
	
	public int[] generateRandomNotRepeatedNumbers(int amountNumbers) {
		Random randomGenerator = new Random();
		int generatedList[] = new int[amountNumbers];
		boolean usedList[] = new boolean[randomMaxRange];
		
		for (int currentIndex = 0; currentIndex < amountNumbers; currentIndex++) {
			int numberToAdd =  randomGenerator.nextInt(randomMaxRange);
			if (usedList[numberToAdd])
				continue;
			generatedList[currentIndex] = numberToAdd;
			usedList[numberToAdd] = true;
		}

		return generatedList;
	}	

	public int[] generateSortedNumbers(int amountNumbers) {
		int generatedList[] = new int[amountNumbers];
		for (int currentIndex = 0; currentIndex < amountNumbers; currentIndex++) 
			generatedList[currentIndex] = currentIndex;

		return generatedList;
	}	
	
	public int[] generateSortedInvertedNumbers(int amountNumbers) {
		int generatedList[] = new int[amountNumbers];
		for (int currentIndex = amountNumbers-1, index = 0; currentIndex >= 0; currentIndex--, index++) 
			generatedList[index] = currentIndex;

		return generatedList;
	}
	
}