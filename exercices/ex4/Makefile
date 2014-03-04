SRC_JPG=$(wildcard *.jpg)
SRC_PNG=$(wildcard *.png)
OUTPUT_PNG=$(SRC_JPG:.jpg=.png)
OUTPUT_PNG_BB=$(OUTPUT_PNG:.png=.bb)
SRC_PNG_BB=$(SRC_PNG:.png=.bb)

all: png bb

png: $(OUTPUT_PNG)

bb: $(SRC_PNG_BB) $(OUTPUT_PNG_BB)

%.png: %.jpg
	convert $^ $@ 

%.bb: %.png
	@ebb $<
	@echo -n "$^\t" & cat $*.bb | grep %%Bounding

.PHONY: clean

clean:
	rm -rf $(OUTPUT_PNG) 
	rm -rf *.bb
