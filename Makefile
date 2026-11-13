bleach-game: src/main.c src/jogo.c src/combate.c src/monstros.c src/personagem.c src/progressao.c src/tabuleiro.c src/menu.c src/historia.c include/combate.h include/jogo.h include/menu.h include/monstros.h include/personagem.h include/progressao.h include/tabuleiro.h include/tipos.h include/historia.h
	gcc -std=c99 -Wall -Wextra -Iinclude src/main.c src/jogo.c src/combate.c src/monstros.c src/personagem.c src/progressao.c src/tabuleiro.c src/menu.c src/historia.c -o bleach-game -lm

clean: 
	 rm -f bleach-game
