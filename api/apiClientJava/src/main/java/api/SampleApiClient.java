package api;

import java.util.HashMap;

public class SampleApiClient implements DependencyNode {

	@Override
	public Object process(InputProperties inputProperties) {
        System.out.println("In SampleApiClient");
        return new HashMap<String, String>() {{
            put("a", "20");
        }};
	}


};

