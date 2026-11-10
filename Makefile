bleach-game: src/main.c src/jogo.c src/combate.c src/monstros.c src/personagem.c src/progressao.c src/tabuleiro.c
	gcc -std=c99 -Wall -Wextra -Iinclude src/main.c src/jogo.c src/combate.c src/monstros.c src/personagem.c src/progressao.c src/tabuleiro.c -o bleach-game -lm

clean: 
	 rm -f bleach-game
