package Algorithms;

public class SortFunctions {
	
	public void insertionSort(int[] numbers) {
		int frontIndex, key, currentIndex;  
	    for (frontIndex = 1; frontIndex < numbers.length; frontIndex++) {  
	        key = numbers[frontIndex];  
	        currentIndex = frontIndex - 1;  
	  
	        while (currentIndex >= 0 && numbers[currentIndex] > key) {  
	            numbers[currentIndex + 1] = numbers[currentIndex];  
	            currentIndex = currentIndex - 1;  
	        }  
	        numbers[currentIndex + 1] = key;  
	    }  
	}

	public void quickSort(int[] numbers, int low, int high) {

		int pivot = numbers[(low + high)/2],leftIndex = low;
        int rigthIndex = high, interchangeValue;

        while (leftIndex < rigthIndex) {
            while (numbers[leftIndex] <= pivot && leftIndex < rigthIndex) {
                leftIndex++;
            }
            while (numbers[rigthIndex] > pivot) {
                rigthIndex--;
            }
            if (leftIndex < rigthIndex) {
                interchangeValue = numbers[leftIndex];
                numbers[leftIndex] = numbers[rigthIndex];
                numbers[rigthIndex] = interchangeValue;
            }
        }

        numbers[low] = numbers[rigthIndex];
        numbers[rigthIndex] = pivot;
        
        if (low < rigthIndex - 1) {
            quickSort(numbers, low, rigthIndex - 1);
        }
        if (rigthIndex + 1 < high) {
            quickSort(numbers, rigthIndex + 1, high);
        }
	}
	
}