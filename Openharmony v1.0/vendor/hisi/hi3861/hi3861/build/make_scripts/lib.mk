#all: $(LIBOUT)
$(OBJS): $(OBJDIR)/%.o : %.c
	$(Q)if [ ! -d $(dir $@) ]; then \
	mkdir -p $(dir $@); \
	fi;
	$(Q) echo Compile $<;
ifeq ($(ID_CFG_FILE), $(wildcard $(ID_CFG_FILE)))
	$(Q)if [ -e $(ID_CFG_FILE) ]; \
	then ID=$(shell grep -e $(notdir $<) -w -m1 $(ID_CFG_FILE) | grep -e "\s[0-9]*" -o |tr -cd "[0-9]"); \
	if [ -z $$ID ]; \
	then $(CC) $(CCFLAGS) -c $< -o $@; \
	else $(CC) $(CCFLAGS) -D__NEW_FILE_ID__=$$ID -c $< -o $@; \
	fi; \
	if [ "$$?" != "0" ]; then \
	exit 1;\
	fi; \
	fi;
else
	$(Q)if [ -e $< ]; \
	then $(CC) $(CCFLAGS) -c $< -o $@; \
	if [ "$$?" != "0" ]; then \
	exit 1;\
	fi; \
	fi;
endif

$(ASM_OBJS): $(OBJDIR)/%.o : %.S
	$(Q)echo Compile  $<;
	$(Q)if [ ! -d $(dir $@) ]; \
	then \
	mkdir -p $(dir $@);\
	fi;
	$(Q)if [ -f $< ]; \
	then \
	$(CC) $(ASFLAGS)  -c $< -o $@ ; \
	if [ "$$?" != "0" ]; then \
	exit 1;\
	fi;\
	fi;

$(LIBOUT): $(OBJS) $(ASM_OBJS)
	$(Q)if [ ! -d $(dir $@) ]; \
	then \
	mkdir -p $(dir $@);\
	fi;
	$(Q)$(AR) $(ARFLAGS) $@ $(sort $^)
	$(Q)echo make [$(LIB_NAME)] SUCCESS

