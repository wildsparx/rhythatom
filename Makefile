# Copyright (C) 2017 Asher Blum

INCS := $(shell ls *.inc)

# Start from scratch since building is fast:
ALL: clean index.html

index.html: pre.html
	python2 proc.py pre.html $@

clean:
	rm -f *.auto index.html

