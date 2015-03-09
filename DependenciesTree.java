public class DependenciesTree {
	private static final String input = "a->b\nb->c\nb->d\nc->d";
	private static final String inputLoop = "a->b\nb->c\nb->d\nc->d\nd->a";

	public static void main(String[] args) {
		System.out.println(getCompileOrder(input));
		System.out.println(getCompileOrder(inputLoop));
	}

	public static String getCompileOrder(String input) {
		Map<String, Node> nodes = new HashMap<String, Node>();
		List<Node> ret = new LinkedList<Node>();

		BufferedReader reader = new BufferedReader(new StringReader(input));
		try {
			while (true) {
				String line = reader.readLine();
				if (null == line)
					break;
				// System.out.println(line);
				String[] strs = line.split("->");
				if (strs.length != 2)
					throw new Exception("invalid rule:" + line);
				String firstStr = strs[0];
				String secondStr = strs[1];
				Node first = nodes.get(firstStr);
				Node second = nodes.get(secondStr);
				if (null == second) {
					second = new Node(secondStr);
					nodes.put(secondStr, second);
				}

				if (null == first) {
					first = new Node(firstStr);
					nodes.put(firstStr, first);
				}

				first.dep.add(second);
			}

			// for (Node n : nodes.values()) {
			// System.out.println(n);
			// }

			for (int i = 0; i < nodes.size(); i++) {
				boolean nochange = true;
				for (Node node : nodes.values()) {
					// check if all dependencies are processed
					if (!node.processed && node.isDepsAllProcessed()) {
						node.processed = true;
						ret.add(node);
						nochange = false;
					}
				}

				boolean allDone = true;
				for (Node node : nodes.values()) {
					if (!node.processed)
						allDone = false;
				}
				if (allDone) {
					break;
				}

				if (nochange) {
					throw new Exception("loop found");
				}
			}

		} catch (Exception e) {
			e.printStackTrace();
		}
		return ret.toString();
	}
}
