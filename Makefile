all:
	@echo "=====Compiling GamePack Library====="
	@make -C GamePack
	@echo "=====Compiling Test project====="
	@make -C Test

clean:
	@make -C GamePack clean
	@make -C Test clean
