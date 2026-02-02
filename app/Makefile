########       AVR Project Makefile       ########
#####                                        #####
#####      Makefile produit et écrit par     #####
#####   Simon Barrette & Jerome Collin pour  #####
#####           INF1900 - 2016               #####
#####                                        #####
#####         Inspiré de Pat Deegan -        #####
#####  Psychogenic Inc (www.psychogenic.com) #####
##################################################

# Nom du microcontrôleur cible
MCU = atmega324pa

# Nom du projet
PROJECTNAME = OppsMobile

# Fichiers source
PRJSRC = $(wildcard *.cpp)

# Inclusions supplémentaires
INC = $(shell find ../lib -type d -exec echo -I{} \;)

# Librairies à lier
LIBS = -L../lib -lrobot

# Optimisation
OPTLEVEL = s

# Identifiant du programmateur
AVRDUDE_PROGRAMMERID = usbasp

##################################################
#####           Configuration système        #####
##################################################

CXX = avr-g++
OBJCOPY = avr-objcopy
AVRDUDE = avrdude
REMOVE = rm -f
HEXFORMAT = ihex
F_CPU = 8000000UL

CFLAGS = -I. -I/usr/include/simavr -MMD $(INC) -g -mmcu=$(MCU) -O$(OPTLEVEL) \
         -std=c++14 -fshort-enums -funsigned-bitfields -funsigned-char \
         -Wall -DF_CPU=$(F_CPU)

CXXFLAGS = -fno-exceptions
LDFLAGS = -Wl,-Map,$(PROJECTNAME).map -mmcu=$(MCU)

TRG = $(PROJECTNAME).elf
HEXROMTRG = $(PROJECTNAME).hex
HEXTRG = $(HEXROMTRG) $(PROJECTNAME).ee.hex

CFILES = $(filter %.c, $(PRJSRC))
CPPFILES = $(filter %.cpp, $(PRJSRC))
OBJDEPS = $(CFILES:.c=.o) $(CPPFILES:.cpp=.o)

.PHONY: all install clean debug

all: $(TRG) $(HEXROMTRG)

debug: CXXFLAGS += -DDEBUG -g
debug: CFLAGS += -DDEBUG -g
debug: clean all

$(TRG): $(OBJDEPS)
	$(CXX) $(LDFLAGS) -o $(TRG) $(OBJDEPS) $(LIBS)

%.o: %.c
	$(CXX) $(CFLAGS) -c $<

%.o: %.cpp
	$(CXX) $(CFLAGS) $(CXXFLAGS) -c $<

%.hex: %.elf
	$(OBJCOPY) -j .text -j .data -O $(HEXFORMAT) $< $@

-include *.d

install: $(HEXROMTRG)
	$(AVRDUDE) -v -c $(AVRDUDE_PROGRAMMERID) -p $(MCU) -P usb -B 10 -U flash:w:$(HEXROMTRG)

clean:
	$(REMOVE) $(TRG) $(PROJECTNAME).map $(OBJDEPS) $(HEXTRG) *.d