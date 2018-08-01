MKDIR := mkdir -p
RM := rm -rf

all: ./out/Makefile
	@ $(MAKE) -C out

./out/Makefile:
	@ ($(MKDIR) out > /dev/null)
	@ (cd out > /dev/null 2>&1 && cmake ..)

distclean:
	@ ($(MKDIR) out > /dev/null)
	@ (cd out > /dev/null 2>&1 && cmake .. > /dev/null 2>&1)
	@- $(MAKE) --silent -C out clean || true
	@- $(RM) ./out/Makefile
	@- $(RM) ./out/src
	@- $(RM) ./out/test
	@- $(RM) ./out/CMake*
	@- $(RM) ./out/cmake.*
	@- $(RM) ./out/*.cmake
	@- $(RM) ./out/*.txt
	@- find . -name '.DS_Store' -type f -delete
