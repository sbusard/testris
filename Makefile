# TEsTris
#
# Created by Simon Busard on 22.08.2007
#
# Copyright (C) 2008 Busard Simon
#
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 2 of the License, or
# (at your option) any later version.
# 
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
# GNU General Public License for more details.
# 
# You should have received a copy of the GNU General Public License along
# with this program; if not, write to the Free Software Foundation, Inc.,
# 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.


EXEC=TEsTris
SDLFLAGS=`sdl-config --cflags --libs`
SDLIMGFLAGS=-lSDL_image
SDLTTFFLAGS=-lSDL_ttf
SDLMIXERFLAGS=-lSDL_mixer
ERRORFLAG=-Wall -Werror

all: ${EXEC}

${EXEC}: ./src/${EXEC}.o ./src/game.o ./src/display.o ./src/highscores.o \
			 ./src/config.o ./src/undo.o ./src/music.o	 \
			 ./src/ai.o	./src/events.o ./src/model.o	 \
			 ./src/constants.h ./src/pieces.h 		 \
			 ./src/game.h ./src/display.h ./src/highscores.h \
			 ./src/model.h \
			 ./src/config.h ./src/music.h ./src/ai.h ./src/events.h
	gcc -o  ${EXEC} -g ./src/${EXEC}.o 			\
		${SDLFLAGS} ${SDLIMGFLAGS} ${SDLTTFFLAGS} ${SDLMIXERFLAGS} \
		./src/game.o ./src/display.o ./src/highscores.o \
		./src/config.o ./src/undo.o ./src/music.o	\
		./src/ai.o ./src/events.o ./src/model.o			\
		${ERRORFLAG}

${EXEC}.o: ./src/${EXEC}.c ./src/constants.h
	gcc -c -g -o ./src/${EXEC}.c ${ERRORFLAG}

game.o: ./src/game.c ./src/game.h ./src/constants.h ./src/pieces.h ./src/model.h
	gcc -c -g -o ./src/game.c ${ERRORFLAG}

display.o: ./src/display.c ./src/display.h ./src/constants.h
	gcc -c -g ./src/display.c ${ERRORFLAG}

highscores.o: ./src/highscores.c ./src/highscores.h
	gcc -c -g ./src/highscores.c ${ERRORFLAG}

config.o: ./src/config.c ./src/config.h ./src/constants.h
	gcc -c -g ./src/highscores.c ${ERRORFLAG}

undo.o: ./src/undo.c ./src/undo.h
	gcc -c -g ./src/undo.c ${ERRORFLAG}

music.o: ./src/music.c ./src/music.h
	gcc -c -g ./src/music.c ${ERRORFLAG}

ai.o: ./src/ai.c ./src/ai.h
	gcc -c -g ./src/ai.c ${ERRORFLAG}

events.o: ./src/events.c ./src/events.h ./src/model.h
	gcc -c -g ./src/events.c ${ERRORFLAG}

model.o: ./src/model.c ./src/model.h ./src/constants.h
	gcc -c -g ./src/model.c ${ERRORFLAG}

clean:
	rm -fr ./src/*.o
	rm -fr ./src/*~
	rm -fr ./*~

mrpropre: clean
	rm -fr ${EXEC}
