spell.exe: dsa2proj1.o hashtable.o
	g++ -o spell.exe dsa2proj1.o hashtable.o

dsa2proj1.o: dsa2proj1.cpp hash.h
	g++ -c dsa2proj1.cpp

hashtable.o: hashtable.cpp hash.h
	g++ -c hashtable.cpp

debug:
	g++ -g -o spellDebug.exe dsa2proj1.cpp hashtable.cpp

clean:
	rm -f *.exe *.o *.stackdump *~

backup:
	test -d backups || mkdir backups
	cp *.cpp backups
	cp *.h backups