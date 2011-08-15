java -mx150m -cp "stanford-parser.jar:" edu.stanford.nlp.parser.lexparser.LexicalizedParser -outputFormat "typedDependencies" ./englishPCFG.ser.gz $1
