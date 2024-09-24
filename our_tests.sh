echo 1
< test.txt grep a1 | cat -e | wc -w > result.txt
echo result: ----SYNTAX ANALYSIS---- Segmentation fault

echo 2
< ./Libft ls -l | wc -l > result.txt
echo result: ----SYNTAX ANALYSIS---- Segmentation fault

echo 3
< test.txt grep a1 | wc -w > result.txt
echo result: ----SYNTAX ANALYSIS---- Segmentation fault

echo 4: absolute path as a cmd
< test.txt /usr/bin/ls/ | wc -l > result.txt
echo result: ----SYNTAX ANALYSIS---- Segmentation fault

echo 5: binary file as a cmd
< test.txt ./checker_linux | grep a > result.txt
echo result: ----SYNTAX ANALYSIS---- Segmentation fault

echo 6: empty cmd
< test.txt "" | wc -l > result.txt
echo result: ----SYNTAX ANALYSIS---- Segmentation fault

echo 7: empty file
< empty.txt ls -l | wc -l > result.txt
echo result: ----SYNTAX ANALYSIS---- Segmentation fault

echo 8: one space cmd
< test.txt " " | wc -l > result.txt
echo result: ----SYNTAX ANALYSIS---- Segmentation fault

echo 9: UNSET PATH
#unset PATH
< test.txt ls -l | wc -l > result.txt
echo result: ????????????????????

echo 10
cat read.sh > out.txt
echo result: WORKS FINE

echo 11
< read.sh cat > out.txt
echo result: permission denied 
#because seg fault in syntax analysis

echo 11_2
< read.sh cat
echo result: ----SYNTAX ANALYSIS---- Segmentation fault

echo 12
cat < read.sh > out.txt
echo result: WORKS FINE

echo 13
cat read.sh >> out.txt
echo result: WORKS FINE

echo 14
< read.sh cat >> out.txt
echo result: permission denied
#because seg fault in syntax analysis

echo 15
cat < read.sh >> out.txt
echo result: WORKS FINE

echo 16
cat read.sh >out.txt
echo result: WORKS FINE

echo 17
< read.sh cat >out.txt
echo result: permission denied
#because seg fault in syntax analysis

echo 18
cat < read.sh >out.txt
echo result: WORKS FINE

echo 19
cat read.sh >>out.txt
echo result: WORKS FINE

echo 20
< read.sh cat >>out.txt
echo result: permission denied
#because seg fault in syntax analysis

echo 21
cat < read.sh >>out.txt
echo result: WORKS FINE

echo 22
cat | cat | ls -l | wc -l
echo result: gives different result
#to be checked

echo 23
cat | cat | ls
echo result: gives same result but exits from shell
#to be checked

echo 24
<<eof cat
$HOME
bla
eof
echo result: ----SYNTAX ANALYSIS---- Segmentation fault

echo 25
<< eof cat
bla
eof
echo result: ----SYNTAX ANALYSIS---- Segmentation fault

echo 26
cat read.sh > out.txt > out2.txt
echo result: WORKS FINE
#but it creates a new file with the same name if it is done in another bash for testing
#it does not do in Codam computer

echo 27
< read.sh cat > out.txt > out2.txt
echo result: permission denied 
#because seg fault in syntax analysis

echo 28
cat < read.sh > out.txt > out2.txt
echo result: WORKS FINE

echo 29
cat read.sh >> out.txt >> out2.txt
echo result: WORKS FINE

echo 30
< read.sh cat >> out.txt >> out2.txt
echo result: permission denied
#because seg fault in syntax analysis

echo 31
cat < read.sh >> out.txt >> out2.txt
echo result: WORKS FINE

echo 32
return
echo Error: empty line
#it additinally closes the program