echo 1
< test.txt grep a1 | cat -e | wc -w > result.txt
echo result: 
# wc creates problem

echo 1b
< read.sh grep a1 | cat -e | wc -w > result.txt
echo result: 
# wc creates problem

echo 2
< ./Libft ls -l | wc -l > result.txt
echo result: Segmentation fault
#from the beginning

echo 2b
< ./libft ls -l | ls -a > result.txt

echo 3
< test.txt grep a1 | wc -w > result.txt
echo result: ??????????????

echo 4: absolute path as a cmd
< test.txt /usr/bin/ls/ | wc -l > result.txt
echo result: 
# wc creates problem
# meassage will be changed

echo 5: binary file as a cmd
< test.txt ./checker_linux | grep a > result.txt
echo result: 
# grep creates problem

echo 5b: binary file as a cmd
< test.txt ./checker_linux
echo result: WORKS FINE
#exit code to be checked

echo 6: empty cmd
< test.txt "" | wc -l > result.txt
echo result: ???????????????
# wc creates problem
#exit code to be checked
#token to be checked

echo 6b: empty cmd
< test.txt "" > result.txt
echo result: ???????????????
#exit code to be checked
#token to be checked

echo 7: empty file
< empty.txt ls -l | wc -l > result.txt
echo result: ???????????????
# wc creates problem

echo 7b: empty file
< empty.txt ls -l > result.txt
echo result: WORKS FINE

echo 8: one space cmd
< test.txt " " | wc -l > result.txt
echo result: ???????????????
# wc creates problem

echo 8b
< test.txt
echo result: WORKS FINE
#exit code to be checked

echo 8c
< test.txt " "
echo result: 
#exit code to be checked
#token to be checked

echo 9: UNSET PATH
#unset PATH
< test.txt ls -l | wc -l > result.txt
ls -l test.txt | wc -l 
echo result: ????????????????????

echo 10
cat read.sh > out.txt
echo result: WORKS FINE

echo 11
< read.sh cat > out.txt
echo result: WORKS FINE

echo 12
cat < read.sh > out.txt
cat read.sh
echo result: WORKS FINE

echo 13
cat read.sh >> out.txt
echo result: WORKS FINE

echo 14
< read.sh cat >> out.txt
echo result: WORKS FINE

echo 15
cat < read.sh >> out.txt
echo result: WORKS FINE

echo 16
cat read.sh >out.txt
echo result: WORKS FINE

echo 17
< read.sh cat >out.txt
echo result: WORKS FINE

echo 18
cat < read.sh >out.txt
echo result: WORKS FINE

echo 19
cat read.sh >>out.txt
echo result: WORKS FINE

echo 20
< read.sh cat >>out.txt
echo result: WORKS FINE

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

echo 27
< read.sh cat > out.txt > out2.txt
echo result: WORKS FINE

echo 28
cat < read.sh > out.txt > out2.txt
echo result: WORKS FINE

echo 29
cat read.sh >> out.txt >> out2.txt
echo result: WORKS FINE

echo 29b
ls -l >> out.txt >> out2.txt
echo result: WORKS FINE

echo 30
< read.sh cat >> out.txt >> out2.txt
echo result: WORKS FINE

echo 31
cat < read.sh >> out.txt >> out2.txt
echo result: WORKS FINE

echo 32
>>             test.txt
echo result: WORKS FINE

echo 33
cat read.sh > out
#cat: out: input file is output file

echo 34
->here_doc_cmd
#zsh: segmentation fault (core dumped)  ./minishell

echo 35
echo hello > out3

echo 36
cat read.sh | echo >> out4