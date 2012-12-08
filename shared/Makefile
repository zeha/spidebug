
all: generated.h SerialInterface_gen.cs

generated.h: generate_c.py data/*.json
	./generate_c.py > generated.h

SerialInterface_gen.cs: generate_cs.py data/*.json
	./generate_cs.py > SerialInterface_gen.cs
