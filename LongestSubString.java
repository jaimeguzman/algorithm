import java.util.Arrays;
import java.util.HashMap;
import java.util.Map;

public class LongestSubString {
	// Given an array containing only stars '*' and hashes '#' . Find longest contiguous sub array that will contain
	// equal no. of stars '*' and hashes '#'.
	// Order (n) solution required

	private static final String input1 = "##*#**"; // 6
	private static final String input2 = "##############*#"; // 2

	public static void main(String[] args) {
		System.out.println(get(input1));
		System.out.println(get(input2));
	}

	public static int get(String input) {
		if (null == input)
			return -1;

		int[] arr = new int[input.length()];
		char[] str = input.toCharArray();

		// * = 1, # = -1
		int sum = 0;
		for (int i = 0; i < str.length; i++) {
			if (str[i] == '*')
				sum += 1;
			else if (str[i] == '#') {
				sum -= 1;
			} else {
				System.out.println("invalid input: " + str[i]);
			}
			arr[i] = sum;
		}

		System.out.println("arr = " + Arrays.toString(arr));

		int max = -1;
		Map<Integer, Integer> pos = new HashMap<Integer, Integer>();
		pos.put(0, -1);
		for (int i = 0; i < arr.length; i++) {
			int value = arr[i];
			Integer first = pos.get(value);
			if (null == first) {
				pos.put(value, i);
				continue;
			} else {
				int diff = i - first;
				if (diff > max)
					max = diff;
			}
		}

		return max;

	}
}
