$(APP_S): %.VtableImpl.s : %.mpl $(MAPLE_BIN) $(MPLCG_BIN)
	$(MAPLE_BIN) --infile $< $(MPLCOMBO_FLAGS) --save-temps

