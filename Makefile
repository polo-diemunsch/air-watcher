ECHO=@echo
RM=rm
MKDIR=mkdir
EDL=g++
COMP=g++
CCFLAGS=-ansi -pedantic -Wall -std=c++17 # -g -DMAP
RMFLAGS=-f
LDFLAGS=$(CCFLAGS)
LIBS=
SRC=src
MAINFILE=$(SRC)/main
INT=$(addprefix $(SRC)/data/, Parser.h) $(addprefix $(SRC)/model/, Attribute.h Measurement.h Sensor.h PrivateIndividual.h Cleaner.h Provider.h)
REAL=$(INT:.h=.cpp)
OBJ=$(INT:.h=.o)
EFFACE=clean
BIN=bin
EXE=$(BIN)/air-watcher
TEST_EXE=$(BIN)/test

.PHONY:$(EFFACE)

$(EXE): $(OBJ) $(MAINFILE).o
	$(ECHO) "Edition des liens de $(EXE)"
	$(MKDIR) -p $(BIN)
	$(EDL) -o $(EXE) $(MAINFILE).o $(OBJ) $(LIBS) $(LDFLAGS)

%.o: %.cpp
	$(ECHO) "Compilation de <$<>"
	$(COMP) -o $@ -c $< $(CCFLAGS)

$(EFFACE):
	$(ECHO) "Nettoyage"
	$(RM) $(RMFLAGS) $(OBJ) $(EXE) $(TESTFILE) $(TESTFILE).o $(MAINFILE).o core
