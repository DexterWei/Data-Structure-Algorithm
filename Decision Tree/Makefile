CC=g++
PROG=tree
FNAME=wine.train
PNAME=wine.test
THETA=5
RM=rm -rf

.PHONY: all run_tree clean_tree_pred predict_tree clean

all:$(PROG)

tree: tree.cpp 
	$(CC) ./tree.cpp -o tree

tree_pred.h: tree $(FNAME)
	./tree $(FNAME) $(THETA)

clean_tree_pred:
	$(RM) tree_pred.h

run_tree: clean_tree_pred tree_pred.h

predict_tree: tree_predictor.cpp tree_pred.h $(PNAME)
	$(CC) ./tree_predictor.cpp -o ./tree_predictor
	./tree_predictor $(PNAME) > ./tree_prediction.txt

clean:
	$(RM) $(PROG)

