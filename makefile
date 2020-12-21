FLAGS = -g -Iinclude -Wall -Wextra

OBJPATH = ./obj/
HEADPATH = ./header/
SRCPATH = ./src/
DOCPATH = ./doc/

main: $(OBJPATH)main.o $(OBJPATH)stack.o $(OBJPATH)utils.o $(OBJPATH)io.o $(OBJPATH)arbre.o $(OBJPATH)dawg.o
	gcc $^ $(FLAGS) -o languageDetector

tempsDawg: $(OBJPATH)main_temps_dawg.o $(OBJPATH)stack.o $(OBJPATH)utils.o $(OBJPATH)dawg.o $(OBJPATH)io.o $(OBJPATH)arbre.o
	gcc $^ $(FLAGS) -o ./time_dawg

tempsTrie: $(OBJPATH)main_temps_trie.o $(OBJPATH)stack.o $(OBJPATH)utils.o $(OBJPATH)dawg.o $(OBJPATH)io.o $(OBJPATH)arbre.o
	gcc $^ $(FLAGS) -o ./time_trie

# ./obj/main.o: $(HEADPATH)main.c $(HEADPATH)stack.c $(HEADPATH)utils.c
./obj/main.o: $(HEADPATH)stack.h $(HEADPATH)utils.h
	mkdir -p $(OBJPATH)
	gcc $(FLAGS) -c $(SRCPATH)main.c -o $@

./obj/main_temps_dawg.o:
	mkdir -p $(OBJPATH)
	gcc $(FLAGS) -c $(SRCPATH)main_temps_dawg.c -o $@

./obj/main_temps_trie.o:
	mkdir -p $(OBJPATH)
	gcc $(FLAGS) -c $(SRCPATH)main_temps_trie.c -o $@

./obj/%.o: $(SRCPATH)%.c $(HEADPATH)%.h
	gcc $(FLAGS) -c $< -o $@

doc:
	doxygen $(DOCPATH)Doxyfile

clean:
	rm -r $(OBJPATH)* $(DOCPATH)* languageDetector
