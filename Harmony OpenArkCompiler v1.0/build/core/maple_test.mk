include $(MAPLE_BUILD_CORE)/maple_variables.mk

test: $(APP_S)
include $(MAPLE_BUILD_CORE)/mplcomb.mk
include $(MAPLE_BUILD_CORE)/jbc2mpl.mk
include $(MAPLE_BUILD_CORE)/java2jar.mk

.PHONY: clean
clean:
	@rm -rf *.jar
	@rm -f *.class
	@rm -f *.mpl
	@rm -f *.mplt
	@rm -f *.s
	@rm -f *.groots.txt
	@rm -f *.primordials.txt
	@rm -rf comb.log
