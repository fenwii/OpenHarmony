$(APP_MPL): %.mpl : %.jar $(JBC2MPL_BIN)
	$(JBC2MPL_BIN) --mplt $(LIB_MPLT) -injar $(APP_JAR) -out $(APP)
