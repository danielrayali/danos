SUBDIRS := kernel

all: $(SUBDIRS)

$(SUBDIRS):
	$(MAKE) -C $@

clean:
	rm -rf build/danos.bin kernel/*.o danos.bin

.PHONY: $(SUBDIRS)
