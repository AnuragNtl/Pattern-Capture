package api;

import java.util.Map;

import com.fasterxml.jackson.core.type.TypeReference;
import com.fasterxml.jackson.databind.DeserializationFeature;
import com.fasterxml.jackson.databind.MapperFeature;
import com.fasterxml.jackson.databind.ObjectMapper;

public class InputProperties {
    
    private String nodeClass;

    private Map<String, String> inputProperties;

    private Map<String, Object> inputData;

    private static ObjectMapper objectMapper = new ObjectMapper();

    static {
        objectMapper.configure(MapperFeature.ACCEPT_CASE_INSENSITIVE_PROPERTIES, true);
        objectMapper.configure(DeserializationFeature.FAIL_ON_UNKNOWN_PROPERTIES, false);
    }

    public String getNodeClass() {
        return nodeClass;
    }

    public Map<String, Object> getInputData() {
		return inputData;
	}

	public void setInputData(Map<String, Object> inputData) {
		this.inputData = inputData;
	}

	public void setNodeClass(String nodeClass) {
        this.nodeClass = nodeClass;
    }

    public Map<String, String> getInputProperties() {
        return inputProperties;
    }

    public void setInputProperties(Map<String, String> inputProperties) {
        this.inputProperties = inputProperties;
    }

    public static <T> T getBeanFromInputProperties(InputProperties inputProperties) {
        return objectMapper.convertValue(inputProperties, new TypeReference<T>(){});
    }


};

