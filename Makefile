ECHO=@echo
RM=rm
MKDIR=mkdir
EDL=g++
COMP=g++
CCFLAGS=-ansi -pedantic -Wall -std=c++17 # -g -DMAP
RMFLAGS=-f
LDFLAGS=$(CCFLAGS)
LIBS=-lm
SRC=src
MAINFILE=$(SRC)/main
TEST=test
UNITTESTSFILE=$(TEST)/unit-tests/test
INT=$(addprefix $(SRC)/data/, Parser.h) $(addprefix $(SRC)/model/, Attribute.h Measurement.h Sensor.h PrivateIndividual.h Cleaner.h Provider.h) $(addprefix $(SRC)/service/, SensorAnalyzer.h) $(addprefix $(SRC)/vue/, UserInterface.h) 
REAL=$(INT:.h=.cpp)
OBJ=$(INT:.h=.o)
EFFACE=clean
BIN=bin
EXE=$(BIN)/air-watcher
UNITTESTSEXE=$(BIN)/unit-tests

.PHONY:$(EFFACE)

$(EXE): $(OBJ) $(MAINFILE).o
	$(ECHO) "Edition des liens de $(EXE)"
	$(MKDIR) -p $(BIN)
	$(EDL) -o $(EXE) $(MAINFILE).o $(OBJ) $(LIBS) $(LDFLAGS)

unit-tests: $(OBJ) $(UNITTESTSFILE).o
	$(ECHO) "Edition des liens de $(UNITTESTSEXE)"
	$(MKDIR) -p $(BIN)
	$(EDL) -o $(UNITTESTSEXE) $(UNITTESTSFILE).o $(OBJ) $(LIBS) $(LDFLAGS)

%.o: %.cpp
	$(ECHO) "Compilation de <$<>"
	$(COMP) -o $@ -c $< $(CCFLAGS)

$(EFFACE):
	$(ECHO) "Nettoyage"
	$(RM) $(RMFLAGS) $(OBJ) $(EXE) $(MAINFILE).o $(UNITTESTSEXE) $(UNITTESTSFILE).o core
