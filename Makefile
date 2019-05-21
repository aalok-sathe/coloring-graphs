

install: graphtool deps
	

graphtool:
	sudo apt-get install python3-graph-tool
	
deps:
	python3 -m pip install --user -r requirements.txt
