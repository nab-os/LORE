ifeq ($(OS),Windows_NT)
	MAKE=@mingw32-make
else
	MAKE=@make
endif
	
all:
	@echo "=====Compiling Lore Library====="
	$(MAKE) -C Lore
	@echo "=====Compiling Test project====="
		$(MAKE) -C Test
	@echo "=====Compiling Done====="

clean:
	$(MAKE) -C Lore clean
	$(MAKE) -C Test clean