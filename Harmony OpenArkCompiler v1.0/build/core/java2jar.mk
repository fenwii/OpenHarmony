$(APP_JAR): %.jar : %.java
	$(JAVA2JAR) $(APP_JAR) ${MAPLE_ROOT}/libjava-core/java-core.jar "$(wildcard *.java)"
