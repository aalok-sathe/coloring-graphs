

install: deps
	echo "installing deps. now please call appropriate install method based on "
	echo "your operating system: install[mac|ubuntu|redhat]"

deps:
	python3 -m pip install --user -r requirements.txt

test:
	python3 lib/test/graphtest.py
