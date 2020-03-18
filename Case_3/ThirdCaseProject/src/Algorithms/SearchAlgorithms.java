package Algorithms;

public class SearchAlgorithms {

	public int binarySearch(int[] numbers, int numberToFind, int minLimit, int maxLimit) {
		if (numberToFind < numbers[minLimit] || numberToFind > numbers[maxLimit])
			return -1;

		int midIndex = (minLimit + maxLimit)/2;
		if (numbers[midIndex] == numberToFind) {
			return numbers[midIndex];
		} else if (numberToFind < numbers[midIndex]) {
			return binarySearch(numbers, numberToFind, minLimit, midIndex-1);
		} else {
			return binarySearch(numbers, numberToFind, midIndex + 1, maxLimit);
		}
	}

	public int interpolationSearch(int[] numbers, int numberToFind) {
		int lowerIndex = 0, higherIndex = numbers.length-1;

		while (lowerIndex < higherIndex && numberToFind >= numbers[lowerIndex] && numberToFind <= numbers[higherIndex]) {
			if (lowerIndex == higherIndex) {
				if (numbers[lowerIndex] == numberToFind)
					return lowerIndex;
				else
					return -1;
			}

	        int intercaledPosition = (int) (lowerIndex + 
	        		(( (double) ((higherIndex - lowerIndex) / (numbers[higherIndex] - numbers[lowerIndex]))) 
	        			* (numberToFind - numbers[lowerIndex]))); 
	  
	        if (numbers[intercaledPosition] == numberToFind) 
	            return intercaledPosition; 
	        if (numbers[intercaledPosition] < numberToFind) 
	            lowerIndex = intercaledPosition + 1; 
	        else
	            higherIndex = intercaledPosition - 1;
		}

		return -1;
	}

	public int sequentialSearch(int[] numbers, int numberToFind) {
		int currentIndex = 0;
		while (currentIndex < numbers.length) {

			if (numbers[currentIndex] == numberToFind)
				return currentIndex;

			if (numbers[currentIndex] > numberToFind)
				break;

			currentIndex++;
		}
		return -1;
	}

}