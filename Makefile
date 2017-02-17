all:
	@echo "=====Compiling Lore Library====="
	@make -C Lore
	@echo "=====Compiling Test project====="
	@make -C Test
	@echo "=====Compiling Done====="

clean:
	@make -C Lore clean
	@make -C Test clean
