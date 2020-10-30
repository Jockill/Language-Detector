FLAGS = -g -Iinclude -Wall -Wextra

OBJPATH = ./obj/
HEADPATH = ./header/
SRCPATH = ./src/
DOCPATH = ./doc/

main: $(OBJPATH)main.o $(OBJPATH)stack.o $(OBJPATH)utils.o
	gcc $^ $(FLAGS) -o languageDetector

./obj/main.o: $(HEADPATH)main.c $(HEADPATH)stack.c $(HEADPATH)utils.c
	mkdir -p $(OBJPATH)
	gcc $(FLAGS) -c $(SRCPATH)main.c -o $@

./obj/%.o: $(SRCPATH)%.c $(HEADPATH)%.h
	gcc $(FLAGS) -c $< -o $@

doc:
	doxygen $(DOCPATH)Doxyfile

clean:
	rm -r $(OBJPATH)* $(DOCPATH)* languageDetector 
