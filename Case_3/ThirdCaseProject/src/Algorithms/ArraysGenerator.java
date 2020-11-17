package Algorithms;

import java.util.Arrays;
import java.util.Collections;
import java.util.List;
import java.util.Random;
import java.util.stream.Collectors;

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
		List<Integer> list = Arrays.stream(this.generateSortedNumbers(amountNumbers)).boxed().collect(Collectors.toList());
		Collections.shuffle(list);
		return list.stream().mapToInt(i->i).toArray();
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