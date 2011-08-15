#!/bin/sh
# usage ./run.sh input.txt output.txt
#for internal scripts
# usage: ./stanford-postagger.sh model textFile
#  e.g., ./stanford-postagger.sh models/left3words-wsj-0-18.tagger sample-input.txt
# Runs the English PCFG parser on one or more files, printing trees only
# usage: ./lexparser.csh fileToparse+
#
#c++ wrap_tagger.cpp -o wtag
#c++ wrap_parser.cpp -o wpar
#c++ wrap.cpp -o w
#tagging
java -mx300m -cp 'stanford-postagger.jar:' edu.stanford.nlp.tagger.maxent.MaxentTagger -model models/left3words-wsj-0-18.tagger -textFile $1
#java -cp 'stanford-postagger.jar:' tag $1 $2
#taaged ouptut to map
#./wtag <tag_o.txt
#parsing
#java -mx150m -cp "stanford-parser.jar:" edu.stanford.nlp.parser.lexparser.LexicalizedParser -outputFormat "typedDependencies" ./englishPCFG.ser.gz $1 > par_o.txt
#relations and words in data structure
#./wpar <par_o.txt
#taaged ouptut to map alongwith 'relations and words' in data structure
#./w >$2
#cat $2 | grep $3 > final.txt
