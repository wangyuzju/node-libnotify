all: build test


build:
	@node-gyp configure --nodedir=/home/wangyu/IdeaProjects/node --python /home/wangyu/Python-2.6.9/python
	@node-gyp build

test:
	@coffee ./test/hello.coffee
	
.PHONY: build test