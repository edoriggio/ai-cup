CC := g++ -std=c++11
SRCDIR := src
BUILDDIR := build
TARGET := bin/runner
 
SRCEXT := cpp
SOURCES := $(shell find $(SRCDIR) -type f -name *.$(SRCEXT))
OBJECTS := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.o))
CFLAGS := -w -O3

$(TARGET): $(OBJECTS)
	@echo " Linking..."
	@echo " $(CC) $^ -o $(TARGET)"; $(CC) $^ -o $(TARGET)

$(BUILDDIR)/%.o: $(SRCDIR)/%.$(SRCEXT)
	@mkdir -p $(BUILDDIR)
	@echo " $(CC) $(CFLAGS) -c -o $@ $<"; $(CC) $(CFLAGS) -c -o $@ $<

clean:
	@echo " Cleaning..."
	@echo " $(RM) -r $(BUILDDIR) $(TARGET)"; $(RM) -r $(BUILDDIR) $(TARGET)

run:
	make --always-make
	@echo " Running..."
	@echo " ./$(TARGET)"; ./$(TARGET)

docs: .FORCE
	@echo " Generating docs..."
	@echo " doxygen ./doxyfile.conf"; doxygen ./doxyfile.conf
	@echo " Generating pdf..."
	@echo " make"; cd docs/documentation/latex; make; mv refman.pdf ../../documentation.pdf; cd -

html: .FORCE
	@echo " Opening html..."
	@echo " open docs/documentation/html/index.html"; open docs/documentation/html/index.html

.PHONY: clean
.FORCE:
