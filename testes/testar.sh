echo "Running unit tests:"

for i in testes/*_testes
do
	if test -f $i
	then
		if $VALGRIND ./$i 2>> testes/testes.log
		then
			echo $i PASSOU
		else
			echo "ERRO no teste $i: aqui está testes/testes.log"
			echo "------"
			tail testes/testes.log
			exit 1
		fi
	fi
done

echo ""
