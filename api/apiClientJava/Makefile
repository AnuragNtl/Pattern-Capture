include ../../Makefile

apiClientJava:
	@./gradlew clean build
	@cd $(current_dir) && pwd &&  java -jar javacpp-platform-1.5.3-bin/javacpp.jar -classpath api/apiClientJava/build/classes/java/main api.ApiClient -d $(current_dir)api/apiClientJava -header 
	@mv libjniApiClient.so $(current_dir)/lib
	$(call build_library,ApiClientJava.cpp,ApiClientJava,-lApiClient -ljniApiClient,-I/usr/lib/jvm/java/include/ -I/usr/lib/jvm/java/include/linux/)

